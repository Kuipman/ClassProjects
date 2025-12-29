/***
 *  @file FreeRunningTimer.h
 *  @version 1.0
 *  @author Nicholas Kuipers
 *  
 *  @brief Utilizes Timer5 (a "Type B timer") in the Pic32 to create a free running timer that runs at the rate of
 *    microseconds. Allows for the return of 32-bit unsigned int values depicting the current millisecond and microsecond values
 *    tracked in the system.
*/


#ifndef FREERUNNINGTIMER_H
#define	FREERUNNINGTIMER_H

#include "Protocol2.h"
#include "BOARD.h"
#include <stdint.h>
#include <sys/attribs.h>
#include <xc.h>

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/

#define DEBUG_FRT        0       // set to activate main() in testbench

/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/**
 * @brief Initializes Timer5 to be a free running timer that generates an interrupt on every
 *    millisecond (i.e. when the respective value in the Period Register is reached)
 * @param  none
 * @return none
 * @author Nicholas Kuipers
 */ 
void FreeRunningTimer_Init(void);

/**
 * @brief Returns a 32-bit value depicting the current millisecond counter value tracked
 *    by the system
 * @param None
 * @return current value in milliseconds tracked by the system
   */
unsigned int FreeRunningTimer_GetMilliSeconds(void);

/**
 * @brief Returns a 32-bit value depicting the current microsecond counter value tracked
 *    by the system
 * @param None
 * @return current value in microseconds tracked by the system
   */
unsigned int FreeRunningTimer_GetMicroSeconds(void);
#endif	/* FREERUNNINGTIMER_H */

