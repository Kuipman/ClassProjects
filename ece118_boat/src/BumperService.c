/**
 * File: BumperService.h
 * Project: ECE 118 - Final Project
 * Author: Nicholas Kuipers
 * 
 * @brief Header for Bumper Service function, designed to integrate in the
 *      broader ES_Framework built for ECE 118.
 *      - Service determines what bumper triggered the BUMPER_EVENT and what change occurred
 *          (BUMPER_PRESSED, BUMPER_RELEASED)
 */

/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "BOARD.h"
#include "BOAT.h"
#include "AD.h"
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BumperService.h"
#include "BOAT_HSM.h"
#include <stdio.h>

#include <serial.h>
/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/

/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/

void Debug_BumperChangeHandler(uint8_t BumperChange);
ES_EventTyp_t eventHelper_Bumpers(uint16_t eventParam);

/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                    *
 ******************************************************************************/

static uint8_t MyPriority;         // priority of 0 - 8
static uint8_t lastBumperValue;    // lower 4-bits indicate high/low bumper values respectively
static uint8_t holdingBumperParam;    // separate held parameter from last event checker call
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

/**
 * @Function RunBumperService(ES_Event ThisEvent)
 * @Version 2
 * #param ThisEvent
 * @brief Function is called any time a new event is passed to the respective event queue (handled
 *      by ES_Framework).
 *      - Past init, the function is called by either a BUMPER_EVENT (from the bumper event) or
 *          TIMER_EXPIRY.
 *          - BUMPER_EVENT: On first call the passed parameter values are taken in to a heldBumperParam. If
 *              the timer flag is FALSE and the heldBumperParam is different than the lastBumperValue, lastBumperValue = held, the function
 *              posts the event to the HSM, sets the timer flag to TRUE, and starts the debounce timer. While the timer
 *              flag is TRUE, any further function calls with BUMPER_EVENT are ignored
 *          - TIMER_EXPIRY: The timer flag is set back to FALSE. Check that a separate bumper event didn't occur. If it did,
 *              call the service again
 * @param ThisEvent
 * @return 
 */
ES_Event RunBumperService(ES_Event ThisEvent)
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
         * When first called, this posts the current bumper values to the HSM. A debounce timer is called
         *      and future calls with BUMPER_EVENT are ignored until the timer expires
         */
        case BUMPER_EVENT:
        {
            holdingBumperParam = ThisEvent.EventParam;   // records current bumper values in a holding variable
            if(timerRunning == FALSE)
            {
                if(lastBumperValue != holdingBumperParam)   // nested for loop, filtering out extraneous edge-cases
                {
                    lastBumperValue = holdingBumperParam;
                    StateEvent.EventParam = holdingBumperParam;
                    // determine the event to send to HSM depending on parameter received
                    StateEvent.EventType = eventHelper_Bumpers(ThisEvent.EventParam);
                    // Pass the event to the state machine
                    PostHSM(StateEvent);
                    // Start the timer and set flag to TRUE
                    timerRunning = TRUE;
                    ES_Timer_InitTimer(0, 50);   // Start the 50ms debounce timer
                }
            }
            break;
        }
        case ES_TIMEOUT:
        {
            timerRunning = FALSE;      // debounce timer expired, clear flag for next bumper value
            if(lastBumperValue != holdingBumperParam)  // catcher in event a separate bumper event occurred during debounce timer
            {
                StateEvent.EventType = BUMPER_EVENT;
                StateEvent.EventParam = holdingBumperParam;
                PostBumperService(StateEvent);
            }
        }
    }
    return ReturnEvent;
}

#if COMMENT_OUT
/**
 * @Version 1
 * @brief Holds the actual Bumper Service Function, called any time a new event
 *      is passed to the respective event queue.
 *      Version 1 generates separate events depending on whether a bumper was
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
    
    ES_Event StateEvent;
    
    switch(ThisEvent.EventType)
    {
        case ES_INIT:
        {
            break;
        }
        /*
         * Called when any bumper is pressed or released. On first call, inits a debounce timer
         *  (timer2) for 50ms. During this time future calls have their parameter recorded, and nothing else.
         */
        case BUMPER_EVENT:
        {
            holdingBumperParam = ThisEvent.EventParam;   // updated on each call
            if(timerRunning == FALSE)
            {
                timerRunning = TRUE;
                ES_Timer_InitTimer(0, 50);   // Start the debounce timer.
            }
            break;
        }
        /*
         * Called upon expiry of debounce timer. Compares the most recent bumper parameter from above with
         *  the prior values tracked in the library for the previous bumper values. If this results in a difference:
         *      - If the bumpers were all previously 0, a Bumper Press event occurred. 
         *      - If the held parameter is 0, a Bumper Release event occurred
         *      - If neither value is 0, a Bumper Change occurred. This will fall to the state machine to
         *          decide what to do. 
         */
        case ES_TIMEOUT:
        {
            timerRunning = FALSE;
            uint8_t BumperChange = (holdingBumperParam ^ lastBumperValue);
            if(BumperChange)
            {
                // if the previous bumper value was 0, this will be a bumper press event
                if(lastBumperValue == 0)
                {
                    StateEvent.EventType = BUMPER_PRESS;
                    printf("\r\nBUMPER_PRESS Event");
                }
                // if the new bumper value is 0, this will be a bumper release event
                else if(holdingBumperParam == 0)
                {
                    StateEvent.EventType = BUMPER_RELEASE;
                    printf("\r\nBUMPER_RELEASE Event");
                }
                // for etc cases, we need to be creative
                // reads the toggled bumper, cross references with lastBumperValue
                // will be a bumper change event -- up to state machine to determine what to do
                else
                {
                    StateEvent.EventType = BUMPER_EVENT;
                    printf("\r\nBUMPER_CHANGE Event");
                }
                
                lastBumperValue = holdingBumperParam;
                //Debug_BumperChangeHandler(BumperChange);
                StateEvent.EventParam = BumperChange;
                PostHSM(StateEvent);

                /*
                if(StateEvent.EventType == BUMPER_PRESS || StateEvent.EventType == BUMPER_RELEASE)
                {
                    StateEvent.EventParam = BumperChange;
                    //PostHSM(DebugEvent);     // commented due to bug (NK 20230605)
                }
                 * */
                
            }  
        }
    }
    return ReturnEvent;
}
#endif

/*******************************************************************************
 * HELPER FUNCTIONs                                                           *
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

// What kind of event to post to HSM?
ES_EventTyp_t eventHelper_Bumpers(uint16_t eventParam)
{
    // Up to this point we have determined the eventParam is a different value than the last Bumper
    // Value recorded. So, we simply determine whether a bumper was pressed or released
    
    if(lastBumperValue == 0)    // if the previous value was 0, then a bumper has to have been pressed
    {
        return BUMPER_PRESS;
    }
    if(eventParam == 0)         // if the current value is 0, then a pressed bumper was released
    {
        return BUMPER_RELEASE;
    }
    
    return BUMPER_CHANGE;
}
