/**
 * File: BOAT_HSM.h
 * Project: ECE 118 - Final Project
 * Author: Nicholas Kuipers
 * 
 * @brief Main State machine (hierarchical) for use with the BOAT robot.
 *      Global Variables:
 *          - RZ_EXIT = FALSE       // denotes when bot moved outside of reload zone, toggled by timer5
 *          - TURN_FLAG = FALSE     // used for center field collisions, bot turns to aim at goal if obstacle is in center of the field
 *          - BOT_FIELD_SIDE        // two field enums with LEFT/RIGHT values
 *          - OBS_FIELD_SIDE        // two field enums with LEFT/RIGHT values 
 *      HSM is structured as follows:
 *          - INIT
 *              - Upon power-on or reset bot moves immediately into this state. Initializes all
 *                  libraries and performs a UART handshake with the ESP32.
 *              - If a library initialization fails or the handshake fails, moves bot to INIT_FAIL state
 *                  where it sits until reset
 *          - INIT_FAIL
 *              - Light the Alert_LED. Perform no other actions (reset)
 *              - Reach state from INIT - low battery, failed init, failed handshake
 *          - STANDBY
 *              - INIT successful. Bot waits in this state until START_SWITCH event moves from OFF to ON
 *              - Upon START_SWITCH event, 1 second timer started. Upon timer expiry, moves state to ORIENTING
 *          - ORIENTING (Sub-State Machine)
 *              - FINDING_2K: Bot spins CCW until 2k beacon is found (BEACON_2K event)
 *              - STRAIGHTENING: Bot turns CW/CCW slowly for a few seconds while reading rear ToF sensor. After identifying
 *                  the minimum range in a ~60 degree cone (CW/CCW for 0.5seconds), bot turns CW slowly 
 *                  until that minimum range is found again. Bot *should* be oriented forward.
 *              - FINDING_SIDE: Bot compares ranges from both ToF sensors. The smaller range is determined to be 
 *                  the bot's side (Global Variable BOT_FIELD_SIDE = 0 (left) or 1 (right))
 *          - MOVE_TO_POSITION (Sub-State Machine)
 *              - Set 2 Second Timer (Timer5)
 *              - RZ_EXIT = FALSE
 *              - MOVING_FORWARD: Bot moves forward (no duh). While in this state, Timer5 is active. Upon expiry,
 *                  RZ_EXIT = TRUE, indicating bot has left the reload zone.
 *              - COLLISION:   
 *                  - Timer 5 stop
 *                  - OBS_FIELD_SIDE = BOT_FIELD_SIDE
 *                  - COLLISIONFLAG = TRUE
 *                  - Back away from collision (switch/case with bumper event)
 *                  - Strafe in direction opposite from BOT_FIELD_SIDE for 1 second (Timer 4)
 *                  - BOT_FIELD_SIDE = opposite side
 *              - AT_1PT: (Sub-State Machine)
 *                  - Reached upon tape event and RZ_EXIT = FALSE
 *                  - CENTERING: Bot uses ToF sensor on BOT_FIELD_SIDE to strafe 400mm (~16in) from that side wall.
 *                      - If neither side wall is within 400mm, bot moves to closer side wall until it is 400mm away
 *                  - COLLISION: Entered during CENTERING if bot sees an obstacle on its opposite ToF sensor (range of < 50mm),
 *                      or experiences a corner bumper event.
 *                          - If ToF event: if bot is within 100mm of the 400mm from the side wall, TURN_FLAG is set to TRUE and bot spins slowly
 *                              (CCW if BOT_FIELD_SIDE = RIGHT and CW otherwise) for 0.5 seconds. Otherwise, obstacle must be on the bot's side of the field.
 *                  - Bot uses ToF sensor on BOT_FIELD_SIDE to strafe 400mm away from that wall
 *                  - If other ToF sensor detects an obstacle (ranging < 500mm - initialDistanceFromWall) or encounters a bumper event, go into collision detection
 * 
 * 
 */

#ifndef BOAT_HSM_H  // <- This should be changed to your own guard on both
#define BOAT_HSM_H  //    of these lines


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
 *      the hierarchical state machine.
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
 * @brief Runs and updates the Hierarchical State Machine. Function is called recursively
 *      to implement the correct order for a state transition (i.e. exit current state
 *      -> enter new state using ES_EXIT and ES_ENTRY events)
 * @param ThisEvent - event (type and param) to be responded to
 * @return return event type - in general should be ES_NO_EVENT but can have other values
 *      during events of recursion
 */
ES_Event RunHSM(ES_Event ThisEvent);


/** Extra Functions **/

/**
 * @Function ResetHSM(void)
 * @param none
 * @return none
 * 
 * @brief Called by a switch event from ON to OFF. Sets the HSM state back to STANDBY. Checks that state
 *      is not in INIT or STANDBY to prevent potential errors
 * 
 * @author Nicholas Kuipers
 */
void ResetHSM(void);

/**
 * @Function ReadTOF(unsigned int leftToF, unsigned int rightToF, unsigned int backToF)
 * @param none
 * @return none
 * 
 * @brief Allows for the updateToF event to directly pass updated ToF measurements read
 *      from the analog pins (connected to ESP32) to the HSM.
 * @author Nicholas Kuipers
 */
void HSM_UpdateTOF(unsigned int leftToF, unsigned int rightToF, unsigned int backToF);

#endif /* BOAT_HSM_H */

