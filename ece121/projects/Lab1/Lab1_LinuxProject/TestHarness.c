/***
 *  @file TestHarness.c
 *  @version 1.0
 *  @author Nicholas Kuipers
 *  @purpose Test Harness for Parts 1 - 3 of Lab 1
 * 
 *  @note Original test harnesses were written directly
 *      in UART.c -- moved to this separate file for brevity
 */

/*******************************************************************************
 * #INCLUDES                                                                   *
 ******************************************************************************/
// User-Created Libraries
#include "UART.h"
#include "LEDs.h"         //for debugging purposes

// Board-required libraries
#include "BOARD.h"
#include <sys/attribs.h>
#include <xc.h>

// C input-output libraries
#include <stdio.h>
#include <stdlib.h>

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/

// For testing, please only select one at a time
#define TEST_PART1              0
#define TEST_PART2              0

/*******************************************************************************
 * TEST BENCHES                                                                *
 ******************************************************************************/

/**
 * @brief Tests the input/output capabilities of the UART driver through use of a serial
 *      monitor. Does not use buffers or interrupts -- merely checks basic RX/TX functionality
 * @author Nicholas Kuipers
 */
#if TEST_PART1
int main()
{
    BOARD_Init();
    initializeUART(115200);
    IEC0bits.U1RXIE = 0;      // Interrupts not used for part 1
    
    while(1)
    {
        if(U1STAbits.URXDA)     //URXDA is asserted whenever the receive buffer has data
        {
            U1TXREG = U1RXREG;  //loop the data in RX into the TX register
        }
    }
    
    BOARD_End();
    while(1);
}
#endif /*TEST_PART1*/

/**
 * @brief Part 2 demonstrates RX/TX interrupt functionality. This function stands by
 *      for a value to be received by the RX FIFO. When this occurs, the value is immediately
 *      placed by the RX Interrupt into the RX Circular Buffer. The main loop here checks for
 *      any data in the RX circular buffer -- when this is true, one character from the RX
 *      circular buffer is moved to the TX circular buffer and the TX interrupt is activated
 *      so the resulting data can be sent
 * @return 
 */
#if TEST_PART2
int main()
{
    BOARD_Init();
    initializeUART(115200);
    
    while(1)
    {
        if(currentBufferSize('R'))
        {
            moveData_PART2TEST();
        }
        
    }
}

#endif   /*TEST_PART2*/


//////////////////////////////////?************************************

/**
 * @brief Tests the input/output capabilities of the UART driver through use of a serial
 *      monitor. Does not use buffers or interrupts -- merely checks basic RX/TX functionality
 * @author Nicholas Kuipers
 */
#if TESTBENCH_IO
int main()
{
    BOARD_Init();
    initializeUART(115200);
    IEC0bits.U1RXIE = 0;      // Interrupts not used for part 1
    
    while(1)
    {
        if(U1STAbits.URXDA)     //URXDA is asserted whenever the receive buffer has data
        {
            U1TXREG = U1RXREG;  //loop the data in RX into the TX register
        }
    }
    
    BOARD_End();
    while(1);
}
#endif /*TESTBENCH_IO*/

/**
 * @brief Demonstrates RX/TX interrupt functionality: Main function stands by for a value to be received by the RX FIFO.
 *      When this occurs, RX interrupt places the value into the RX circular buffer.
 *      Once the RX circular buffer is full, all characters are moved into the TX circular buffer and the TX interrupt is activated.
 *      The TX interrupt will pull characters from the TX circular buffer into the TX FIFO until the circular buffer is empty,
 *      in which case the TX interrupt is again deactivated.
 */
#if TESTBENCH_CIRCBUFF
int main()
{
    BOARD_Init();
    initializeUART(115200);
    
    while(1)
    {
        if(currentBufferSize('R'))
        {
            moveData_PART2TEST();
        }
        
    }
}

#endif   /*TESTBENCH_CIRCBUFF*/