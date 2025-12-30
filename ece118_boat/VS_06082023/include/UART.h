/***
 *  @file UART.h
 *  @version 1.2
 *  @author Nicholas Kuipers
 *  @purpose Implements a UART device driver with circular buffer, intended to send and
 *      receive bytes with the ARD
 *  @note Uses notes and inspiration from instructor-provided file of same name and
 *      LibraryTemplate.h
 *  @note Repurposed from ECE 121
 */
#ifndef UART_H
#define	UART_H

/*******************************************************************************
 * PUBLIC #INCLUDES                                                            *
 ******************************************************************************/

#include "BOARD.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>     //enables use of uint8_t
#include <sys/attribs.h>
#include <xc.h>

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/

#define PBCLK          40000000    //Clock frequency of Peripheral Bus Clock is 40MHz
#define BUFFER_SIZE    16          //Circular buffer size

// For the desired test, set to 1
#define TESTBENCH_IO                0         //basic input/output test
#define TESTBENCH_CIRCBUFF          0         //circular buffer functionality

/*******************************************************************************
 * PUBLIC TYPEDEFS                                                             *
 ******************************************************************************/

/**
 * @brief Circular buffer that can track up to 16 char values. Uses a head
 *      and tail that increment upon each use to read to/write from the buffer
 *      respectively. Further, holds an isFull value to account for when the
 *      buffer is full (head = tail and all values filled)
 * @author Nicholas Kuipers
 */
typedef struct CircBuffer {
    unsigned char buffer[BUFFER_SIZE];
    int head;
    int tail;
    int isFull;               //bool flag
} CircBuffer;

/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/**
 * @brief Initializes the UART through direct manipulation of the Pic32's registers.
 *      Also sets the value for the two software circular buffers, RXBUF and TXBUF
 * 
 * @param baudrate 
 * @author Nicholas Kuipers
 */
void initializeUART(unsigned long baudrate);

/**
 * @brief Helper function that overwrites functionality of putchar(char c) function:
 *   rather than sending a char to stdout, the char is sent to the TX circular buffer.
 *  The TX interrupt is also activated.
 * @param char c, to write to TXBUF
 */
void _mon_putc(char c);

/**
 * @brief Helper function that overwrites functionality of getchar(char c) function:
 *   rather than polling for a character from a terminal (stdin), a while loop continues
 *   (thus halting the main() program, NOT interrupts) until a character is seen in the RX
 *   FIFO (thus a char was received from the UART RX).
 */
int _mon_getc (int canblock);

/**
 * @brief Places a character into the circular buffer
 * 
 * @param cB 
 * @param ch 
 * @return int -- 0 if success, 1 if error
 * @author Nicholas Kuipers
 */
int PutChar(CircBuffer* cB, char ch);

/**
 * @brief Read a character value from the circular buffer, pointed to by head
 * 
 * @param cB 
 * @return unsigned char value, or null character ('\0') if error
 * @author Nicholas Kuipers
 */
unsigned char GetChar(CircBuffer* cB);

/**
 * @brief Reads a specified character from the buffer without affecting the
 *      buffer (i.e. no adding or removing characters)
 * 
 * @param cB 
 * @return 0 for success, 1 for failure
 * @author Nicholas Kuipers
 */

unsigned char ReadChar(CircBuffer* cB, int position);

/**
 * @brief Returns whether or not there is a character in the RX circular buffer
 * @return 1 if a character exists in RXBUF, 0 otherwise
 */
int checkRXCircBuffer();

#endif	/* UART_H */

