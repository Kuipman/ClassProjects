/**
 * File: LightService.c
 * Project: ECE 118 Lab 0, Part 5
 * Group: Group 8, Nick Kuipers & Josh Gamlen
 * 
 * @brief Source for Light Service function, designed to integrate in the
 *      broader ES_Framework built for ECE 118.
 *      - Version 1: Print message to the terminal indicating a light event occurred
 */

/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "BOARD.h"
#include "AD.h"
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "LightService.h"
#include <stdio.h>

#include <serial.h>
/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/

/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/

/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                    *
 ******************************************************************************/

static uint8_t MyPriority;            // priority of 0 - 8
static LIGHT_STATE lastLightState;    // either LIGHT or DARK

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @brief Initializes the light service function. This function is called automatically
 *      by the ES_FRAMEWORK at the beginning of code execution.
 * @param Priority - internal variable tracking which event queue is used
 * @return TRUE if successful, FALSE otherwise
 */
uint8_t InitLightService(uint8_t Priority)
{
    ES_Event ThisEvent;

    MyPriority = Priority;

    // in here you write your initialization code
    // this includes all hardware and software initialization
    // that needs to occur.
    
    lastLightState = DARK;       // Initialize in "dark location" -- will transition if starts in light

    // post the initial transition event
    ThisEvent.EventType = ES_INIT;
    
    if (ES_PostToService(MyPriority, ThisEvent) == TRUE) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * @brief Wrapper function allowing for post of an event to the respective
 *      queue for the Light Service Function.
 * @param ThisEvent - the event (a struct with "type" and "param" variables) to
 *      be posted to queue
 * @return TRUE if successful, FALSE otherwise
 */
uint8_t PostLightService(ES_Event ThisEvent)
{
    return ES_PostToService(MyPriority, ThisEvent);
}

#if LIGHT_SERVICE_V1
/**
 * @brief Holds the actual Light Service Function, called any time a new event
 *      is passed to the respective event queue.
 *      Version 1 is very simplistic. Pseudocode is as follows:
 *          - Print to the terminal if an event occurs that is different than the previous event
 *              - i.e. DARK to LIGHT or LIGHT to DARK
 *          - return an event type -- in general should be ES_NO_EVENT
 * @param ThisEvent - the event (type and param) to be responded to
 * @return event - return event (type and param), that in general should be ES_NO_EVENT
 */
ES_Event RunLightService(ES_Event ThisEvent)
{
    ES_Event ReturnEvent;
    ReturnEvent.EventType = ES_NO_EVENT; // assume no errors

    /********************************************
     in here you write your service code
     *******************************************/
    
    ES_Event HSM_Event;
    switch(ThisEvent.EventType)
    {
        case ES_INIT:
        {
            break;
        }
        case LIGHTLEVEL:
        {
            if(ThisEvent.EventParam == lastLightState)
                break;
            else
            {
                lastLightState = ThisEvent.EventParam;
                printf("\r\nLight Change Event!");    // DEBUG
                HSM_Event.EventType = LIGHTLEVEL;
                HSM_Event.EventParam = ThisEvent.EventParam;
                PostHSM(HSM_Event);  // Sends new light value to FSM
                break;
            }
        }
        default:
        {
            printf("\r\nService called but No Light Event");
        }
    }

    return ReturnEvent;
}

#endif /* LIGHT_SERVICE_V1 */

/*******************************************************************************
 * PRIVATE FUNCTIONs                                                           *
 ******************************************************************************/

