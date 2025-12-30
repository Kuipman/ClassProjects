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
 *          - AT_1PT: (Sub-State Machine)
 *              - Reached upon tape event and RZ_EXIT = FALSE
 *              - CENTERING: Bot uses ToF sensor on BOT_FIELD_SIDE to strafe 400mm (~16in) from that side wall.
 *                      - If neither side wall is within 400mm, bot moves to closer side wall until it is 400mm away
 *              - COLLISION: Entered during CENTERING if bot sees an obstacle on its opposite ToF sensor (range of < 50mm),
 *                      or experiences a corner bumper event.
 *                          - If ToF event: if bot is within 100mm of the 400mm from the side wall, TURN_FLAG is set to TRUE and bot spins slowly
 *                              (CCW if BOT_FIELD_SIDE = RIGHT and CW otherwise) for 0.5 seconds. Otherwise, obstacle must be on the bot's side of the field.
 *              - Bot uses ToF sensor on BOT_FIELD_SIDE to strafe 400mm away from that wall
 *              - If other ToF sensor detects an obstacle (ranging < 500mm - initialDistanceFromWall) or encounters a bumper event, go into collision detection
 *           - FIRING: 
 * 
 *           - RETURNING:
 * 
 * 
 */


/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BOARD.h"
#include "BOAT_HSM.h"
#include "BumperService.h"
#include <stdio.h>

#include "BOAT_SubHSM_Orienting.h"
#include "BOAT_SubHSM_MoveToPosition.h"
#include "BOAT_SubHSM_At1Pt.h"
#include "BOAT_SubHSM_Firing.h"
#include "BOAT_SubHSM_Returning.h"

#include "BOAT.h"
#include "BOAT_Sensors.h"
#include "BOAT_Movement.h"
/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/

#define STANDARD_SPEED  1000
#define STANDARD_TURN   750
#define REVERSE_SPEED   1000
#define SLOW_SPEED      600
#define SLOW_TURN       500

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/


typedef enum {
    INIT,
    STANDBY,
    ORIENTING,
    MOVE_TO_POSITION,
    AT_1PT,
    FIRING,
    RETURNING,
            
    INIT_FAIL
} HSMState_t;

typedef enum {
    UNKNOWN_FIELD,
    LEFT_FIELD,
    CENTER_FIELD,
    RIGHT_FIELD,
} FIELD_SIDE;

static const char *StateNames[] = {
    "INIT",
	"STANDBY",
    "ORIENTING",
    "MOVE_TO_POSITION",
    "AT_1PT",
    "FIRING",
    "RETURNING",
    
    "INIT_FAIL"
};


/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
//void moveForward();
//void moveBackward();
//void turnRight();
//void stopMoving();
//void moveAway_FB();
//void moveAway_RB();
/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                            *
 ******************************************************************************/

// ES Framework variables
static HSMState_t CurrentState; // <- change enum name to match ENUM
static uint8_t MyPriority;

// Boolean Flags
static uint8_t RZ_EXIT;       // denotes when bot moved outside of reload zone, toggled by timer5
static uint8_t TURN_FLAG;    // used for center field collisions, bot turns to aim at goal if obstacle is in center of the field

FIELD_SIDE BOT_FIELD_SIDE;        // bot's starting side on the field
FIELD_SIDE OBS_FIELD_SIDE;        // obstacle's side of field

// ToF Sensor Values
static unsigned int TOF_Left, TOF_Right, TOF_Rear;

//static uint8_t currentBumperState;   // Tracks the state of bumpers for obstacle detection
//static uint8_t altFlag;   // boolean that operates differently depending on state
//static uint8_t timerRunning;   // boolean, active whenever timer 1 is running


/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function BOAT_InitHSM(uint8_t)
 * @brief Called by the framework at beginning of code execution to initialize
 *      the hierarchical state machine and its sub-state machines
 * @note Will post an ES_INIT event to the appropriate queue, which is handled in the
 *      BOAT_RunHSM() function.
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE if success, FALSE otherwise
 */
uint8_t InitHSM(uint8_t Priority)
{
    // ES Framework Initializations
    MyPriority = Priority;
    CurrentState = INIT;
    
    // Sub-State Machine Initializations
    /*
    InitSubHSM_Orienting();
    InitSubHSM_MoveToPosition();
    InitSubHSM_At1Pt();
    InitSubHSM_Firing();
    InitSubHSM_Returning();
     * */
    
    // Global Variable Initializations
    RZ_EXIT   = FALSE;
    TURN_FLAG = FALSE;
    BOT_FIELD_SIDE  = UNKNOWN_FIELD;
    OBS_FIELD_SIDE  = UNKNOWN_FIELD;
    
    TOF_Left = 0;
    TOF_Right = 0;
    TOF_Rear = 0;
    
    
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
 *      queue for later operation by BOAT_RunHSM()
 * @param ThisEvent - Event with a type and parameter
 * @return TRUE if success, FALSE otherwise
 */
uint8_t PostHSM(ES_Event ThisEvent)
{
    return ES_PostToService(MyPriority, ThisEvent);
}

/**
 * @Function RunHSM(ES_Event ThisEvent)
 * @param ThisEvent - event (type and param) to be responded to by the state machine
 * @brief Runs and updates the Boat Hierarchical State Machine as needed. Function is called
 *      recursively to implement the correct order for a state transition by exiting the current
 *      state and entering the new state using the ES_EXIT and ES_ENTRY events
 * @note See description at top of file for information on structure of state machine
 * @return return event type - in general should be ES_NO_EVENT but can have other values
 *      during events of recursion
 */
ES_Event RunHSM(ES_Event ThisEvent)
{
    uint8_t makeTransition = FALSE; // use to flag transition
    HSMState_t nextState; // <- need to change enum type here
    ES_Tattle(); // trace call stack


/**
 * HIERARCHICAL STATE MACHINE START
**/
switch (CurrentState) {
    case INIT: // If current state is initial Pseudo State
    {
        if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
        {
            // this is where you would put any actions associated with the
            // transition from the initial pseudo-state into the actual
            // initial state
            // Initialize all sub-state machines
            
            // now put the machine into the actual initial state
            nextState = STANDBY;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
        }
        break;
    }

    /*
     * STANDBY
     * @brief State remains here until bot experiences a SWITCH_EVENT, specifically the pin moving
     *      from low to high (as determined by switch event). Then, this moves straight to ORIENTING
     */
    case STANDBY: // in the first state, replace this with correct names
        // run sub-state machine for this state
        //NOTE: the SubState Machine runs and responds to events before anything in the this
        //state machine does
    {
        switch (ThisEvent.EventType) {
        case SWITCH_EVENT:
            //InitSubHSM_Orienting();
            nextState = ORIENTING;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
        //case ES_NO_EVENT:
        default:
            break;
        }
        break;
    }
        
    /*
     * ORIENTING
     * @brief Will incorporate a SSM if more complex movement (i.e. straightening logic) can be implemented in time. Else:
     *      - Upon entry, checks if the 2k beacon is detected. If it is, state moves immediately to MOVE_TO_POSITION
     *      - Else, spins CCW until the 2k beacon is detected (BEACON_EVENT_2K), then stops spinning.
     *      - OPTION FOR SSM: Use the center tape and two center tape sensors
     * @note The substate machine runs and responds to events before anything else in this state machine
     */
    case ORIENTING:
    {
        
        // Upon entry, the bot checks if the 2k beacon detector is above the high threshold. If it is, SSM skips
        //  to STRAIGHTENING. Else, bot begins to spin CCW
        if(ThisEvent.EventType == ES_ENTRY)
        {
            if(BOAT_ReadBeacon_2k() >= BEACON_2K_HIGH_THRESHOLD)
            {
                //SSM to STRAIGHTENING
            }
            else
            {
                BOAT_SpinCCW(STANDARD_SPIN_SPEED);
            }
        }
        
        //ThisEvent = RunSubHSM_Orienting(ThisEvent);
        switch (ThisEvent.EventType) {
//        case POSITION_FINISHED:
//            InitNavigationSubHSM();
//            nextState = Navigate;
//            makeTransition = TRUE;
//            ThisEvent.EventType = ES_NO_EVENT;
        case ES_NO_EVENT:
        default:
            break;
        }
        break;
    }
   /*
     * MOVE_TO_POSITION
     * @brief Incorporates a SSM for collision-detection and tape detection purposes. In essence, this state performs:
     *      - Upon entry, bot begins moving forward towards the 2k beacon. A 3 second timer is started and ticks while moving forward.
     *      - If the bot experiences a collision, moves into COLLISON_DETECTED where it will back away from the obstacle, strafe left, then move forward again
     *      - After the 3 second timer expires, the next rear tape event will trigger the bot's next state
     * @note The substate machine runs and responds to events before anything else in this state machine
     */    
   case MOVE_TO_POSITION:
       ThisEvent = RunFirstSubHSM(ThisEvent);
       switch (ThisEvent.EventType) {
       case POSITION_FINISHED:
           InitNavigationSubHSM();
           nextState = Navigate;
           makeTransition = TRUE;
           ThisEvent.EventType = ES_NO_EVENT;
       case ES_NO_EVENT:
       default:
           break;
       }
       break;
       
   /*
     * AT_1PT
     * @brief Incorporates a SSM for collision-detection and final positioning purposes. Performs the following:
     *      - Upon entry, bot takes reading of the left and right ToF sensors. From the closer wall, bot will strafe until
     *          it reaches approximately 400mm from that wall.
     *      - If the bot experiences a collision, moves into COLLISON_DETECTED where it will back away from the obstacle, strafe left, then move forward again
     *      - After the 3 second timer expires, the next rear tape event will trigger the bot's next state
     * @note The substate machine runs and responds to events before anything else in this state machine
     */        
   case AT_1PT: // in the first state, replace this with correct names
       ThisEvent = RunFirstSubHSM(ThisEvent);
       switch (ThisEvent.EventType) {
       case POSITION_FINISHED:
           InitNavigationSubHSM();
           nextState = Navigate;
           makeTransition = TRUE;
           ThisEvent.EventType = ES_NO_EVENT;
       case ES_NO_EVENT:
       default:
           break;
       }
       break;
   

   case FIRING: // in the first state, replace this with correct names
       // run sub-state machine for this state
       //NOTE: the SubState Machine runs and responds to events before anything in the this
       //state machine does
       ThisEvent = RunFirstSubHSM(ThisEvent);
       switch (ThisEvent.EventType) {
       case POSITION_FINISHED:
           InitNavigationSubHSM();
           nextState = Navigate;
           makeTransition = TRUE;
           ThisEvent.EventType = ES_NO_EVENT;
       case ES_NO_EVENT:
       default:
           break;
       }
       break;
       
   case RETURNING: // in the first state, replace this with correct names
       // run sub-state machine for this state
       //NOTE: the SubState Machine runs and responds to events before anything in the this
       //state machine does
       ThisEvent = RunFirstSubHSM(ThisEvent);
       switch (ThisEvent.EventType) {
       case POSITION_FINISHED:
           InitNavigationSubHSM();
           nextState = Navigate;
           makeTransition = TRUE;
           ThisEvent.EventType = ES_NO_EVENT;
       case ES_NO_EVENT:
       default:
           break;
       }
       break;
    }    
    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunHSM(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunHSM(ENTRY_EVENT); // <- rename to your own Run function
    }



/**
 *BASIC STATE MACHINE END
**/


    
    
#if BLOCKSTATEMACHINE
    // Beginning of State Machine, operating as a switch/case
    switch (CurrentState) {
    case INIT: // If current state is initial Pseudo State
        if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
        {
            /*
             * Init states would happen here, purposefully leaving empty
             */
            
            printf("\r\nBOAT HSM started.");
            nextState = STANDBY;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
        }
        break;
/************************************************************/
    /*
     * STANDBY: Bot performs no actions until START event
     */
    case STANDBY:
    {
        if (ThisEvent.EventType == ES_ENTRY)
        {
            //if battery voltage drops below 9.0V, light the LED (done in AD.c's interrupt)
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
#endif
    
    ES_Tail(); // trace call stack end
    return ThisEvent;
}

/**
 * @Function ReadTOF(unsigned int leftToF, unsigned int rightToF, unsigned int backToF)
 * @param none
 * @return none
 * 
 * @brief Allows for the updateToF event to directly pass updated ToF measurements read
 *      from the analog pins (connected to ESP32) to the HSM.
 * @author Nicholas Kuipers
 */
void HSM_UpdateTOF(unsigned int leftToF, unsigned int rightToF, unsigned int backToF)
{ 
    TOF_Left  = BOAT_ReadTOF(LEFT_TOF);
    TOF_Right = BOAT_ReadTOF(RIGHT_TOF);
    TOF_Rear  = BOAT_ReadTOF(REAR_TOF);
}

/**
 * @Function ResetHSM(void)
 * @param none
 * @return none
 * 
 * @brief Called by a switch event from ON to OFF. Sets the HSM state back to STANDBY.
 * 
 * @author Nicholas Kuipers
 */
void ResetHSM(void)
{
    if(CurrentState != INIT && CurrentState != STANDBY)
        CurrentState = STANDBY;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/

/*
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
 * 
 * */