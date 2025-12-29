/**
 * File: Midterm_Part5_EventChecker.c
 * Authors: Nick Kuipers
 * 
 * @brief Library of event checkers ran through by ES_Framework during a
 *      standard loop.
 */

#include <stdio.h>
#include "Midterm_Part5_EventChecker.h"
#include "ES_Configure.h"
#include "ES_Events.h"
#include "serial.h"
#include "AD.h"
#include "roach.h"

/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                    *
 ******************************************************************************/

/*******************************************************************************
 * PRIVATE FUNCTIONS                                                            *
 ******************************************************************************/

// Returns a high value if Pin is asserted high and 0 otherwise
uint8_t readEWPin()
{
    if(PORTB & 0x800)    // will be asserted high if there is a high voltage on the EW pin
        return 0xFF;
    else
        return 0;
}

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
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
uint8_t checkEW(void)
{
    static int FRT_Start = 0;
    static int FRT_Stop  = 0;
    static uint8_t lastValue_EW = 0;
    ES_Event ThisEvent;
    
    if(readEWPin() != lastValue_EW)
    {
        if(lastValue_EW == 0)     // Low to High Change
        {
            FRT_Start = ReadTimer1();   // reads with accuracy of 25us
            lastValue_EW = 0xFF;
            return FALSE;
        }
        else
        {
            FRT_Stop = ReadTimer1();    // reads with accuracy of 25us
            lastValue_EW = 0;
            
            int distance = FRT_Stop - FRT_Start;   // time elapsed during EW high
            distance = (distance*25)/148;    // accuracy within 25us
            
            ES_Timer_InitTimer(1, 100);    // this kicks off the next ping in 100ms
            
            /*
             * At this point the minimum requirements are met for part (c).
             *  For brevity, the below code sends the distance to some arbitrary service
             *  that will make use of the information.
             */
            ThisEvent.EventType = PING_DISTANCE;
            ThisEvent.EventParam = distance;
            PostARBITRARYService(ThisEvent);
            return TRUE;
        }
    }
    else
        return FALSE;
}