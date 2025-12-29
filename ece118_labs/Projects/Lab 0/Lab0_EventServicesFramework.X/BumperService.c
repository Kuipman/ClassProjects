/**
 * File: BumperService.c
 * Project: ECE 118 Lab 0, Part 5
 * Group: Group 8, Nick Kuipers & Josh Gamlen
 * 
 * @brief Source for Bumper Service function, designed to integrate in the
 *      broader ES_Framework built for ECE 118.
 *      - Version 1: Print message to the terminal indicating a bumper event occurred
 *      - Version 2: Added logic determining what bumper triggered the event and what change
 *          occurred (BUMPER_PRESSED, BUMPER_RELEASED)
 */

/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "BOARD.h"
#include "AD.h"
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BumperService.h"
#include <stdio.h>

#include <serial.h>
/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/

#define BATTERY_DISCONNECT_THRESHOLD 175

/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/

/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                    *
 ******************************************************************************/

static uint8_t MyPriority;         // priority of 0 - 8
static uint8_t lastBumperValue;    // lower 4-bits indicate high/low bumper values respectively

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @brief Initializes the Bumper Service function, called automatically by the
 *      ES_Framework at the beginning of code execution.
 * @note This will post an ES_INIT event to the event queue for the Bumper Service,
 *      requiring an adequate handler within the run function
 * @param Priority - internal variable to track which event queue is used
 * @return TRUE if successful, FALSE otherwise
 */
uint8_t InitBumperService(uint8_t Priority)
{
    ES_Event ThisEvent;

    MyPriority = Priority;

    // in here you write your initialization code
    // this includes all hardware and software initialization
    // that needs to occur.
    
    lastBumperValue = 0;

    // post the initial transition event
    ThisEvent.EventType = ES_INIT;
    //ES_Timer_InitTimer(0, 5);           // initializes timer 0, elapses after 5ms
    
    if (ES_PostToService(MyPriority, ThisEvent) == TRUE) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * @brief Wrapper function allowing for post of an event to the respective
 *      queue for the Bumper Service Function.
 * @param ThisEvent - the event (a struct with "type" and "param" variables) to
 *      be posted to queue
 * @return TRUE if successful, FALSE otherwise
 */
uint8_t PostBumperService(ES_Event ThisEvent)
{
    return ES_PostToService(MyPriority, ThisEvent);
}

#if BUMPER_SERVICE_V1
/**
 * @Version 1
 * @brief Holds the actual Bumper Service Function, called any time a new event
 *      is passed to the respective event queue.
 *      Version 1 is very simplistic. Pseudocode is as follows:
 *          - Print to the terminal that an event occurred
 *          - return an event type -- in general should be ES_NO_EVENT
 * @param ThisEvent - the event (type and param) to be responded to
 * @return event - return event (type and param), that in general should be ES_NO_EVENT
 */
ES_Event RunBumperService(ES_Event ThisEvent)
{
    ES_Event ReturnEvent;
    ReturnEvent.EventType = ES_NO_EVENT; // assume no errors

    /********************************************
     in here you write your service code
     *******************************************/
    // Pseudocode start
    //printf("\r\nBumper Event!");
    //return ES_NO_EVENT;
    
    switch(ThisEvent.EventType)
    {
        case ES_INIT:
        {
            break;
        }
        case BUMPER_CHANGE:        // any bumper is pressed or released
        {
            printf("\r\nBumper Event!");
            break;
        }
        default:
        {
            printf("\r\nService called, No Bumper Event");
        }
    }

    return ReturnEvent;
}

#endif /* BUMPER_SERVICE_V1 */

/*******************************************************************************
 * PRIVATE FUNCTIONs                                                           *
 ******************************************************************************/

