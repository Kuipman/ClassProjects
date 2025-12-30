/**
 * File: TapeAndTrackService.h
 * Project: ECE 118 - Final Project
 * Author: Nicholas Kuipers
 * 
 * @brief Header for TapeAndTrack Service function, designed to integrate in the
 *      broader ES_Framework built for ECE 118.
 *      - Since the tape sensors and track wire perform very similar functions,
 *          these are integrated into one service
 *      - When a TAPE_EVENT is called, the updated values are recorded in the lastTapeValue
 *          variable and passed as an event to the HSM service
 *      - When a TRACK_EVENT is called, the updated value is recorded in the lastTapeValue
 *          variable and passed as an event to the HSM service
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

static uint8_t MyPriority;         // priority of 0 - 8
static uint8_t lastTapeValue;      // lower 4-bits indicate high/low tape values respectively
static uint8_t lastTrackValue;     // only the lowest bit matters -- 0 or 1

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @brief Initializes the Tape and Track Service function, called automatically by the
 *      ES_Framework at the beginning of code execution.
 * @note This will post an ES_INIT event to the event queue for the Service,
 *      requiring an adequate handler within the run function
 * @param Priority - internal variable to track which event queue is used
 * @return TRUE if successful, FALSE otherwise
 */
uint8_t InitTapeAndTrackService(uint8_t Priority)
{
    ES_Event ThisEvent;

    MyPriority = Priority;

    // in here you write your initialization code
    // this includes all hardware and software initialization
    // that needs to occur.
    
    lastTapeValue  = 0;
    lastTrackValue = 0;

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
 *      queue for the Service Function.
 * @param ThisEvent - the event (a struct with "type" and "param" variables) to
 *      be posted to queue
 * @return TRUE if successful, FALSE otherwise
 */
uint8_t PostTapeAndTrackService(ES_Event ThisEvent)
{
    return ES_PostToService(MyPriority, ThisEvent);
}

/**
 * @Function RunTapeAndTrackService(ES_Event ThisEvent)
 * @Version 1
 * @brief This function is called any time a new event
 *      is passed to the respective event queue.
 *      This processes simple events from either the TAPE or TRACK event checkers.
 *          - If a TAPE_EVENT is received, the updated values are passed into a new
 *              event parameter with the name TAPE_EVENT. This is passed to the HSM.
 *          - If a TRACK_EVENT is received, the updated value is passed into a new event
 *              parameter with the name TRACK_EVENT. This is passed to the HSM
 *      Version 2 generates separate events depending on whether a bumper was
 * @param ThisEvent - the event (type and param) to be responded to
 * @return event - return event (type and param), that in general should be ES_NO_EVENT
 */
ES_Event RunTapeAndTrackService(ES_Event ThisEvent)
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
         * Called when the tape event checker detects a change in the current tape sensor values. This simply passes 
         *      the values over to the HSM
         */
        case TAPE_EVENT:
        {
            PostHSM(ThisEvent);
            break;
        }
        /*
         * Called when the track wire event checker detects a change. This simply passes the event to the HSM
         */
        case TRACKWIRE_EVENT:
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