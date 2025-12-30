/**
 * File: ES_HSM.h
 * Project: ECE 118 - Lab 0 Part 7
 * Authors: Josh Gamlen, Nick Kuipers
 * 
 * @brief Hierarchical State Machine designed to function with the ES_FRAMEWORK.
 *      HSM structured as follows:
 *          - IDLE
 *              - Light level is dark. Bumpers DO matter
 *                  - If bumper is pressed, move away until BUMPER_RELEASED, then set 1/2 second
 *                      timer and stop moving after TIMEOUT
 *                  - If in the light, change state to SEARCHING 
 *          - SEARCHING
 *              - Light level is light. 
 *              - Roach is searching for a dark place
 *              - If light level changes to dark, state returns to IDLE
 *              - If a bumper is pressed, state moves to OBSTACLE_DETECTED
 *          - OBSTACLE_DETECTED
 *              - Light level does not matter
 *              - Roach moves away from bumper press
 *                  - Backwards from front bumper press, forwards from rear bumper press
 *                  - Movement in either direction is straight and veering to the right
 *              - After movement, if bumpers are no longer pressed state returns to SEARCHING
 *              - If another bumper is pressed, repeats process until no bumpers are pressed
 */

#ifndef ES_HSM_H  // <- This should be changed to your own guard on both
#define ES_HSM_H  //    of these lines


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
 * @Function InitHSM(uint8_t)
 * @brief Called by the framework at beginning of code execution to initialize
 *      the finite state machine.
 * @note Will post an ES_INIT event to the appropriate queue, which is handled in the
 *      RunFSM() function.
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE if success, FALSE otherwise
 */
uint8_t InitHSM(uint8_t Priority);


/**
 * @Function PostHSM(ES_Event ThisEvent)
 * @brief Wrapper to the queue posting function -- posts the event to the respective
 *      queue for later operation by RunFSM()
 * @param ThisEvent - Event with a type and parameter
 * @return TRUE if success, FALSE otherwise
 */
uint8_t PostHSM(ES_Event ThisEvent);




/**
 * @Function RunHSM(ES_Event ThisEvent)
 * @brief Runs and updates the Finite State Machine. Function is called recursively
 *      to implement the correct order for a state transition (i.e. exit current state
 *      -> enter new state using ES_EXIT and ES_ENTRY events)
 * @param ThisEvent - event (type and param) to be responded to
 * @return return event type - in general should be ES_NO_EVENT but can have other values
 *      during events of recursion
 */
ES_Event RunHSM(ES_Event ThisEvent);

#endif /* ES_HSM_H */

