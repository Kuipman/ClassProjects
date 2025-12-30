/*
 * File: BOAT_SubHSM_Returning.h
 * Author: Nicholas Kuipers
 * 
 * Brief: Sub-State Machine designed to work under the RETURNING state of the BOAT's
 *      Hierarchical State Machine.
 */

#ifndef ES_SUBHSM_RETURNING_H  // <- This should be changed to your own guard on both
#define ES_SUBHSM_RETURNING_H  //    of these lines


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
uint8_t InitSubHSM_Returning(void);

/**
 * @Function RunSubHSM_Returning(ThisEvent)
 * @brief Sub State Machine operates within the RETURNING state for HSM.
 *      Structured as follows:
 *          - INIT state: Default state
 * `        - MOVING: Upon entry, bot decides whether to move to closest wall (if obstacle
 *              is not on the same side or position unknown, i.e. no collision occurred yet) or furthest wall (if obstacle
 *              is known to be on same side). 3 second timer is started and decrements during movement
 *              - Then, bot moves in reverse. Timer decrements.
 *          - COLLISION: Rear bumper collision.
 *              - If timer has not expired (flag = FALSE), it is an obstacle or wall collision. Assume obstacle.
 *                  - Bot strafes to wall on opposite side of field. Set COLLIDED flag. Switches back to MOVING
 *              - If timer HAS expired, assume bot has reached the reload zone.
 *          - RELOADING: Boat reached RZ, 3 second timer started on transition
 *              - Bot does not move. Upon conclusion of 3 second timer, HSM state transition to ORIENTING
 * @param ThisEvent
 * @return 
 */
ES_Event RunSubHSM_Returning(ES_Event ThisEvent);

#endif /* ES_SUBHSM_RETURNING_H */

