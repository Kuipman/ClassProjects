/*
 * File: TemplateSubHSM.c
 * Author: J. Edward Carryer
 * Modified: Gabriel H Elkaim
 *
 * Template file to set up a Heirarchical State Machine to work with the Events and
 * Services Framework (ES_Framework) on the Uno32 for the CMPE-118/L class. Note that
 * this file will need to be modified to fit your exact needs, and most of the names
 * will have to be changed to match your code.
 *
 * There is for a substate machine. Make sure it has a unique name
 *
 * This is provided as an example and a good place to start.
 *
 * History
 * When           Who     What/Why
 * -------------- ---     --------
 * 09/13/13 15:17 ghe      added tattletail functionality and recursive calls
 * 01/15/12 11:12 jec      revisions for Gen2 framework
 * 11/07/11 11:26 jec      made the queue static
 * 10/30/11 17:59 jec      fixed references to CurrentEvent in RunTemplateSM()
 * 10/23/11 18:20 jec      began conversion from SMTemplate.c (02/20/07 rev)
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
#include "BOAT_SubHSM_Returning.h"
#include "BOAT_Movement.h"
#include "BOAT_Sensors.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
typedef enum {
    MOVING,
    REACTION,
} Returning_SubHSMState_t;

static const char *StateNames[] = {
	"MOVING",
	"REACTION",
};



/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/

/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                            *
 ******************************************************************************/
/* You will need MyPriority and the state variable; you may need others as well.
 * The type of state variable should match that of enum in header file. */

static Returning_SubHSMState_t CurrentState = MOVING; // <- change name to match ENUM
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
uint8_t InitSubHSM_Returning(void)
{
    ES_Event returnEvent;

    CurrentState = MOVING;
    currentBumperState = 0;
    returnEvent = RunSubHSM_Returning(INIT_EVENT);
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
ES_Event RunSubHSM_Returning(ES_Event ThisEvent)
{
    uint8_t makeTransition = FALSE; // use to flag transition
    Returning_SubHSMState_t nextState; // <- change type to correct enum

    ES_Tattle(); // trace call stack

    switch (CurrentState) 
    {
        /*
         * MOVING
         * @brief Bot moves backwards, a 3 second timer is implemented. Bot continues moving until it encounters
         *      a bumper event after 3 seconds
         * 
         */
    case MOVING: // If current state is initial Psedudo State
    {
        switch(ThisEvent.EventType)
        {
            case ES_ENTRY:
            {
                printf("\r\nIn SubHSM Returning");
                ES_Timer_InitTimer(1, 3000);
                BOAT_MoveBackward(STANDARD_REVERSE_SPEED);
                break;
            }
            case ES_TIMEOUT:
                {
                    printf("\r\n MTP TIMEOUT");
                    RZ_Cleared = TRUE;
                    break;
                }
                case BUMPER_PRESS:
                {
                    if(RZ_Cleared == TRUE)
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
        break;
    }
    case REACTION:
    {

     break;
    }
    default: // all unhandled states fall into here
        break;
    } // end switch on Current State

    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunSubHSM_Returning(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunSubHSM_Returning(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/
