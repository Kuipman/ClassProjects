/**
 * File: TapeAndTrackService.h
 * Project: ECE 118 - Final Project
 * Author: Nicholas Kuipers
 * 
 * @brief Header for Tape Service function, designed to integrate in the
 *      broader ES_Framework built for ECE 118.
 *      - Service determines what tape sensor triggered the TAPE_EVENT 
 */

#ifndef TAPEANDTRACKSERVICE_H  // <- This should be changed to your own guard on both
#define TAPEANDTRACKSERVICE_H  //    of these lines


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
 * @brief Initializes the Tape Service function, called automatically by the
 *      ES_Framework at the beginning of code execution.
 * @note This will post an ES_INIT event to the event queue for the Tape Service,
 *      requiring an adequate handler within the run function
 * @param Priority - internal variable to track which event queue is used
 * @return TRUE if successful, FALSE otherwise
 */
uint8_t InitTapeAndTrackService(uint8_t Priority);

/**
 * @brief Wrapper function allowing for post of an event to the respective
 *      queue for the Tape Service Function.
 * @param ThisEvent - the event (a struct with "type" and "param" variables) to
 *      be posted to queue
 * @return TRUE if successful, FALSE otherwise
 */
uint8_t PostTapeAndTrackService(ES_Event ThisEvent);

/**
 * @brief Holds the actual Tape Service Function, called any time a new event
 *      is passed to the respective event queue. Works similarly to Bumper Service, but
 *      without need for debouncing.
 *          - When the TAPE_EVENT is received, this simply passes the param along as a
 *              TAPE_EVENT to the  
 * @param ThisEvent - the event (type and param) to be responded to
 * @return event - return event (type and param), that in general should be ES_NO_EVENT
 */

ES_Event RunTapeAndTrackService(ES_Event ThisEvent);



#endif /* TemplateService_H */

