/***
 *  @file RotaryEncoder.h
 *  @version 1.0
 *  @author Nicholas Kuipers
 *  @purpose 
 */

#ifndef ROTARYENCODER_H
#define	ROTARYENCODER_H

#include "SPI.h"

/*******************************************************************************
 * PUBLIC #DEFINES                                                            *
 ******************************************************************************/

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

