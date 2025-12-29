/***
 * @file CircularBufferTest.c
 * @version 1.1
 * @author Nicholas Kuipers
 * @brief Test bench for the circular buffer
 * @note Now incorporates the Pic32
*/

/*******************************************************************************
 * #INCLUDES                                                                   *
 ******************************************************************************/
#include "UART.h"
//#include "BOARD.h"
#include <stdio.h>
//#include <sys/attribs.h>
//#include <xc.h>

/*******************************************************************************
 * TEST BENCH IMPLEMENTATION                                                   *
 ******************************************************************************/

/**
 * @brief Test bench for Circular Buffer -- runs through series of tests checking
 *      for proper results when buffer is empty, full, when wrapping is needed,
 *      and that character values are properly written to and read from the buffer.
 */
int main()
{
    BOARD_Init();
    initializeUART(115200);
    char testChar = '\0';
    int testResult = 0;
    
    //Test 1: Send one character to RXBUF, have it wrap to TXBUF, output result
    /*
     * 
     */
    
    while(1);     // END OF TESTBENCH
}

/**
 * @brief ISR for when Pic32 receives data into the Receive Shift Register (or FIFO?).
 *      U1RXIF flag is set when the RX buffer is NOT empty (i.e. at least one char was received)
 *      Pulls received data into the RXBUF via the PutChar function in the uart library
 * 
 * @note An ISR needs to resolve the condition that called it, as well as reset the
 *      respective interrupt flag
 * 
 * @param None
 * @return None
 * @author Nicholas Kuipers
 */
void __ISR(IFS0bits.U1RXIF) UART1Handler_RX(void)
{
    /* Attempts to place the received byte into the RX Buffer.
     *   If the attempt fails (i.e. the buffer is full), returns an
     *   error and drops the received character
     */
    if(PutChar(&RXBUF, U1RXREG))    //if the buffer is full
    {
        
    }
    
    //Last, reset the flag that called the interrupt
    IFS0bits.U1RXIF = 0;
}
