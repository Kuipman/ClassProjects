/***
 *  @file UART.c
 *  @version 1.2
 *  @author Nicholas Kuipers
 *  @purpose Library for uart.h -- provides a device driver that handles incoming and
 *      outgoing (RX/TX) bytes between the Pic32 and the PC
 */

/*******************************************************************************
 * #INCLUDES                                                                   *
 ******************************************************************************/

#include "UART.h"

/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/

#define DEBUG_UART 0

/*******************************************************************************
 * PRIVATE VARIABLES                                                           *
 ******************************************************************************/

// Software Circular Buffers
CircBuffer RXBUF, TXBUF;

// Conditional Flags
uint8_t TX_Collision;

/*******************************************************************************
 * PRIVATE FUNCTION DECLARATIONS                                             *
 ******************************************************************************/

int getBufferSize(CircBuffer* cB);
void IRQ_Handler_UART1_RX();
void IRQ_Handler_UART1_TX();

/*******************************************************************************
 * PUBLIC FUNCTION IMPLEMENTATIONS                                             *
 ******************************************************************************/

/**
 * @brief Initializes the UART through direct manipulation of the Pic32's registers.
 *      Also sets the value for the two software circular buffers, RXBUF and TXBUF
 * 
 * @param baudrate 
 * @author Nicholas Kuipers
 */
void initializeUART(unsigned long baudrate)
{
    //First, Clear all control registers for UART
    U1MODECLR = 0xFFFFFFFF;
    U1STACLR  = 0xFFFFFFFF;
    U1BRGCLR  = 0xFFFFFFFF;
    
    //Next, we calculate the Baud Rate Generator (BRG) Value to match our parameter 'baudrate'
    //For BR with BRGH = 1: UxBRG = (FPB/4*baudrate) - 1
    //PBCLK value defined in uart.h as 40MHz
    U1MODEbits.BRGH = 1;
    U1BRGSET = (PBCLK/(4*baudrate)) - 1;
    
    /* Now, we set UART1 for 8-N-1, Enable UART1, and Enable RX/TX
     * - 8 data bits, no parity, 1 stop bit (8-N-1) is set by default in bits 2-0 of
     *      UxMODE (value of 000 for those bits)
     * - Enabling UART is as simple as setting the ON bit (UxMODE<15>)
     * - UART Transmitter: UTXEN bit (UxSTA<10>)
     * - UART Receiver   : URXEN bit (UxSTA<12>)
     * 
     * So overall, we set UxMODE to 0x00008000 (only ON bit is set)
     *                and UxSTA  to 0x00001400
     */
    U1MODEbits.ON = 1;     //Enables UART1 by setting bit 15 (see PIC32mx340f512h.h for details)
    U1STAbits.URXEN = 1;   //Enables RX by setting bit 12 of UxSTA
    U1STAbits.UTXEN = 1;   //Enables TX by setting bit 10 of UxSTA
    
    // Set types of interrupts in UART1 registers
    U1STAbits.UTXISEL = 1;    //triggers when TX FIFO has at least one empty space 
    U1STAbits.URXISEL = 0;    //triggers when RX FIFO has data
    // Set interrupt priorities
    IPC6bits.U1IP = 4;        // RX/TX priority of 4
    IPC6bits.U1IS = 1;        // Sub-priority of 1
    //Enable the interrupts
    IEC0bits.U1RXIE = 1;
    IEC0bits.U1TXIE = 0;      // Active when TX FIFO has data
    
    //Now, initialize the respective buffer values for RX/TX
    RXBUF.head = 0;
    RXBUF.tail = 0;
    RXBUF.isFull = 0;
    TXBUF.head = 0;
    TXBUF.tail = 0;
    TXBUF.isFull = 0;
    
    //Finally, clear software flags
    TX_Collision = 0;
}

/**
* @brief Substitute function for putchar(), in stdio.h. If UART is not actively transmitting,
*  character is written directly to the RX register. Otherwise, the character is placed in the
*  software circular buffer for TX.
*
* @param c, character to be transmitted
*/
void _mon_putc(char c)
{
    if(U1STAbits.TRMT && !IEC0bits.U1TXIE)   //checks if TSR register is empty and if interrupt is inactive
        U1TXREG = c;
    else
    {
        PutChar(&TXBUF, c);
        IEC0bits.U1TXIE = 1;    //usually not necessary, but 
    }
}

/**
 * @brief Substitute function for getchar(). Function pulls a single
 *      character from the RX circular buffer.
 * @param canblock , for now this will remain unused
 * @return 
 */
int _mon_getc(int canblock)
{
    return (int)GetChar(&RXBUF);
}

/**
 * @brief Places a character into the circular buffer
 * 
 * @param cB 
 * @param ch 
 * @return int -- 0 if success, 1 if error
 * @author Nicholas Kuipers
 */
int PutChar(CircBuffer* cB, char ch)
{
    if(cB->isFull)
        return 1;          //Return an error: Buffer is already full
    if(getBufferSize(cB) >= BUFFER_SIZE - 1)
        cB->isFull = 1;    //Buffer is full after completion of function
    
    //place char in buffer at tail position, increment tail, then return success
    cB->buffer[cB->tail] = ch;
    if(cB->tail++ == BUFFER_SIZE - 1)             //checks if a wrap back to 0 is necessary
        cB->tail = 0;
    return 0;   //success
}

/**
 * @brief Read a character value from the circular buffer, pointed to by head
 * 
 * @param cB 
 * @return unsigned char value, or null character ('\0') if error
 * @author Nicholas Kuipers
 */
unsigned char GetChar(CircBuffer* cB)
{
    if(getBufferSize(cB) == 0 && !cB->isFull)  //check if the buffer is empty
        return '\0';             //returns a null character
    if(cB->isFull)                             //check if the buffer is full, resets flag if so
        cB->isFull = 0;
    
    char temp = cB->buffer[cB->head];
    if(cB->head < (BUFFER_SIZE - 1))           //check if head is less than 15
        cB->head++;
    else
        cB->head = 0;                          //wrapping condition if head equals 15    
    
    return temp;
}

/**
 * @brief Reads a specified character from the buffer without affecting the
 *      buffer (i.e. no adding or removing characters)
 * 
 * @param cB 
 * @return 0 for success, 1 for failure
 * @author Nicholas Kuipers
 */

unsigned char ReadChar(CircBuffer* cB, int position)
{    return cB->buffer[position];     }


/*******************************************************************************
 * PRIVATE FUNCTION IMPLEMENTATIONS                                            *
 ******************************************************************************/

/**
 * @brief Returns the current size of the circular buffer
 * 
 * @param cB 
 * @return integer size of the buffer
 * @author Nicholas Kuipers
 */
int getBufferSize(CircBuffer* cB)
{
    int currentSize = cB->tail - cB->head;

    //Check positive values, otherwise negative values, otherwise 0
    if(cB->isFull)
    {
        return BUFFER_SIZE - 1;
    }
    else if(currentSize > 0)
    {
        return currentSize;
    }
    else if(currentSize < 0)
    {
        return BUFFER_SIZE + currentSize;
    }
    return 0;
}

/**
 * @brief The ISR is called whenever the U1RXIF/TXIF flags are set. For brevity and readability, this
 *      function will handle the RX condition.
 *      First checks for a FIFO buffer overrun. If OERR flag is set, all characters in the FIFO are
 *          pushed to RXBUF. If RXBUF becomes full here the remaining characters are discarded. Then,
 *          OERR is cleared.
 *      Then, checks for a Framing and/or Parity Error. If either is true, the current character is discarded
 *          by getting pushed to a placeholder variable not attached to RXBUF. Then,
 *          FERR and PERR is cleared.
 *      If no errors are detected, the selected character is pushed to the RXBUF circular buffer. Since the
 *          RX interrupt flag is set whenever there is data in the FIFO, this function is called for one
 *          character at a time. The IRQ flag is then cleared. If the interrupt condition remains (i.e. more data is in the FIFO), the flag
 *          is reset and the function is called for the next character.
 * 
 * @return 
 */
void IRQ_Handler_UART1_RX()
{
    if(U1STAbits.OERR)     // Check for FIFO overrun
    {
        while(U1STAbits.URXDA && !RXBUF.isFull)                   // moves through the RX FIFO  
        {
            PutChar(&RXBUF, U1RXREG & 0xFF);  
        }
        U1STAbits.OERR = 0;                      // OERR bit is cleared manually. Any remaining data is cleared
    }
    else if(U1STAbits.FERR || U1STAbits.PERR)    // Check for Framing/Parity Error
    {
        char temp = U1RXREG & 0xFF;               // Sends bad data to a placeholder to clear up the register
        U1STAbits.FERR = 0;
        U1STAbits.PERR = 0;
    }
    else                   // Error checks passed -- Read data and push to RXBUF
    {
        PutChar(&RXBUF, U1RXREG & 0xFF);  // one character is read from the FIFO
    }
    IFS0bits.U1RXIF = 0;   // reset the RX interrupt flag
}

/**
 * @brief The ISR is called whenever the U1RXIF/TXIF flags are set. For brevity and readability, this
 *      function will handle the TX condition
 * 
 * @return 
 */
void IRQ_Handler_UART1_TX()
{
    /* Version 1.0 : When IRQ is called when there is one space left */
    //U1STAbits.UTXBF -- 1 when transmit buffer FIFO is full
    //checks that TX FIFO is not full and there is data in TXBUF
    if(getBufferSize(&TXBUF) && !U1STAbits.UTXBF)
        U1TXREG = GetChar(&TXBUF);
    else if(getBufferSize(&TXBUF) == 0)
        IEC0bits.U1TXIE = 0;    //TXBUF is empty, deactivate TX IRQ
}

/*******************************************************************************
 * INTERRUPTS                                                                 *
 ******************************************************************************/

/**
 * @brief Singular ISR called when the RX or TX interrupt flags are called
 * 
 * @param None
 * @return None
 * @author Nicholas Kuipers
 * @todo Separate this vector into two interrupts, handling RX and TX
 */
void __ISR(_UART1_VECTOR, ipl4auto) IRQHandler_UART1(void)
{
    //if(U1STAbits.URXDA)
    if(IFS0bits.U1RXIF)
        IRQ_Handler_UART1_RX();
    else if(IFS0bits.U1TXIF)
        IRQ_Handler_UART1_TX();
}

/*******************************************************************************
 * TEST BENCHES                                                                *
 ******************************************************************************/


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
        if(getBufferSize(&RXBUF))
        {
            unsigned char receivedByte = (int)getchar();
            putchar(receivedByte);
        }
        
    }
}

#endif   /*TESTBENCH_CIRCBUFF*/






