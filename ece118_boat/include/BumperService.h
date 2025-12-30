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

#ifndef BUMPERService_H  // <- This should be changed to your own guard on both
#define BUMPERService_H  //    of these lines


/*******************************************************************************
 * PUBLIC #INCLUDES                                                            *
 ******************************************************************************/

#include "ES_Configure.h"   // defines ES_Event, INIT_EVENT, ENTRY_EVENT, and EXIT_EVENT

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/

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
 *      is passed to the respective event queue. Performs the following:
 *          - Performs debouncing on first BUMPER_EVENT by setting a 10ms timer and
 *              ignoring calls by future BUMPER_EVENTs until the timer expires
 *          - Cross-references the current bumper value tracked in the service and determines
 *              whether this is a BUMPER_PRESS or BUMPER_RELEASE event
 * @param ThisEvent - the event (type and param) to be responded to
 * @return event - return event (type and param), that in general should be ES_NO_EVENT
 */

ES_Event RunBumperService(ES_Event ThisEvent);



#endif /* TemplateService_H */

