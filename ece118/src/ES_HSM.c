/**
 * File: ES_HSM.c
 * Project: ECE 118 - Lab 0 Part 7
 * Authors: Josh Gamlen, Nick Kuipers
 * 
 * @brief Hierarchical State Machine designed to function with the ES_FRAMEWORK.
 *      HSM structured as follows:
 *          - IDLE
 *              - Light level is dark. Bumpers DO matter
 *                  - If bumper is pressed, move away until BUMPER_RELEASED, then set 1/2 second
 *                      timer and stop moving after TIMEOUT
 *                  - If in the light, change state to SEARCHING 
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
#include "BOARD.h"
#include "ES_HSM.h"
#include <stdio.h>
#include "ES_SubHSM.h" //#include all sub state machines called
/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/

#define STANDARD_SPEED  90
#define STANDARD_TURN   45
#define REVERSE_SPEED  -70
#define REVERSE_TURN   -50

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/


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

static HSMState_t CurrentState = INIT; // <- change enum name to match ENUM
static uint8_t MyPriority;
static uint8_t currentBumperState;   // Tracks the state of bumpers for obstacle detection
static uint8_t altFlag;   // boolean that operates differently depending on state
static uint8_t timerRunning;   // boolean, active whenever timer 1 is running


/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitHSM(uint8_t)
 * @brief Called by the framework at beginning of code execution to initialize
 *      the finite state machine.
 * @note Will post an ES_INIT event to the appropriate queue, which is handled in the
 *      RunFSM() function.
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE if success, FALSE otherwise
 */
uint8_t InitHSM(uint8_t Priority)
{
    MyPriority = Priority;
    // put us into the Initial PseudoState
    CurrentState = INIT;
    currentBumperState = 0;   // Tracks the state of bumpers for obstacle detection
    altFlag            = FALSE;   // boolean that operates differently depending on state
    timerRunning       = FALSE;   // boolean, active whenever timer 1 is running
    InitSubHSM();
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
uint8_t PostHSM(ES_Event ThisEvent)
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
ES_Event RunHSM(ES_Event ThisEvent)
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
        
        RunSubHSM(ThisEvent);

        // Change state to SEARCHING if the light has changed from DARK to LIGHT
        if((ThisEvent.EventType == LIGHTLEVEL) && ThisEvent.EventParam == LIGHT)
        {
            nextState = SEARCHING;
            //revert SSM to START
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
        }
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
        RunHSM(EXIT_EVENT);
        CurrentState = nextState;
        RunHSM(ENTRY_EVENT);
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
    Roach_LeftMtrSpeed(100);
    Roach_RightMtrSpeed(-100);
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