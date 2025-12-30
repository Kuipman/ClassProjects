/*
 * File: BOAT_SubHSM_At1Pt.h
 * Author: Nicholas Kuipers
 *
 * Brief: Sub-State Machine designed to work under the AT_1PT state of the BOAT's
 *      Hierarchical State Machine.
 */

#ifndef BOAT_SUBHSM_AT1PT_H  // <- This should be changed to your own guard on both
#define BOAT_SUBHSM_AT1PT_H  //    of these lines


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
uint8_t InitSubHSM_At1Pt(void);

/**
 * @Function RunSubHSM(ThisEvent)
 * @brief Sub State Machine operates within the AT_1PT state for HSM.
 *      Structured as follows:
 *          - INIT state: Default state
 *          - MOVING_TO_RANGE: Bot uses ToF with closest wall, strafes until roughly
 *              400mm from that wall (~16in)
 *              - Upon reaching 400mm, bot stops moving during state transition
 *          - RANGE_REACHED: Bot has stopped moving. Sends signal to ESP32 to turn on Flywheel.
 *              - HSM transition to FIRING
 *          - COLLISION: Bumper event or opposite ToF sensor sees obstacle within 50mm
 *              - If Bumper event and bot <300mm from wall, bot reverses and strafes "around" the obstacle by
 *                  moving to opposite side's 16" range, then moves back up.
 *              - If ToF event and bot is less than 200mm from the wall, does above. Else, bot moves to ~75mm from the obstacle, stops,
 *                  and turns towards the goal (hardcode the time taken). Then, moves state to RANGE_REACHED
 * @param ThisEvent
 * @return 
 */
ES_Event RunSubHSM_At1Pt(ES_Event ThisEvent);

#endif /* BOAT_SUBHSM_AT1PT_H */

