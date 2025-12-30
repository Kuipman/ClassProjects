/*
 * File: BOAT_SubHSM_Firing.h
 * Author: Nicholas Kuipers
 * 
 * Brief: Sub-State Machine designed to work under the FIRING state of the BOAT's
 *      Hierarchical State Machine.
 */

#ifndef BOAT_SUBHSM_FIRING_H  // <- This should be changed to your own guard on both
#define BOAT_SUBHSM_FIRING_H  //    of these lines


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
uint8_t InitSubHSM_Firing(void);

/**
 * @Function RunSubHSM_Firing(ThisEvent)
 * @brief Sub State Machine operates within the FIRING state for HSM.
 *      Upon entry, ESP32 has global variable AMMO = 3
 *      Structured as follows:
 *          - INIT state: Default State
 *          - LOAD_BALL: Sends a high signal to the ESP32 (digital pin) to tell it to engage the firing sequence.
 *              ESP32 handles the extent of the firing sequence via its state machine
 *          - STANDING_BY: Digital pin is converted to an input. PIC waits for signal over this pin from the ESP32 indicating
 *              the firing sequence is complete and the flywheel has stopped turning.
 *              - HSM state transition to returning
 * @param ThisEvent
 * @return 
 */
ES_Event RunSubHSM_Firing(ES_Event ThisEvent);

#endif /* BOAT_SUBHSM_FIRING_H */

