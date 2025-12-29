/***
 *  @file RotaryEncoder.h
 *  @version 1.0
 *  @author Nicholas Kuipers
 *  @purpose 
 */

#ifndef ROTARYENCODER_H
#define	ROTARYENCODER_H

#include "Protocol2.h"
#include "UART.h"
#include "FreeRunningTimer.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "BOARD.h"
#include <sys/attribs.h>
#include <xc.h>

/*******************************************************************************
 * PUBLIC #DEFINES                                                            *
 ******************************************************************************/

// Syntax Defines -- for simpler understanding
#define MOSI_IO          TRISGbits.TRISG8    // Pin 11
#define MOSI_VAL         LATGbits.LATG8  
#define MISO_IO          TRISGbits.TRISG7    // Pin 12
#define MISO_VAL         PORTGbits.RG7     // use for reading the input value
#define SCK_IO           TRISGbits.TRISG6    // Pin 13
#define SCK_VAL          LATGbits.LATG6 
#define SS_IO            TRISGbits.TRISG9    // Pin 10
#define SS_VAL           LATGbits.LATG9

#define SPI_MAXSPEED       10000000    // Rotary Encoder max 10MHz speed
#define ENCODER_BLOCKING_MODE  0
#define ENCODER_INTERRUPT_MODE 1

#define DEBUG_ROTARYENCODER    1

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                           *
 ******************************************************************************/

/**
 * @brief Initializes the rotary encoder (AS5047D)
 * @param interfaceMode, can be either blocking mode or interrupt mode as specified
 * @return 0 if SUCCESS, 1 if ERROR   */
int RotaryEncoder_Init(char interfaceMode);

/**
 * @brief Accesses the register on the Rotary Encoder via SPI
 * @return 14-bit value representing the raw encoder angle (0 - 16384) */
unsigned short RotaryEncoder_ReadRawAngle(void);


#endif	/* ROTARYENCODER_H */

