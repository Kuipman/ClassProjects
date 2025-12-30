/**
 * File: BeaconService.h
 * Project: ECE 118 - Final Project
 * Author: Nicholas Kuipers
 * 
 * @brief Header for Beacon Service function, designed to integrate in the
 *      broader ES_Framework built for ECE 118.
 *      - Both the 2k and 1.5k beacons are tied to this service, so this first
 *          differentiates which event (BEACON_EVENT_2K or BEACON_EVENT_1_5K) called it
 *      - Passes the respective parameter as a separate event with parameter to the HSM 
 */

/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "BOARD.h"
#include "BOAT.h"
#include "AD.h"
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "TapeAndTrackService.h"
#include "BOAT_HSM.h"
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
static uint8_t lastBeaconValue_2k;    // is either high or low
static uint8_t lastBeaconValue_1_5k;  // is either high or low

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @brief Initializes the Beacon Service function, called automatically by the
 *      ES_Framework at the beginning of code execution.
 * @note This will post an ES_INIT event to the event queue for the Bumper Service,
 *      requiring an adequate handler within the run function
 * @param Priority - internal variable to track which event queue is used
 * @return TRUE if successful, FALSE otherwise
 */
uint8_t InitBeaconService(uint8_t Priority)
{
    ES_Event ThisEvent;

    MyPriority = Priority;

    // in here you write your initialization code
    // this includes all hardware and software initialization
    // that needs to occur.
    
    lastBeaconValue_2k   = 0;
    lastBeaconValue_1_5k = 0;

    // post the initial transition event
    ThisEvent.EventType = ES_INIT;
    //ES_Timer_InitTimer(0, 50);           // initializes timer 0, elapses after 5ms
    
    if (ES_PostToService(MyPriority, ThisEvent) == TRUE) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * @brief Wrapper function allowing for post of an event to the respective
 *      queue for the Service Function.
 * @param ThisEvent - the event (a struct with "type" and "param" variables) to
 *      be posted to queue
 * @return TRUE if successful, FALSE otherwise
 */
uint8_t PostBeaconService(ES_Event ThisEvent)
{
    return ES_PostToService(MyPriority, ThisEvent);
}

/**
 * @Version 1
 * @brief Function is called any time a new event
 *      is passed to the respective event queue.
 *      Version 1 simply takes in the respective event and passes it onto the HSM
 * 
 * @param ThisEvent - the event (type and param) to be responded to
 * @return event - return event (type and param), that in general should be ES_NO_EVENT
 */
ES_Event RunBeaconService(ES_Event ThisEvent)
{
    ES_Event ReturnEvent;
    ReturnEvent.EventType = ES_NO_EVENT; // assume no errors

    /********************************************
     in here you write your service code
     *******************************************/
    
    ES_Event StateEvent;
    
    switch(ThisEvent.EventType)
    {
        case ES_INIT:
        {
            break;
        }
        /*
         * Simply takes the 2k event and passes it to the HSM
         */
        case BEACON_EVENT_2K:
        {
            PostHSM(ThisEvent);
            break;
        }
        /*
         * Simply takes the 1.5k event and passes it to the HSM
         */
        case BEACON_EVENT_1_5K:
        {
            PostHSM(ThisEvent);
            break;
        }
    }
    return ReturnEvent;
}

/*******************************************************************************
 * PRIVATE FUNCTIONs                                                           *
 ******************************************************************************/
