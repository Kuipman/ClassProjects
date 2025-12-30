/*
 * File: BOAT_SubHSM_Orienting.h
 * Author: Nicholas Kuipers
 *
 * Brief: Sub-State Machine designed to work under the ORIENTING state of the BOAT's
 *      Hierarchical State Machine.
 * 
 * Note: Collisions are ignored in the ORIENTING state
 */

#ifndef BOAT_SUBHSM_ORIENTING_H  // <- This should be changed to your own guard on both
#define BOAT_SUBHSM_ORIENTING_H  //    of these lines


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
uint8_t InitSubHSM_Orienting(void);

/**
 * @Function RunSubHSM(ThisEvent)
 * @brief Sub State Machine operates within the ORIENTING state for HSM.
 *      States in this SSM include:
 *          - INIT: Default state, moves to FINDING after initialization
 *          - FINDING:
 *              - Bot spins in place reading its 2k beacon detector until it finds the beacon.
 *          - MANEUVERING:
 *              - Bot uses its rear ToF sensor readings as it sways back and forth to find the minimum value
 *                  (bot is oriented forward)
 * @param ThisEvent
 * @return 
 */
ES_Event RunSubHSM_Orienting(ES_Event ThisEvent);

#endif /* BOAT_SUBHSM_ORIENTING_H */

