/*
 * File: TemplateSubHSM.h
 * Author: J. Edward Carryer
 * Modified: Gabriel H Elkaim and Soja-Marie Morgens
 *
 * Template file to set up a Heirarchical SubState Machine to work with the Events and
 * Services Framework (ES_Framework) on the Uno32 for the CMPE-118/L class. Note that 
 * this file will need to be modified to fit your exact needs, and most of the names
 * will have to be changed to match your code.
 *
 * Make sure each SubState machine has a unique name and is #include in the
 * higher level state machine using it
 *
 * This is provided as an example and a good place to start.
 *
 * Created on 23/Oct/2011
 * Updated on 16/Sep/2013
 */

#ifndef SUB_TEMPLATE_HSM_H  // <- This should be changed to your own guard on both
#define SUB_TEMPLATE_HSM_H  //    of these lines


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
 * @brief Initialization function for sub state machine
 * @return 
 */
uint8_t InitSubHSM(void);

/**
 * @Function RunSubHSM(ThisEvent)
 * @brief Sub State Machine operates within the IDLE state for HSM.
 *      Structured as follows:
 *          - START state: Default state, we start here and return here after a 
 *              TIMEOUT event in RUNNING state
 *              - Motors are stopped
 * `        - REACT state: Transition here upon a bumper press
 *              - Determine which bumper, start moving opposite direction
 *              - Switch state upon receiving a BUMPER_RELEASE event
 *          - RUNNING state: Transition here upon BUMPER_RELEASE
 *              - Immediately start 1/2 second timer
 *              - Upon BUMPER_PRESS
 *                  - Stop motors, return to REACT state
 *              - Upon TIMEOUT
 *                  - Stop motors
 *                  - Return to START state
 * @param ThisEvent
 * @return 
 */
ES_Event RunSubHSM(ES_Event ThisEvent);

#endif /* SUB_HSM_Template_H */

