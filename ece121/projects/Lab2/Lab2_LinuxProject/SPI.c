/* 
 * @file SPI.c
 * @version 1.0
 * @author Nicholas Kuipers
 * @purpose Library allowing for a SPI interface between the PIC32 and
 *      a device connected to its respective SPI pins
 */

#include "SPI.h"

/*******************************************************************************
 * GLOBAL VARIABLES                                                            *
 ******************************************************************************/

unsigned int* rxFrame, txFrame;

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                           *
 ******************************************************************************/

/**
 * @brief Initializes the pins of the SPI Interface so the PIC32
 *      is the master connected to a slave. This does not yet communicate
 *      anything to the external hardware connected to the PIC32 via SPI.
 *      This initialization performs the following:
 *      - Activates the SPI pins on the I/O shield and pulls them high or low
 *          depending on their function:
 *              - MOSI (Master Out, Slave In) = Pin 11, Port G Bit 8, Output Pin, Init Low
 *              - MISO (Master In, Slave Out) = Pin 12, Port G Bit 7, Input Pin
 *              - SCK  (System Clock)         = Pin 13, Port G Bit 6, Output Pin, Init Low
 *              - SS   (Slave Select)         = Pin 10, Port D Bit 4 OR Oscillator 5, Output Pin, Init High
 *      - Allocates memory for rxPacket and txPacket
 *      - Activates SPI itself in the hardware by writing the SPI-specific registers. Uses instructions from
 *          page 18 of the PIC32 FRM Section 23: SPI
 *          - Diables the SPI interrupts in IECx
 *          - Resets the SPI module by clearing the ON bit in SPICON
 *          - Clears the receive buffer
 *          - Sets the ENHBUF bit in SPIxCON (for Enhanced Buffer Mode with 128-bit FIFOs)
 *          - No SPI Interrupts are used
 *          - Writes the Baud Rate Register (SPIxBRG)
 *          - Clears the SPIROV bit in SPIxSTAT<6>
 *          - Write "the desired settings" in SPIxCON -- MSTEN(SPIxCON<5>) = 1
 *          - Enable SPI operation (set ON bit in SPIxCON<15>). Transmission and reception activate
 *              automatically upon data being written to the SPIxBUF register
 * @param nothing
 * @return nothing
 * @author Nicholas Kuipers
 */
void SPI_Init()
{
    // First, activate and configure the SPI Pins (see define values in SPI.h)
    MOSI_IO  = 0;    // MOSI Pin is an output
    MOSI_VAL = 0;    // Asserts MOSI Pin low
    MISO_IO  = 1;    // MISO Pin is an input
    SCK_IO   = 0;    // SCK Pin is an output -- Might use OSC5 instead?
    SCK_VAL  = 0;    // Asserts SCK Pin low
    SS_IO    = 0;    // Slave Select is an output
    SS_VAL   = 1;    // SS pin is asserted high until a SPI transaction is performed
    
    // Allocate memory for rxPacket
    rxFrame = (unsigned int) malloc(sizeof(int));
    txFrame = (unsigned int) malloc(sizeof(int));
    
    // Now, we configure SPI
    IEC0bits.SPI1EIE  = 0;   // SPI Interrupt disabled
    IEC0bits.SPI1RXIE = 0;   // SPI Interrupt disabled
    IEC0bits.SPI1TXIE = 0;   // SPI Interrupt disabled
    SPI1CONbits.ON      = 0;   // SPI module reset, ON bit cleared
    SPI1BUF             = 0;   // Clears SPI receive buffer
    SPI1BRGSET          = 1;   // Set Baud Rate Generator -- Baud Rate determined by PBCLK/BRG (see pg 23, FRM sec23)
    SPI1STATbits.SPIROV = 0;   // Clear Receive Overflow bit
    SPI1CONSET          = 0x10000;  // ENHBUF = bit 16
    SPI1CONbits.MSTEN   = 1;   // Enable Master Mode
    SPI1CONbits.CKE     = 0;   // Output data changes from idle clock state to active
    SPI1CONbits.CKP     = 0;   // Clock idle when low, active when high
    SPI1CONbits.SMP     = 0;   // Input data is sampled at middle of data output time
    
    SPI1CONbits.ON      = 1;   // Activate SPI module
}

/**
 * @brief Sends a command frame, then a read frame, to the slave. To perform the send this 
 *      does the following:
 *      - pulls SS pin low to initiate SPI
 *      - sends the command frame via function
 *      - sends the read/write frame immediately after
 *      - wait for incoming bits over SPI from the slave. Once frame is received
 *              (or dropped) and no more data exists on the buffer, pull SS high
 * @param address to read to/write from in slave
 * @param data 
 * @return 
 */
uint8_t SPI_SendReadFrame(int address, int data)
{
    SS_VAL     = 0;    // SS pin pulled low to initiate SPI
    
}

/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/

/**
 * @brief Builds and sends a command frame to the slave (pre-configured for Rotary Encoder)
 *      Command frames are structured as follows (from MSB to LSB):
 *          - Bit 15 : Parity bit, even, calculated on lower 15 bits of command frame
 *          - Bit 14 : denotes following frame - 0 for write, 1 for read
 *          - Bits <13:0> : Address in the RE to read or write
 * @param unsigned int, address to be written to
 * @param type of frame that will follow the command frame
 * @return 0 if success, 1 if error
 * @author Nicholas Kuipers
 */
unsigned int SPI_BuildCommandFrame(unsigned int address, SPI_FrameType type)
{
    unsigned int payload = address;
    if(type == READ)
        payload |= 0x4000;     // set bit 14 to 1
    if(SPI_CalcParityBit(payload))
        payload |= 0x8000;     // parity bit (bit 15) set to 1
    
    return payload;
}

/*
 loads the parity bit into SPIxBUF
 *      - loads RWE bit into SPIxBUF
 *      - loads payload (MSB first) into SPIxBUF
 *      - waits for a flag (?) indicating all data is sent
 *          - (for command) immediately follow up with sending read/write frame
 *          - (for write) pull SS high, ending SPI transaction
 *          - (for read) read incoming bits from a received frame. Assert SS
 *              high once reception is complete
 * 
 * */


/**
 * @brief Calculates the parity bit for a frame by performing the following:
 *      - Each SPI frame must be "even", or there must be an even amount of 1's
 *      - Takes in a frame (prior to transmission or upon reception)
 *      - Copy the 16-bit value to an unsigned int temp. Over the course of 15 bits (payload - parity bit):
 *          - Read the LSB of temp variable. If 1, increment a counter
 *          - Bitshift right the temp variable by 1
 *      - Conditional:
 *          - if the counter is an even value, return 0 (parity bit 0)
 *          - else, return 1 (parity bit 1)
 *  @param frame, whose payload is used to calculate the parity bit
 *  @return parity bit value (0 or 1)
 *  @author Nicholas Kuipers
 */
uint8_t SPI_CalcParityBit(unsigned int payload)
{
    unsigned int counter = 0;                  // increments whenever a 1 is encountered in the for loop
    unsigned int payload = frame->payload;     // allows for bitshifting without affecting the actual payload

    for(int i = 0; i < 14; i++)
    {
        if(payload &= 0x1)      // returns TRUE if the LSB is a 1
            counter++;
        payload = payload >> 1; // payload value is left shifted to next bit
    }       
    if(counter % 2)             // if this returns a 0, counter is even
        return 0;               // SPI word is already even, parity bit is 0
    else
        return 1;               // SPI word is odd, parity bit is 1 to make this even
}
