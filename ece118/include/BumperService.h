/**
 * File: BumperService.h
 * Project: ECE 118 Lab 0, Part 5
 * Group: Group 8, Nick Kuipers & Josh Gamlen
 * 
 * @brief Header for Bumper Service function, designed to integrate in the
 *      broader ES_Framework built for ECE 118.
 *      - Version 1: Print message to the terminal indicating a bumper event occurred
 *      - Version 2: Added logic determining what bumper triggered the event and what change
 *          occurred (BUMPER_PRESSED, BUMPER_RELEASED)
 */

#ifndef BUMPERService_H  // <- This should be changed to your own guard on both
#define BUMPERService_H  //    of these lines


/*******************************************************************************
 * PUBLIC #INCLUDES                                                            *
 ******************************************************************************/

#include "ES_Configure.h"   // defines ES_Event, INIT_EVENT, ENTRY_EVENT, and EXIT_EVENT

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/

#define BUMPER_SERVICE_V1    0       // "catch-all" for any bumper event
#define BUMPER_SERVICE_V2    1       // Only bumper presses generate FSM changes

/*******************************************************************************
 * PUBLIC TYPEDEFS                                                             *
 ******************************************************************************/


/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/**
 * @brief Initializes the Bumper Service function, called automatically by the
 *      ES_Framework at the beginning of code execution.
 * @note This will post an ES_INIT event to the event queue for the Bumper Service,
 *      requiring an adequate handler within the run function
 * @param Priority - internal variable to track which event queue is used
 * @return TRUE if successful, FALSE otherwise
 */
uint8_t InitBumperService(uint8_t Priority);

/**
 * @brief Wrapper function allowing for post of an event to the respective
 *      queue for the Bumper Service Function.
 * @param ThisEvent - the event (a struct with "type" and "param" variables) to
 *      be posted to queue
 * @return TRUE if successful, FALSE otherwise
 */
uint8_t PostBumperService(ES_Event ThisEvent);

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

ES_Event RunBumperService(ES_Event ThisEvent);



#endif /* TemplateService_H */

