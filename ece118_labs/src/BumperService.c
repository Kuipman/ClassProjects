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

/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/

void Debug_BumperChangeHandler(uint8_t BumperChange);

/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                    *
 ******************************************************************************/

static uint8_t MyPriority;         // priority of 0 - 8
static uint8_t lastBumperValue;    // lower 4-bits indicate high/low bumper values respectively
static uint8_t heldBumperParam;    // separate held parameter from last event checker call
static uint8_t timerRunning;       // boolean value -- high when Timer 0 is active

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
    timerRunning = FALSE;

    // post the initial transition event
    ThisEvent.EventType = ES_INIT;
    ES_Timer_InitTimer(0, 50);           // initializes timer 0, elapses after 5ms
    
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
    
    switch(ThisEvent.EventType)
    {
        case ES_INIT:
        {
            break;
        }
        case BUMPER_CHANGE:        // any bumper is pressed or released
        {
            heldBumperParam = ThisEvent.EventParam;
            if(timerRunning == FALSE)
            {
                timerRunning = TRUE;
                ES_Timer_InitTimer(0, 50);   // Start the debounce timer
            }
            break;
        }
        case ES_TIMEOUT:    // debounce timer has elapsed
        {
            timerRunning = FALSE;
            uint8_t BumperChange = (heldBumperParam ^ lastBumperValue);
            if(BumperChange)
            {
                lastBumperValue = heldBumperParam;
                //printf("\r\nBumper Event! ");
                Debug_BumperChangeHandler(BumperChange);
#if DEBUG_FSM
                ES_Event DebugEvent;
                DebugEvent.EventType = BUMPER_CHANGE;
                DebugEvent.EventParam = BumperChange;
                PostFSM(DebugEvent);   // DEBUG
#endif  /* STATEMACHINEOPS */
            }
            
        }
    }
    return ReturnEvent;
}

#endif /* BUMPER_SERVICE_V1 */

#if BUMPER_SERVICE_V2
/**
 * @Version 2
 * @brief Holds the actual Bumper Service Function, called any time a new event
 *      is passed to the respective event queue.
 *      Version 2 generates separate events depending on whether a bumper was
 *          pressed or released
 *          - Print to the terminal that an event occurred
 *          - return an event type -- in general should be ES_NO_EVENT
 *          - returns BUMPER_PRESS or BUMPER_RELEASE to the state machine
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
    
    ES_Event DebugEvent;
    
    switch(ThisEvent.EventType)
    {
        case ES_INIT:
        {
            break;
        }
        case BUMPER_CHANGE:        // any bumper is pressed or released
        {
            heldBumperParam = ThisEvent.EventParam;
            if(timerRunning == FALSE)
            {
                timerRunning = TRUE;
                ES_Timer_InitTimer(0, 50);   // Start the debounce timer
            }
            break;
        }
        case ES_TIMEOUT:    // debounce timer has elapsed
        {
            timerRunning = FALSE;
            uint8_t BumperChange = (heldBumperParam ^ lastBumperValue);
            if(BumperChange)
            {
                // if the previous bumper value was 0, this will be a bumper press event
                if(lastBumperValue == 0)
                {
                    DebugEvent.EventType = BUMPER_PRESS;
                    printf("\r\nBUMPER_PRESS Event");
                }
                // if the new bumper value is 0, this will be a bumper release event
                else if(heldBumperParam == 0)
                {
                    DebugEvent.EventType = BUMPER_RELEASE;
                    printf("\r\nBUMPER_RELEASE Event");
                }
                // for etc cases, we need to be creative
                // reads the toggled bumper, cross references with lastBumperValue
                // will be a bumper change event -- up to state machine to determine what to do
                else
                {
                    DebugEvent.EventType = BUMPER_CHANGE;
                    printf("\r\nBUMPER_CHANGE Event");
                }
                
                lastBumperValue = heldBumperParam;
                Debug_BumperChangeHandler(BumperChange);
                
                if(DebugEvent.EventType == BUMPER_PRESS || DebugEvent.EventType == BUMPER_RELEASE)
                {
                    DebugEvent.EventParam = BumperChange;
                    PostHSM(DebugEvent);
                }
                
            }
            
        }
    }
    return ReturnEvent;
}

#endif /* BUMPER_SERVICE_V2 */

/*******************************************************************************
 * PRIVATE FUNCTIONs                                                           *
 ******************************************************************************/

// Debug function -- prints out bumper changes to terminal
void Debug_BumperChangeHandler(uint8_t BumperChange)
{
    printf("\r\nBumper Event! ");
    uint8_t readValue = 0;
    
    //Bit 1
    uint8_t temp = BumperChange;
    if(temp & 0b0001)           // Front left bumper pressed
        printf("FL ");
    
    //Bit 2
    temp = BumperChange;
    if(temp & 0b0010)
        printf("FR ");
    
    //Bit 3
    temp = BumperChange;
    if(temp & 0b0100)
        printf("RL ");
    
    //Bit 4
    temp = BumperChange;
    if(temp & 0b1000)
        printf("RR");
}
