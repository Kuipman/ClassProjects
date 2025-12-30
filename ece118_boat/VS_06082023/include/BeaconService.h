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

#ifndef BEACONSERVICE_H  // <- This should be changed to your own guard on both
#define BEACONSERVICE_H  //    of these lines


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
 * @brief Initializes the Beacon Service function, called automatically by the
 *      ES_Framework at the beginning of code execution.
 * @note This will post an ES_INIT event to the event queue for the Tape Service,
 *      requiring an adequate handler within the run function
 * @param Priority - internal variable to track which event queue is used
 * @return TRUE if successful, FALSE otherwise
 */
uint8_t InitBeaconService(uint8_t Priority);

/**
 * @brief Wrapper function allowing for post of an event to the respective
 *      queue for the Beacon Service Function.
 * @param ThisEvent - the event (a struct with "type" and "param" variables) to
 *      be posted to queue
 * @return TRUE if successful, FALSE otherwise
 */
uint8_t PostBeaconService(ES_Event ThisEvent);

/**
 * @brief Holds the actual Beacon Service Function, called any time a new event
 *      is passed to the respective event queue.
 *          - Switch/Case splits activity on whether the 1.5k or 2k beacon event was called 
 * @param ThisEvent - the event (type and param) to be responded to
 * @return event - return event (type and param), that in general should be ES_NO_EVENT
 */

ES_Event RunBeaconService(ES_Event ThisEvent);



#endif /* BEACONSERVICE_H */

