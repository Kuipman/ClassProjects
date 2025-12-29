/* 
 * @file SPI.c
 * @version 1.0
 * @author Nicholas Kuipers
 * @purpose Test file ensuring SPI-based functions build and "send" frames properly.
 * @note Only simulates SPI -- not built to handle an actual SPI connection
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>

/*******************************************************************************
 * PUBLIC TYPEDEFS
 ******************************************************************************/

typedef enum{
    READ, WRITE
}SPI_FrameType;

/*******************************************************************************
 * GLOBAL VARIABLES                                                            *
 ******************************************************************************/

//SPI_Frame rxFrame, txFrame;
//unsigned int rxFrame, txFrame;

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                           *
 ******************************************************************************/

/**
 * @brief "Initializes SPI interface" -- essentially just defines values for declared global variables
 * @param Nothing
 * @return Nothing
 * @author Nicholas Kuipers
 */
void SPI_Init()
{
    //rxFrame = malloc(sizeof(SPI_Frame));
    //txFrame = malloc(sizeof(SPI_Frame));
    //rxFrame = (unsigned int) malloc(sizeof(int));
    //rxFrame = (unsigned int) malloc(sizeof(int));
}

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

    while(payload != 0)
    {
        if(payload & 0x1)      // returns TRUE if the LSB is a 1
            counter++;
        payload = payload >> 1; // payload value is left shifted to next bit
    }       
    if(counter % 2)             // if this returns a 0, counter is even
        return 1;               // SPI word is already even, parity bit is 0
    else
        return 0;               // SPI word is odd, parity bit is 1 to make this even
}

/**
 * @brief Builds and returns a command frame to the system.
 *      Command frames are structured as follows (from MSB to LSB):
 *          - Bit 15 : Parity bit, even (0), calculated on lower 15 bits of command frame
 *          - Bit 14 : denotes following frame - 0 for write, 1 for read
 *          - Bits <13:0> : Address in the RE to read or write
 * @param unsigned int, address on RE to be accessed by following command
 * @param type of frame that will follow the command frame
 * @return complete command frame, or 0 for error
 * @author Nicholas Kuipers
 */
unsigned int SPI_BuildCommandFrame(unsigned int address, SPI_FrameType type)
{
    unsigned int frame = address;
    if(type == READ)
        frame |= 0x4000;     // set bit 14 to 1
    if(SPI_CalcParityBit(frame))
        frame |= 0x8000;     // parity bit (bit 15) set to 1
    
    return frame;
}

/**
 * @brief Builds and returns a write frame to the system
 *      Write Frames are structured as follows:
 *          - Bit 15 : Parity bit, even
 *          - Bit 14 : Command Frame Error bit (set by RE hardware -- we're ignoring this)
 *          - Bit <13:0> : Data to write to register specified by address parameter sent in
 *              command frame
 * @param data, to be written to register specified by preceding command frame
 * @return full write frame as an unsigned int
 * @author Nicholas Kuipers
 */
unsigned int SPI_BuildWriteFrame(unsigned int data)
{
    unsigned int frame = data;
    if(SPI_CalcParityBit(frame))
        frame |= 0x8000;
    return frame;
}

/**
 * @brief Builds and sends a command frame, then a write frame, to the slave (RE).
 *      Calls the BuildCommandFrame() function for the command frame.
 *      The Write Frame is structured as follows:
 *          - Bit 15 : Parity bit, even
 *          - Bit 14 : Command Frame Error bit (set by RE hardware -- we're ignoring this)
 *          - Bit <13:0> : Data to write to register specified by address parameter sent in
 *              command frame
 * @param address, register on RE to be written to
 * @param writeValue, to be written to register specified at address
 * @return 0 for success, 1 for error
 * @author Nicholas Kuipers 
 */
uint8_t SPI_SendWriteFrame(unsigned int address, unsigned int writeValue)
{
    unsigned int sendFrame = SPI_BuildCommandFrame(address, WRITE);
    // open SPI connection
    // send this frame over SPI connection
    sendFrame = SPI_BuildWriteFrame(writeValue);
    // send this frame over SPI connection
    // terminate SPI connection
    return 0;  // SUCCESS
}

/**
 * @brief Primary driver module for sending individual bits from a frame through
 *      SPI to a distant device (for our purposes: the Rotary Encoder).
 *      Things to note:
 *          - The Rotary Encoder reads MSB to LSB, meaning we need to send a frame from left to right
 *          - Blocking code occurs here -- getMicroSeconds() from FRT library is constantly called to check that
 *              0.1 us (10MHz) have passed <<<<<<WE NEED A DIFFERENT SOLUTION>>>>>>>>>>>>>>
 *      
 *      Process:
 *          - First check if the SS was pulled low. If it is high, return a 1 for error (this relies on
 *              the pin being pulled low prior to function call)
 *          - for loop: over the course of 16 bits from high to low (int i = 15, i--)
 *              - if some value bitwise anded with selected bit returns a nonzero value:
 *                  - send a 1 over SPI  (pull MOSI high)
 *              - else
 *                  - send a 0 over SPI  (pull MOSI low)
 * 
 */
uint8_t SPI_TransmitFrame(unsigned int frame)
{

}



/*******************************************************************************
 * TEST BENCH                                                                  *
 ******************************************************************************/

int main()
{
    // First, initialize everything needed for test bench purposes
    SPI_Init();
    unsigned int testValue = 0;
    unsigned int testResult = 0;

    // Introduction
    printf("SPI Function Test Bench\n");

    // Test 1.1: Calculate the Parity Bit for several payload values
    printf("\nTest 1: CalcParityBit() Functionality\n");
    printf("Test 1.1: Odd payload value, should return a parity bit of 1\n");
    testValue  = 0b0011011001101000;           // Odd payload value
    //rxFrame->payload = testValue;
    //rxFrame = testValue;
    testResult = SPI_CalcParityBit(testValue);    // should return a 1 to offset the odd payload
    if(testResult)
        printf("Test 1.1 Success! Parity bit = %i\n", testResult);
    else
        printf("Test 1.1 Failed. Parity bit = %i\n", testResult);
    
    printf("\nTest 1.2: Even payload value, should return a parity bit of 0\n");
    testValue = 0b0010110011100011;            // Even payload value
    //rxFrame->payload = testValue;
    testResult = SPI_CalcParityBit(testValue);    // should return a 0
    if(testResult == 0)
        printf("Test 1.2 Success! Parity bit = %i\n", testResult);
    else
        printf("Test 1.2 Failed. Parity bit = %i\n", testResult);

    printf("\nTest 2: BuildCommandFrame() Functionality\n");
    printf("Input value: 0x0003 for a READ frame. Expected value: 0xC003 (parity = 1, RWE = 1)\n");
    testResult = SPI_BuildCommandFrame(0x0003, READ);   //should return a 0xC003
    if(testResult == 0xC003)
        printf("Test 2 Success!\n");
    else   
        printf("Test 2 Failed.\n");
    printf("\nTest 2.1: Input value: 0x0007 for a READ frame. Expected value: 0x4007 (Parity = 0, RWE = 1)\n");
    testResult = SPI_BuildCommandFrame(0x0007, READ);    // should return 0x4007
    if(testResult == 0x4007)
        printf("Test 2.1 Success!\n");
    else   
        printf("Test 2.1 Failed.\n");

    printf("\nTest 3: BuildWriteFrame() Functionality\n");
    printf("Test 3.1: Data to write = 0x1004\n");
    testResult = SPI_BuildWriteFrame(0x1004);
    if(testResult == 0x1004)     // Parity bit = 0
        printf("Test 3.1 Success!\n");
    else
        printf("Test 3.1 Failed.\n");
    
    printf("\nTest 3.2: Data to write = 0x3004\n");
    testResult = SPI_BuildWriteFrame(0x3004);
    if(testResult == 0xB004)
        printf("Test 3.2 Success!\n");
    else
        printf("Test 3.2 Failed.\n");
    





    return 0;
}


