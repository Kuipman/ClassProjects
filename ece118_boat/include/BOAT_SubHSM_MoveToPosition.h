/*
 * File: BOAT_SubHSM_MoveToPosition.h
 * Author: Nicholas Kuipers
 * 
 * Brief: Sub-State Machine designed to work under the ORIENTING state of the BOAT's
 *      Hierarchical State Machine.
 */

#ifndef BOAT_SUBHSM_MOVETOPOSITION_H  // <- This should be changed to your own guard on both
#define BOAT_SUBHSM_MOVETOPOSITION_H  //    of these lines


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
uint8_t InitSubHSM_MoveToPosition(void);

/**
 * @Function RunSubHSM_MoveToPositon(ThisEvent)
 * @brief Sub State Machine operates within the MOVE_TO_POSITION state for HSM.
 *      Structured as follows:
 *          - INIT: Default state. Moves to next state upon SSM activation.
 *              - Sets 3 second timer (RZ_Exit) and moves forward upon state transition to MOVING
 *          - MOVING: Bot moves forward. Timer decrements.
 *              - Upon timer expiry, RZ_Exit flag set to TRUE and bot begins searching for 1pt tape
 *          - COLLISION: Bumper event, frontal collision
 *          - REACHED_1PT: Tape event when RZ_Exit = TRUE
 *              - Bot stops moving, HSM transition to AT1PT
 * @param ThisEvent
 * @return 
 */
ES_Event RunSubHSM_MoveToPosition(ES_Event ThisEvent);

#endif /* BOAT_SUBHSM_MOVETOPOSITION_H */

