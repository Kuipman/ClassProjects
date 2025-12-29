/**
 * File: ES_FSM.c
 * Project: ECE 118 - Lab 0 Part 7
 * Authors: Josh Gamlen, Nick Kuipers
 * 
 * @brief Finite State Machine designed to function with the ES_FRAMEWORK.
 *      - FSM structured with the following states:
 *          - IDLE
 *              - Light level is dark. Bumpers do not matter
 *              - Does nothing. Continues to run event checkers until Light Level
 *                  changes to light
 *          - SEARCHING
 *              - Light level is light. 
 *              - Roach is searching for a dark place
 *              - If light level changes to dark, state returns to IDLE
 *              - If a bumper is pressed, state moves to OBSTACLE_DETECTED
 *          - OBSTACLE_DETECTED
 *              - Light level does not matter
 *              - Roach moves away from bumper press
 *                  - Backwards from front bumper press, forwards from rear bumper press
 *                  - Movement in either direction is straight and veering to the right
 *              - After movement, if bumpers are no longer pressed state returns to SEARCHING
 *              - If another bumper is pressed, repeats process until no bumpers are pressed
 */

/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "ES_Configure.h"
#include "ES_Framework.h"

#include "ES_FSM.h"
#include <BOARD.h>
//Uncomment these for the Roaches
//#include "roach.h"
//#include "RoachFrameworkEvents.h"
#include <stdio.h>


/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/

#define STANDARD_SPEED  75
#define STANDARD_TURN   25
#define REVERSE_SPEED  -60
#define REVERSE_TURN   -40

/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
void moveForward();
void moveBackward();
void turnRight();
void stopMoving();
void moveAway_FB();
void moveAway_RB();


/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                            *
 ******************************************************************************/

/* You will need MyPriority and the state variable; you may need others as well.
 * The type of state variable should match that of enum in header file. */

typedef enum {
    INIT,
    IDLE,
    SEARCHING,
    OBSTACLE_DETECTED,
} HSMState_t;

static const char *StateNames[] = {
    "INIT",
	"IDLE",
	"SEARCHING",
    "OBSTACLE_DETECTION",
};


static HSMState_t CurrentState = INIT; // <- change enum name to match ENUM
static uint8_t MyPriority;
static uint8_t currentBumperState;   // Tracks the state of bumpers for obstacle detection
static uint8_t altFlag;   // boolean that operates differently depending on state
static uint8_t timerRunning;   // boolean, active whenever timer 1 is running


/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitTemplateFSM(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTemplateFSM function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitFSM(uint8_t Priority)
{
    MyPriority = Priority;
    // put us into the Initial PseudoState
    CurrentState = INIT;
    currentBumperState = 0;   // Tracks the state of bumpers for obstacle detection
    altFlag            = FALSE;   // boolean that operates differently depending on state
    timerRunning       = FALSE;   // boolean, active whenever timer 1 is running
    // post the initial transition event
    if (ES_PostToService(MyPriority, INIT_EVENT) == TRUE) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * @Function PostFSM(ES_Event ThisEvent)
 * @brief Wrapper to the queue posting function -- posts the event to the respective
 *      queue for later operation by RunFSM()
 * @param ThisEvent - Event with a type and parameter
 * @return TRUE if success, FALSE otherwise
 */
uint8_t PostFSM(ES_Event ThisEvent)
{
    return ES_PostToService(MyPriority, ThisEvent);
}

/**
 * @Function RunFSM(ES_Event ThisEvent)
 * @brief Runs and updates the Finite State Machine. Function is called recursively
 *      to implement the correct order for a state transition (i.e. exit current state
 *      -> enter new state using ES_EXIT and ES_ENTRY events)
 * @param ThisEvent - event (type and param) to be responded to
 * @return return event type - in general should be ES_NO_EVENT but can have other values
 *      during events of recursion
 */
ES_Event RunFSM(ES_Event ThisEvent)
{
    uint8_t makeTransition = FALSE; // use to flag transition
    HSMState_t nextState; // <- need to change enum type here

    ES_Tattle(); // trace call stack

    switch (CurrentState) {
    case INIT: // If current state is initial Pseudo State
        if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
        {
            /*
             Initial actions of the State Machine go here
             */

            // now put the machine into the actual initial state
            nextState = IDLE;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
        }
        break;
/************************************************************/
    case IDLE:
    {
        // DEBUG -- Light 1st LED on LED Bar
        if (ThisEvent.EventType == ES_ENTRY)
        {
            Roach_LEDSSet(0x1);
            altFlag = FALSE;
            ES_Timer_StopTimer(1);
        }
#if DEBUG_FSM
        // DEBUG -- State machine transition
        if(ThisEvent.EventType == BUMPER_PRESS)
        {
            nextState = SEARCHING;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
            ThisEvent.EventParam = 0;
        }
#endif  /* DEBUG_FSM */

#if !DEBUG_FSM
        // Change state to SEARCHING if the light has changed from DARK to LIGHT
        if((ThisEvent.EventType == LIGHTLEVEL) && ThisEvent.EventParam == LIGHT)
        {
            nextState = SEARCHING;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
        }
        
#endif   /* !DEBUG_FSM */
        break;
    }
/************************************************************/
    case SEARCHING:
    {
        if (ThisEvent.EventType == ES_ENTRY)
        {
            Roach_LEDSSet(0x2); // DEBUG -- Light 2nd LED on LED Bar
            /*
            // check that no bumpers are currently pressed. If they are, move
            // immediately to OBSTACLE_DETECTED
            if(Roach_ReadBumpers())
            {
                nextState = OBSTACLE_DETECTED;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
             * */
            
            ES_Timer_InitTimer(1, 5000);       // start 5 second timer
            altFlag = FALSE;
            moveForward();
        }
#if DEBUG_FSM
        // DEBUG -- State machine transition
        if(ThisEvent.EventType == BUMPER_PRESS)
        {
            nextState = OBSTACLE_DETECTED;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
        }
#endif  /* DEBUG_FSM */
        
#if !DEBUG_FSM
        /**
        * @brief When roach moves to searching, it will perform a series of tasks in a loop
         *      - Check if there is darkness. Return to IDLE if DARK
        *      - Clear a veer flag
         *      - Starts a 5 second timer
         *      - Begins moving forward
        *      - If state doesn't change and timer elapses:
        *          - Set a veer flag
        *          - starts the 5 second timer again
         *          - switches to veering right
        */
        
        // On every repetition, check if the light level is DARK. Return to IDLE if true
        if(ThisEvent.EventType == LIGHTLEVEL && ThisEvent.EventParam == DARK)
        {
            stopMoving();
            nextState = IDLE;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
        }
        
        if(ThisEvent.EventType == ES_TIMEOUT)
        {
            altFlag = !altFlag;
            if(altFlag)
            {
                turnRight();
                ES_Timer_InitTimer(1, 2000);
            }
            else
            {
                moveForward();
                ES_Timer_InitTimer(1, 5000);
            }
        }
        
        if(ThisEvent.EventType == BUMPER_PRESS)
        {
            stopMoving();
            ES_Timer_StopTimer(1);
            currentBumperState = ThisEvent.EventParam;
            printf("TRANSITION to Obstacle Detected: BumperState = %x\r\n", currentBumperState);
            nextState = OBSTACLE_DETECTED;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
        }
#endif   /* !DEBUG_FSM */
        break;
    }
/************************************************************/
    case OBSTACLE_DETECTED:
    {
        printf("OBSICLE DETECTED\r\n");
        // DEBUG -- Light 3rd LED on LED Bar
        if (ThisEvent.EventType == ES_ENTRY)
        {
            Roach_LEDSSet(0x4);
            altFlag = FALSE;
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
            ES_Timer_InitTimer(1, 2000);  // start 2 second timer
            //currentBumperState = 0x0;
        }
        
        if(ThisEvent.EventType == ES_TIMEOUT)
        {
            stopMoving();
            nextState = SEARCHING;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
            
        }
        if (ThisEvent.EventType == BUMPER_PRESS) 
        {
            stopMoving();  //if new bumper press, stop moving
            currentBumperState = ThisEvent.EventParam;
            if (currentBumperState & 0b1000 || currentBumperState & 0b0100) 
            {
                moveAway_RB();  //if rear bumpers pressed at all, escape forwards
                printf("MOVE RB\r\n");
            } 
            else 
            {
                moveAway_FB();  //if no rear bumpers hit, escape backwards
                printf("MOVE FB\r\n");
            }
            ES_Timer_InitTimer(1, 2000);  // restart 2 second timer
            //currentBumperState = 0x0;
        }
#if DEBUG_FSM
        // DEBUG -- State machine transition
        if(ThisEvent.EventType == BUMPER_PRESS)
        {
            nextState = IDLE;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
        }
#endif  /* DEBUG_FSM */
        
        // On every repetition, check if the light level is DARK. Return to IDLE if true
        if(ThisEvent.EventType == LIGHTLEVEL && ThisEvent.EventParam == DARK)
        {
            nextState = IDLE;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
        }
        
        
        // upon state transition, start 1 second timer (TIMER 1)  (use ENTRY_EVENT)
        // while timer is running, reverse veer right away from bumper press
        // check if the light level has changed from LIGHT to DARK
        // if so, stop moving and change state to IDLE
        // otherwise, check if another bumper has been pressed
        // if so, stop moving and reset the timer
        // otherwise, if timer has expired return to SEARCHING state
        break;
    }
    default:
        break;
    } 
    
    /* Provided-code -- Not necessary to change  */
    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        makeTransition = FALSE;
        RunFSM(EXIT_EVENT);
        CurrentState = nextState;
        RunFSM(ENTRY_EVENT);
    }
    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/

void moveForward()
{
    Roach_LeftMtrSpeed(STANDARD_SPEED);
    Roach_RightMtrSpeed(STANDARD_SPEED);
}
void moveBackward()
{
    Roach_LeftMtrSpeed(REVERSE_SPEED);
    Roach_RightMtrSpeed(REVERSE_SPEED);
}
void turnRight()
{
    Roach_LeftMtrSpeed(STANDARD_SPEED);
    Roach_RightMtrSpeed(REVERSE_TURN);
}
void stopMoving()
{
    Roach_LeftMtrSpeed(0);
    Roach_RightMtrSpeed(0);
}
void moveAway_FB()
{
    Roach_LeftMtrSpeed(REVERSE_TURN);
    Roach_RightMtrSpeed(REVERSE_SPEED);
}
void moveAway_RB()
{
    Roach_LeftMtrSpeed(STANDARD_SPEED);
    Roach_RightMtrSpeed(STANDARD_TURN);
}