/* 
 * @file SPI.h
 * @version 1.0
 * @author Nicholas Kuipers
 * @purpose Library allowing for a SPI interface between the PIC32 and
 *      a device connected to its respective SPI pins
 */

#ifndef SPI_H
#define SPI_H

#include "Protocol2.h"
#include "UART.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "BOARD.h"
#include <sys/attribs.h>
#include <xc.h>

/*******************************************************************************
 * PUBLIC #DEFINES                                                            *
 ******************************************************************************/

#define SPI_MAXSPEED       10000000    // Rotary Encoder max 10MHz speed
#define SPI_MODE           1           // SPI on RE operates on mode 1

// Syntax Defines -- for simpler understanding
#define MOSI_IO          TRISGbits.TRISG8
#define MOSI_VAL         LATGbits.LATG8 
#define MISO_IO          TRISGbits.TRISG7
#define MISO_VAL         PORTGbits.RG7     // use for reading the input value
#define SCK_IO           TRISGbits.TRISG6 
#define SCK_VAL          LATGbits.LATG6 
#define SS_IO            TRISDbits.TRISD4
#define SS_VAL           LATDbits.LATD4

/*******************************************************************************
 * PUBLIC TYPEDEFS
 ******************************************************************************/

typedef enum{
    COMMAND, READ, WRITE
}SPI_FrameType;

typedef struct {
    unsigned int payload;      // only uses 14 bits of the 32 bit variable
    SPI_FrameType type;
}*SPI_Frame;

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                           *
 ******************************************************************************/

/**
 * @brief Initializes the pins of the SPI Interface so the PIC32
 *      is the master connected to a slave
 * @param nothing
 * @return nothing
 * @author Nicholas Kuipers
 */
void SPI_Init();

/**
 * @brief Builds and sends a read frame to the slave.
 *      - This includes the blocking code to allow for SPI to return
 *          a frame from the slave bearing the desired information
 * @param
 * @return 0 if success, 1 if error
 * @author Nicholas Kuipers
 */
uint8_t SPI_SendReadFrame(unsigned int regValue);

/**
 * @brief Builds and sends a write frame to the slave
 * @param
 * @return 0 if success, 1 if error
 * @author Nicholas Kuipers
 */
uint8_t SPI_SendWriteFrame(unsigned int regValue);


#endif	/* SPI_H */

