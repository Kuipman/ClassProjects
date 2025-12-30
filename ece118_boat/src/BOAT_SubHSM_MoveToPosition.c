/*
 * File: BOAT_SubHSM_MoveToPosition.c
 * Author: Nicholas Kuipers
 *
 * Brief: Sub-State Machine for use in the MoveToPosition state seen in the HSM of the BOAT
 *      final project for mechatronics ECE 118. The following states are:
 *      - INIT: Default starting state, SSM sits here until it receives an ES_ENTRY event from the HSM.
 *              - Upon receipt of ES_ENTRY event, SSM starts a 3 second timer (TIMER 1). This timer will only
 *                  decrement while bot is in the following MOVING state.
 *      - MOVING: Bot moves forward at standard speed (it is assumed from ORIENTING the bot is facing the goal (or directly forward)).
 *              - TIMER 1 will decrement normally. If it expires, it will trigger the RZ_CLEARED flag to be set to TRUE, meaning the next
 *                  tape event of the rear tape sensor will indicate crossing the 1pt line
 *              - If a tape event at the rear sensor occurs (0 -> 1), SSM will transition to FINISHED state
 *              - If a bumper event is detected, SSM moves into the REACTION state
 *      - REACTION: Bot has encountered a collision (bumper event)
 *              - If TIMER 1 is still running, it is paused. Timer 2 is activated for half a second. Bot moves from the collision
 *                  at SLOW speed until the timer expires. Then Timer 2 restarts for a full second as the bot strafes in a given
 *                  direction (ideally using the TOF sensors) until timer expiry. Then, state returns to MOVING.
 *              - If another COLLISION event occurs (BUMPER_EVENT), the maneuvers are restarted
 */


/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BOARD.h"
#include <stdio.h>
#include "BOAT.h"
#include "BOAT_HSM.h"
#include "BOAT_SubHSM_MoveToPosition.h"
#include "BOAT_Movement.h"
#include "BOAT_Sensors.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
typedef enum {
    MOVING,
    REACTION
} MTPSubHSMState_t;

static const char *StateNames[] = {
	"MOVING",
};



/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/

/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                            *
 ******************************************************************************/
/* You will need MyPriority and the state variable; you may need others as well.
 * The type of state variable should match that of enum in header file. */

static MTPSubHSMState_t CurrentState = MOVING; 
static uint8_t MyPriority;
static uint8_t currentBumperState;   // Tracks the state of bumpers for obstacle detection
static uint8_t RZ_Cleared;


/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitTemplateSubHSM(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTemplateFSM function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitSubHSM_MoveToPosition(void)
{
    ES_Event returnEvent;

    CurrentState = MOVING;
    currentBumperState = 0;
    RZ_Cleared = FALSE;
    returnEvent = RunSubHSM_MoveToPosition(INIT_EVENT);
    if (returnEvent.EventType == ES_NO_EVENT) {
        return TRUE;
    }
    return FALSE;
}

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
ES_Event RunSubHSM_MoveToPosition(ES_Event ThisEvent)
{
    uint8_t makeTransition = FALSE; // use to flag transition
    MTPSubHSMState_t nextState; // <- change type to correct enum

    ES_Tattle(); // trace call stack
    
    switch(CurrentState)
    {
        /*
         * MOVING
         * @brief Bot moves forward. Upon state entry a 3 second timer is started -- upon expiry
         *      the RZ_Cleared flag is set to TRUE. This is set back to FALSE when the SSM sends
         *      back the SSM_FINISHED event
         */
        case MOVING:
        {
            // A number of events can potentially occur. We check for each relevant event
            switch(ThisEvent.EventType)
            {
                // Upon entry, the bot starts its 3 second timer and starts the motors to run forward
                case ES_ENTRY:
                {
                    printf("\r\nIn SubHSM MoveToPosition");
                    ES_Timer_InitTimer(1, 3000);    // Movement timer is began
                    BOAT_MoveForward(STANDARD_FORWARD_SPEED);
                    break;
                }
                // When 3 second timer expires, sets the RZ_Cleared flag to TRUE
                case ES_TIMEOUT:
                {
                    printf("\r\n MTP TIMEOUT");
                    RZ_Cleared = TRUE;
                    break;
                }
                case TAPE_EVENT:
                {
                    if(RZ_Cleared == TRUE)
                        if(ThisEvent.EventParam & 0b1000)
                        {
                            BOAT_StopMovement();
                            RZ_Cleared = FALSE;
                            nextState = MOVING;
                            //makeTransition = TRUE;
                            ThisEvent.EventType = SSM_FINISHED;
                        }
                    break;
                }
            }
        }
        case REACTION:
        {

         break;
        }
        
}
    
#if BLOCK_OLDSTATEMACHINE   
    if((ThisEvent.EventType == LIGHTLEVEL) && ThisEvent.EventParam == LIGHT)
    {
        CurrentState = START;
        ThisEvent.EventType = ES_NO_EVENT;
        return ThisEvent;
    }

    switch (CurrentState) {
    case INIT: // If current state is initial Psedudo State
        if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
        {
            // this is where you would put any actions associated with the
            // transition from the initial pseudo-state into the actual
            // initial state

            // now put the machine into the actual initial state
            nextState = START;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
        }
        break;

    case START: // in the first state, replace this with correct names
    {
        if(ThisEvent.EventType == BUMPER_PRESS)
        {
            currentBumperState= ThisEvent.EventParam;
            nextState = REACT;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
        }
        break;
    }
    case REACT:
    {
        if(ThisEvent.EventType == ES_ENTRY)
        {
            if (currentBumperState & 0b1000 || currentBumperState & 0b0100) 
            {
                moveAway_RB();  //if rear bumpers pressed at all, escape forwards
                printf("MOVE RB\r\n");
            } 
            else 
            {
                moveAway_FB();  //if no rear bumpers hit, escape backwards
                printf("MOVE FB: %x\r\n", currentBumperState);
            }
        }
        if(ThisEvent.EventType == BUMPER_RELEASE)
        {
            nextState = RUNNING;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
        }
        break;
    }
    case RUNNING:
    {
        if(ThisEvent.EventType == ES_ENTRY)
        {
            ES_Timer_InitTimer(1, 500);  // 1/2 second timer
        }
        if(ThisEvent.EventType == BUMPER_PRESS)
        {
            stopMoving();
            currentBumperState= ThisEvent.EventParam;
            nextState = REACT;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
        }
        if(ThisEvent.EventType == ES_TIMEOUT)
        {
            stopMoving();
            nextState = START;
            makeTransition = TRUE;
            ThisEvent.EventType = SUB_SM_COMPLETE;
        }
        break;
    }
        
    default: // all unhandled states fall into here
        break;
    } // end switch on Current State
    
#endif

    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunSubHSM_MoveToPosition(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunSubHSM_MoveToPosition(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/
