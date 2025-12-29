/**
 * File: LightService.h
 * Project: ECE 118 Lab 0, Part 5
 * Group: Group 8, Nick Kuipers & Josh Gamlen
 * 
 * @brief Header for Light Service function, designed to integrate in the
 *      broader ES_Framework built for ECE 118.
 *      - Version 1: Print message to the terminal indicating a light event occurred
 */

#ifndef LIGHTService_H  // <- This should be changed to your own guard on both
#define LIGHTService_H  //    of these lines


/*******************************************************************************
 * PUBLIC #INCLUDES                                                            *
 ******************************************************************************/

#include "ES_Configure.h"   // defines ES_Event, INIT_EVENT, ENTRY_EVENT, and EXIT_EVENT

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/

#define LIGHT_SERVICE_V1    1       // transition from light to dark, or vice-versa

/*******************************************************************************
 * PUBLIC TYPEDEFS                                                             *
 ******************************************************************************/

typedef enum{
    GRAY,
    DARK,
    LIGHT
}LIGHT_STATE;

/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/**
 * @brief Initializes the light service function. This function is called automatically
 *      by the ES_FRAMEWORK at the beginning of code execution.
 * @param Priority - internal variable tracking which event queue is used
 * @return TRUE if successful, FALSE otherwise
 */
uint8_t InitLightService(uint8_t Priority);

/**
 * @brief Wrapper function allowing for post of an event to the respective
 *      queue for the Light Service Function.
 * @param ThisEvent - the event (a struct with "type" and "param" variables) to
 *      be posted to queue
 * @return TRUE if successful, FALSE otherwise
 */
uint8_t PostLightService(ES_Event ThisEvent);

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

ES_Event RunLightService(ES_Event ThisEvent);

#endif /* LIGHT_SERVICE_V1 */



#endif /* LIGHTService_H */

