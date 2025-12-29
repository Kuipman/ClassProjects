/***
 *  @file RotaryEncoder.c
 *  @version 1.0
 *  @author Nicholas Kuipers
 *  @purpose Provides a serial (COM port) interface between the ECE 121 Main Console
 *      and the microcontroller
 */

/*******************************************************************************
 * #INCLUDES                                                                   *
 ******************************************************************************/

#include "RotaryEncoder.h"
#include <stdlib.h>

/*******************************************************************************
 * PRIVATE VARIABLES                                                            *
 ******************************************************************************/

/*******************************************************************************
 * PRIVATE FUNCTIONS PROTOTYPES                                                 *
 ******************************************************************************/

/*******************************************************************************
 * PUBLIC FUNCTION IMPLEMENTATIONS                                             *
 ******************************************************************************/

/**
 * @brief Initializes the pins of the SPI Interface so the PIC32
 *      is the master connected to the rotary encoder slave.
 *      SPI is mode 1 (output sent out at rising clock edge, input sampled at falling edge)
 *      SPI is Framed Mode, Master Mode (generates the clock and SS is an output)
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
 *          - No SPI Interrupts are used
 *          - Writes the Baud Rate Register (SPIxBRG)
 *          - Clears the SPIROV bit in SPIxSTAT<6>
 *          - Write "the desired settings" in SPIxCON -- MSTEN(SPIxCON<5>) = 1
 *          - Enable SPI operation (set ON bit in SPIxCON<15>). Transmission and reception activate
 *              automatically upon data being written to the SPIxBUF register
 * @note1 SPI2 has significantly simpler pins to access (pins 10-13 on the IO shield)
 * @note2 Do we need to write anything to the RE registers?
 * @param nothing
 * @return nothing
 * @author Nicholas Kuipers
 */
int RotaryEncoder_Init(char interfaceMode)
{
    // First, activate and configure the SPI Pins (see define values in SPI.h)
    MOSI_IO  = 0;    // MOSI Pin is an output
    MOSI_VAL = 0;    // Asserts MOSI Pin low
    MISO_IO  = 1;    // MISO Pin is an input
    SCK_IO   = 0;    // SCK Pin is an output -- Might use OSC5 instead?
    SCK_VAL  = 0;    // Asserts SCK Pin low
    SS_IO    = 0;    // Slave Select is an output
    SS_VAL   = 1;    // SS pin is asserted high until a SPI transaction is performed
    
    // Activate Timer 5
    FreeRunningTimer_Init();
    
    // Now, we configure SPI for Master Mode and Frame Master Mode
    IEC1bits.SPI2EIE  = 0;   // SPI Interrupt disabled
    IEC1bits.SPI2RXIE = 0;   // SPI Interrupt disabled
    IEC1bits.SPI2TXIE = 0;   // SPI Interrupt disabled
    IFS1bits.SPI2EIF  = 0;   // Clear Flag
    IFS1bits.SPI2RXIF = 0;   // Clear Flag
    IFS1bits.SPI2TXIF = 0;   // Clear Flag
    SPI2CONbits.ON      = 0;   // SPI module reset, ON bit cleared
    SPI2BUF             = 0;   // Clears SPI receive buffer
    SPI2BRGSET          = 3;   //1?   // Set Baud Rate Generator -- Baud Rate determined by PBCLK/BRG (see pg 23, FRM sec23)
    SPI2STATbits.SPIROV = 0;   // Clear Receive Overflow bit
    SPI2CONbits.MSTEN   = 1;   // Enable Master Mode
    //SPI2CONbits.FRMEN   = 1;
    SPI2CONbits.MODE16  = 1;   // 16-bit mode
    SPI2CONbits.SMP     = 1;   // samples data at falling edge of clock cycle
    SPI2CONbits.CKE     = 0;   // For Mode 1 (see description above)
    SPI2CONbits.CKP     = 0;   // Clock idle when low, active when high
    
    // Activate the SPI module
    SPI2CONbits.ON      = 1;
    
    // Write to RE OTP registers?
    // ...
    
    
    return 0;  // SUCCESS
}

/**
 * @brief Accesses the register on the Rotary Encoder via SPI.
 *      Standard SPI read is executed in the following fashion:
 *          - Pull the SS pin low to begin the SPI transmission
 *          - A frame sync pulse is sent by the serial clock at a rate of 10MHz
 *              (dictated by baud rate setting in init()). Delay the system using
 *              blocking code until this pulse is sent.
 *          - Write 0xFFFF to the SPI2BUF
 *              - The register 0x3FFF on the RE holds the up-to-date angle measurement
 *              with dynamic error compensation
 *              - The command frame must depict a read command, so the RW bit (bit 14)
 *                  is set to 1. Since all other bits (<14:0>) are 1, the resulting 1 bits
 *                  amount to 15, requiring the parity bit to also be 1 so the frame is "even"
 *          - Engage blocking code while system waits for the receive flag to be set (indicates
 *              a response was received from the RE)
 *          - Pull SS pin high to end SPI transmission
 *          - Read SPI2BUF, which holds the 14-bit value from the RE register
 *          - return this 14-bit value
 * @return 14-bit value representing the raw encoder angle (0 - 16384) */
unsigned short RotaryEncoder_ReadRawAngle(void)
{
    SS_VAL = 0;                              // Pull the SS pin low to start SPI transmission
    FreeRunningTimer_DelayMicroseconds(10);  // Block code for 10 microseconds
    SPI2BUF = 0xFFFF;         // Read command to register 0x3FFF on RE
    
    while(!SPI2STATbits.SPIRBF) {} // Blocks code until a frame is received from RE
    /*
    if(SPI2STATbits.SPIROV)
    {
        char* debugMessage2 = (char*)malloc(128);
        //rxFrame = 100;
        sprintf(debugMessage2, "Receive Overflow!");
        Protocol_SendDebugMessage(debugMessage2);
        free(debugMessage2);
    }
    */
    //FreeRunningTimer_DelayMicroseconds(10);  // Give SPI enough time to finish transmission
    SS_VAL = 1;               // End SPI Transaction
    unsigned short result = SPI2BUF & 0x3FFF;   // Trash variable
    SS_VAL = 0;               // Begin second SPI transaction
    SPI2BUF = 0xC000;
    while(!SPI2STATbits.SPIRBF) {};
    SS_VAL = 1;
    result = SPI2BUF & 0x3FFF;
    return result;  // 14-bit value
}

/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/



/*******************************************************************************
 * TEST BENCH                                                          *
 ******************************************************************************/


#if DEBUG_ROTARYENCODER

int main()
{
    BOARD_Init();
    Protocol_Init(115200);
    RotaryEncoder_Init(ENCODER_BLOCKING_MODE);
    
    unsigned char RE_Value[3];
    RE_Value[0] = ID_ROTARY_ANGLE;
    
    char* debugMessage = (char*)malloc(128);
    sprintf(debugMessage, "Lab 2 Rotary Encoder Test. Compiled on: %s at %s", __DATE__, __TIME__);
    Protocol_SendDebugMessage(debugMessage);
    
    unsigned short currentEncoderValue = 0;    // updated on every loop
    unsigned short priorEncoderValue   = 0;    // updated when value changes from current by 10 or more

    while(1)
    {
        // Read up-to-date angle value from encoder
        currentEncoderValue = RotaryEncoder_ReadRawAngle();
        if(abs(currentEncoderValue - priorEncoderValue) >= 25)   // change in value reaches threshold for console update
        {
            priorEncoderValue = currentEncoderValue;  // priorEncoderValue is placeholder so currentEncoderValue is not changed by below code
            RE_Value[2] = (unsigned char)priorEncoderValue;
            priorEncoderValue = priorEncoderValue >> 8;
            RE_Value[1] = (unsigned char)priorEncoderValue;
            Protocol_SendPacket(0x3, ID_ROTARY_ANGLE, &RE_Value);
            priorEncoderValue = currentEncoderValue;  // now, priorEncoderValue will actually represent its namesake
        }
    }
    
    
    /*
    while(1)
    {
        memset(debugMessage, 0, 128);
        currentEncoderValue = RotaryEncoder_ReadRawAngle();
        sprintf(debugMessage, "Angle Reading: %i", (unsigned int)currentEncoderValue);
        Protocol_SendDebugMessage(debugMessage);
    }
     */
    
    
}

#endif    /* DEBUG_ROTARYENCODER */