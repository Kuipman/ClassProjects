/**
 * File: Midterm_Part5.h
 * Authors: Nick Kuipers
 * 
 * @brief Library of functions that correspond to the ping sensor
 *      in part 5 of the ECE118 midterm
 */

#ifndef MIDTERM_PART5_H
#define	MIDTERM_PART5_H

/*******************************************************************************
 * PUBLIC #INCLUDES                                                            *
 ******************************************************************************/

#include "BOARD.h"

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/

/*******************************************************************************
 * PUBLIC TYPEDEFS                                                             *
 ******************************************************************************/

/*
typedef enum{
    GRAY,
    DARK,
    LIGHT
}LIGHT_STATE;
 * */

/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/**
 * @brief Initializes the Sensor pin connections (RB5 and RB4) connected to the ping
 *      sensor
 */
void PingSensor_Init();

/**
 * @brief This function uses blocking code to ping the sensor (using RB5/pin11 as
 *      the trigger pin) for 1ms (fastest we can go). Once the ping is finished we 
 *      record the current FRT value and listen on the EW output pin (RB4/pin12)
 *      until its value drops to 0. The time difference recorded here is calculated by
 *      (EW*1000)/148 and returned as a distance value
 * @param Nothing
 * @return uint8_t, distance value in inches
 */
uint8_t getPingSensorMeasurement_V1();


/**
 * @brief This version avoids the use of blocking code to perform the same functions as
 *      with V1:
 *      - Ping the sensor for 1ms (fastest we can go)
 *      - Record the current FRT value
 *      - Wait for the EW output pin to drop to 0
 *      - Calculate the resulting distance
 * @return 
 */
uint8_t getPingSensorMeasurement_V2();


#endif	/* MIDTERM_PART5_H */

