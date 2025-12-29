/**
 * File: PingService.h
 * Group: Nick Kuipers
 * 
 * @brief Header for Ping Service function, designed to integrate in the
 *      broader ES_Framework built for ECE 118.
 */

#ifndef PINGSERVICE_H  // <- This should be changed to your own guard on both
#define PINGSERVICE_H  //    of these lines


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
 * @brief Initializes the ping service function, called automatically by the ES_Framework
 *      at the beginning of code execution
 * @param Priority - internal variable tracking which event queue is used
 * @return True for success, False otherwise
 */
uint8_t InitPingService(uint8_t Priority);

/**
 * @brief Wrapper function allowing for post of an event to the respective
 *      queue for the Ping Service Function.
 * @param ThisEvent - the event (a struct with "type" and "param" variables) to
 *      be posted to queue
 * @return TRUE if successful, FALSE otherwise
 */
uint8_t PostPingService(ES_Event ThisEvent);

/**
 * @brief Holds the actual Ping Service Function, called any time a new event
 *      is passed to the respective event queue.
 *      Service operates as follows:
 *          - Service can be called upon expiry of Timer0 (two instances), or upon 
 *              an EW_Event (specifically when it moves from high to low)
 *          - a static triggerFlag keeps track of the two separate instances when Timer0 calls service
 *          - If the service is called by timer0
 *              - If triggerFlag is 0, flag is set to 1 as the trigger pin is set high
 *                  and Timer0 is set for 1ms
 *              - If the triggerFlag is 1, flag is set back to 0. FRT time (START) is recorded
 *          - If the service is called by EW_Event
 *              - Records the FRT Time (STOP) and calculates the resulting distance
 *              - Prints distance as a terminal output
 * @param ThisEvent - the event (type and param) to be responded to
 * @return event - return event (type and param), that in general should be ES_NO_EVENT
 */

ES_Event RunPingService(ES_Event ThisEvent);



#endif /* PINGSERVICE_H */

