/**
 * File: Midterm_Part5_EventChecker.h
 * Authors: Nick Kuipers
 * 
 * @brief Library of event checkers ran through by ES_Framework during a
 *      standard loop.
 */

#ifndef MIDTERM_PART5_EVENTCHECKER_H
#define	MIDTERM_PART5_EVENTCHECKER_H

/*******************************************************************************
 * PUBLIC #INCLUDES                                                            *
 ******************************************************************************/

#include "ES_Configure.h"   // defines ES_Event, INIT_EVENT, ENTRY_EVENT, and EXIT_EVENT
#include "BOARD.h"

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/


/*******************************************************************************
 * PUBLIC TYPEDEFS                                                             *
 ******************************************************************************/

/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/**
 * @Function checkEW(void)
 * @brief Checks the current EW value from the ping sensor.
 *      If there is a change in value (low to high or high to low):
 *          - If Low to High, record current value of FRT (START)
 *          - If High to Low, record current value of FRT (STOP)
 *              - Calculate distance, give return value to arbitrary service that
 *                  takes the distance information
 * @return 
 */
uint8_t checkEW(void);


#endif	/* MIDTERM_PART5_EVENTCHECKER_H */

