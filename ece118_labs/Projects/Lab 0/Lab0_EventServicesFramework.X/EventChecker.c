/**
 * File: EventChecker.c
 * Project: ECE 118 - Lab 0 Part 5
 * Authors: Josh Gamlen, Nick Kuipers
 * 
 * @brief Library of event checkers ran through by ES_Framework during a
 *      standard loop. For part 5, event checkers are:
 *      - Check of any bumper interaction -- which bumper does not matter
 *      - Check for any discrete change in light level
 */

/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/
#include <stdio.h>

#include "EventChecker.h"
#include "ES_Configure.h"
//#include "TemplateEventChecker.h"
#include "ES_Events.h"
#include "serial.h"
#include "AD.h"
#include "roach.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
#define BATTERY_DISCONNECT_THRESHOLD 175

#define BUMPER_V1   1
#define BUMPER_V2   0

/*******************************************************************************
 * EVENTCHECKER_TEST SPECIFIC CODE                                                             *
 ******************************************************************************/

//#define EVENTCHECKER_TEST
#ifdef EVENTCHECKER_TEST
#include <stdio.h>
#define SaveEvent(x) do {eventName=__func__; storedEvent=x;} while (0)

static const char *eventName;
static ES_Event storedEvent;
static ES_Event lastBumper;
#endif

/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this EventChecker. They should be functions
   relevant to the behavior of this particular event checker */

/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                    *
 ******************************************************************************/

/* Any private module level variable that you might need for keeping track of
   events would be placed here. Private variables should be STATIC so that they
   are limited in scope to this module. */

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function TemplateCheckBattery(void)
 * @param none
 * @return TRUE or FALSE
 * @brief This function is a prototype event checker that checks the battery voltage
 *        against a fixed threshold (#defined in the .c file). Note that you need to
 *        keep track of previous history, and that the actual battery voltage is checked
 *        only once at the beginning of the function. The function will post an event
 *        of either BATTERY_CONNECTED or BATTERY_DISCONNECTED if the power switch is turned
 *        on or off with the USB cord plugged into the Uno32. Returns TRUE if there was an 
 *        event, FALSE otherwise.
 * @note Use this code as a template for your other event checkers, and modify as necessary.
 * @author Gabriel H Elkaim, 2013.09.27 09:18
 * @modified Gabriel H Elkaim/Max Dunne, 2016.09.12 20:08 */
uint8_t TemplateCheckBattery(void) {
    static ES_EventTyp_t lastEvent = BATTERY_DISCONNECTED;
    ES_EventTyp_t curEvent;
    ES_Event thisEvent;
    uint8_t returnVal = FALSE;
    uint16_t batVoltage = AD_ReadADPin(BAT_VOLTAGE); // read the battery voltage

    if (batVoltage > BATTERY_DISCONNECT_THRESHOLD) { // is battery connected?
        curEvent = BATTERY_CONNECTED;
    } else {
        curEvent = BATTERY_DISCONNECTED;
    }
    if (curEvent != lastEvent) { // check for change from last time
        thisEvent.EventType = curEvent;
        thisEvent.EventParam = batVoltage;
        returnVal = TRUE;
        lastEvent = curEvent; // update history
#ifndef EVENTCHECKER_TEST           // keep this as is for test harness
        //PostGenericService(thisEvent);
#else
        SaveEvent(thisEvent);
#endif   
    }
    return (returnVal);
}

#if BUMPER_V1
/**
 * @Function checkBumpers()
 * @brief Checks for a bumper event -- was one of the bumpers pressed?
 *      - Cross-reference these values with the previous bumper values (set a "change" flag if they're different)
 *      - Conversion - 4-bit value depicting the bits that changed (XOR)
 *      - If the flag is set to true
 *          - set flag false
 *          - post event
 *              - if/else that generate individual events depending on bits that are different (0110)
 *          - sets lastBumperValues = currentbumperValues
 *          - return TRUE
 *      - return FALSE
 * @version 1 -- no debouncing included
 * @param
 * @return TRUE if bumper state change, FALSE otherwise
 */
uint8_t checkBumpers(void)
{
    unsigned char bump = Roach_ReadBumpers();
    ES_Event ThisEvent;
    if(bump)            // if any bumper is pressed, returns an event
    {
        //printf("\r\nA bumper is pressed!");
        ThisEvent.EventType = BUMPER_CHANGE;
        //ThisEvent.EventParam = bump;
        PostBumperService(ThisEvent);
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

#endif  /* BUMPER_V1 */

/**
 * @Function checkLight(void)
 * @brief Check the current light value, read by the light sensor on robot
 *      - Declare an enum (DARK, LIGHT) to record the previous light state (global variable).
 *          - Initialize as DARK
 *      - In the function:
 *          - Declare an enum (DARK, LIGHT) to record the CURRENT light state
 *          - Declare a 16-bit integer, set value to the current light level
 *          - Declare a boolean return value, set to FALSE
 *          - Check if the current light level is below the light threshold or above the dark
 *              threshold
 *              - If either case is true, set currentLightState to respective value
 *              - Check if the currentLightState IS NOT equal to previousLightState
 *                  - if these are not equal, set returnValue to TRUE. Update previousLightState
 *                  - if these are equal, do nothing
 *          - return the returnValue
 * 
 * @param void
 * @return TRUE if light state change, FALSE otherwise
 */
uint8_t checkLight(void)
{
    
}

/* 
 * The Test Harness for the event checkers is conditionally compiled using
 * the EVENTCHECKER_TEST macro (defined either in the file or at the project level).
 * No other main() can exist within the project.
 * 
 * It requires a valid ES_Configure.h file in the project with the correct events in 
 * the enum, and the correct list of event checkers in the EVENT_CHECK_LIST.
 * 
 * The test harness will run each of your event detectors identically to the way the
 * ES_Framework will call them, and if an event is detected it will print out the function
 * name, event, and event parameter. Use this to test your event checking code and
 * ensure that it is fully functional.
 * 
 * If you are locking up the output, most likely you are generating too many events.
 * Remember that events are detectable changes, not a state in itself.
 * 
 * Once you have fully tested your event checking code, you can leave it in its own
 * project and point to it from your other projects. If the EVENTCHECKER_TEST marco is
 * defined in the project, no changes are necessary for your event checkers to work
 * with your other projects.
 */
#ifdef EVENTCHECKER_TEST
#include <stdio.h>
static uint8_t(*EventList[])(void) = {EVENT_CHECK_LIST};

void PrintEvent(void);

void main(void) {
    BOARD_Init();
    /* user initialization code goes here */

    // Do not alter anything below this line
    int i;

    printf("\r\nEvent checking test harness for %s", __FILE__);

    while (1) {
        if (IsTransmitEmpty()) {
            for (i = 0; i< sizeof (EventList) >> 2; i++) {
                if (EventList[i]() == TRUE) {
                    PrintEvent();
                    break;
                }

            }
        }
    }
}

void PrintEvent(void) {
    printf("\r\nFunc: %s\tEvent: %s\tParam: 0x%X", eventName,
            EventNames[storedEvent.EventType], storedEvent.EventParam);
}
#endif