/*
 * File:   BOAT_Movement
 * Author: Nicholas Kuipers
 *
 * Created on May 13, 2023 at 6:12PM
 *
 * Abstract: Driver code for mecanum wheels
 * 
 * @note This is designed specifically for a 4-wheel orientation with the front
 *      two wheels arranged "in-ward" (their 45-degree orientations from top-down
 *      angle inward) and the bottom two wheels arranged outward
 */

#include <BOARD.h>
#include <BOAT.h>
#include <BOAT_Movement.h>
#include <BOAT_Launcher.h>
#include <BOAT_PinDefs.h>
#include <xc.h>

#include <stdio.h>
#include <math.h>
#include <pwm.h>
#include <serial.h>
#include <AD.h>

/*******************************************************************************
 * PRIVATE #DEFINES                                                             *
 ******************************************************************************/

// Set if you want debug information printed to serial monitor
#define DEBUG_BOATMOVEMENT         1

// Driver values
#define BOAT_MAX_SPEED    100

/*******************************************************************************
 * PRIVATE VARIABLES                                                           *
 ******************************************************************************/

/*******************************************************************************
 * PRIVATE TYPEDEFS                                                             *
 ******************************************************************************/

/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/*******************************************************************************
 * PUBLIC FUNCTION IMPLEMENTATIONS                                             *
 ******************************************************************************/

/**
 * @Function BOAT_InitMotors(void)
 * @param None.
 * @return None.
 * @brief Initializes the motors for the BOAT, including their pins.
 *      - Sets the PWM pins, since the four driving motors rely on PWM signals to drive
 *      - Each motor has two direction pins (normal and inverted), which need to be initialized
 *          and set to 0
 * @author Nicholas Kuipers, 20230513
 */
void BOAT_MovementInit(void)
{
    // First, set up the PWM pins for the 4 DC motors attached to the mecanum wheels
    // PWM is initialized in the parent BOAT_Init() function
    PWM_AddPins(WHEEL_FRONT_LEFT_PWM | WHEEL_FRONT_RIGHT_PWM | WHEEL_REAR_LEFT_PWM | WHEEL_REAR_RIGHT_PWM);
    
    // Initialize all the direction pins for each motor
    WHEEL_FRONT_LEFT_DIR_TRIS       = 0;
    WHEEL_FRONT_LEFT_DIR_INV_TRIS   = 0;
    WHEEL_FRONT_RIGHT_DIR_TRIS      = 0;
    WHEEL_FRONT_RIGHT_DIR_INV_TRIS  = 0;
    WHEEL_REAR_LEFT_DIR_TRIS        = 0;
    WHEEL_REAR_LEFT_DIR_INV_TRIS    = 0;
    WHEEL_REAR_RIGHT_DIR_TRIS       = 0;
    WHEEL_REAR_RIGHT_DIR_INV_TRIS   = 0;

    // Set all direction pins for each motor to 0
    WHEEL_FRONT_LEFT_DIR            = 0;       // Forward direction pin
    WHEEL_FRONT_LEFT_DIR_INV        = 0;       // Reverse direction pin
    WHEEL_FRONT_RIGHT_DIR           = 0;
    WHEEL_FRONT_RIGHT_DIR_INV       = 0;
    WHEEL_REAR_LEFT_DIR             = 0;
    WHEEL_REAR_LEFT_DIR_INV         = 0;
    WHEEL_REAR_RIGHT_DIR            = 0;
    WHEEL_REAR_RIGHT_DIR_INV        = 0;

    printf("\r\nBOAT_MovementInit() completed successfully.");
}

/**
 * @Function BOAT_DriveMotor(MOTOR, int speed)
 * @param sel_motor, which motor to drive
 * @param speed, value from -1000 to 1000 to drive motor (duty cycle of PWM)
 * @return SUCCESS or ERROR
 * 
 * @brief This sets the speed and direction for the specified motor
 * @author Nicholas Kuipers, 20230513
 */
char BOAT_DriveMotor(MOTOR sel_motor, int speed)
{
    int driveSpeed = speed;
    switch(sel_motor)
    {
        case FRONT_LEFT:
        {
            if(speed < 0)     // if negative speed, motor will be driven in reverse
            {
                //driveSpeed = driveSpeed * -1;
                printf("\r\nFL DriveSpeed = %i", driveSpeed);
                driveSpeed = abs(driveSpeed);     // convert speed to a positive number
                WHEEL_FRONT_LEFT_DIR     = 0;
            }
            else                  // positive speed --> motor will be driven forward
                WHEEL_FRONT_LEFT_DIR     = 1;
            WHEEL_FRONT_LEFT_DIR_INV = ~WHEEL_FRONT_LEFT_DIR;   // Inverted direction pin opposite from direction pin
            if (PWM_SetDutyCycle(WHEEL_FRONT_LEFT_PWM, driveSpeed) == ERROR) 
            {
                printf("\r\nERROR: Setting PWM for motor (FL) in BOAT_DriveMotor");
                return ERROR;
            }
            break;
        }
        case FRONT_RIGHT:
        {
            if(speed < 0)     // if negative speed, motor will be driven in reverse
            {
                driveSpeed = abs(driveSpeed);     // convert speed to a positive number
                printf("\r\nFR DriveSpeed = %i", driveSpeed);
                WHEEL_FRONT_RIGHT_DIR     = 0;
            }
            else                  // positive speed --> motor will be driven forward
                WHEEL_FRONT_RIGHT_DIR     = 1;
            WHEEL_FRONT_RIGHT_DIR_INV = ~WHEEL_FRONT_RIGHT_DIR;   // Inverted direction pin opposite from direction pin
            if (PWM_SetDutyCycle(WHEEL_FRONT_RIGHT_PWM, driveSpeed) == ERROR)
            {
                printf("\r\nERROR: Setting PWM for motor (FR) in BOAT_DriveMotor");
                return ERROR;
            }
            break;
        }
        case REAR_LEFT:
        {
            if(speed < 0)     // if negative speed, motor will be driven in reverse
            {
                driveSpeed = abs(driveSpeed);     // convert speed to a positive number
                printf("\r\nRL DriveSpeed = %i", driveSpeed);
                WHEEL_REAR_LEFT_DIR     = 0;
            }
            else                  // positive speed --> motor will be driven forward
                WHEEL_REAR_LEFT_DIR     = 1;
            WHEEL_REAR_LEFT_DIR_INV = ~WHEEL_REAR_LEFT_DIR;   // Inverted direction pin opposite from direction pin
            if (PWM_SetDutyCycle(WHEEL_REAR_LEFT_PWM, driveSpeed) == ERROR)
            {
                printf("\r\nERROR: Setting PWM for motor (RL) in BOAT_DriveMotor");
                return ERROR;
            }
            break;
        }
        case REAR_RIGHT:
        {
            if(speed < 0)     // if negative speed, motor will be driven in reverse
            {
                driveSpeed = abs(driveSpeed);     // convert speed to a positive number
                printf("\r\nRR DriveSpeed = %i", driveSpeed);
                WHEEL_REAR_RIGHT_DIR     = 0;
            }
            else                  // positive speed --> motor will be driven forward
                WHEEL_REAR_RIGHT_DIR     = 1;
            WHEEL_REAR_RIGHT_DIR_INV = ~WHEEL_REAR_RIGHT_DIR;   // Inverted direction pin opposite from direction pin
            if (PWM_SetDutyCycle(WHEEL_REAR_RIGHT_PWM, driveSpeed) == ERROR)
            {
                printf("\r\nERROR: Setting PWM for motor (RR) in BOAT_DriveMotor");
                return ERROR;
            }
            break;
        }
    }
    return SUCCESS;
}

/**
 * @Function BOAT_MoveForward(int speed)
 * @param speed, speed the bot moves forward. Can be 0 - 1000 (BOAT_MAX_SPEED)
 * @return SUCCESS or ERROR
 * @brief Engages the motors to move the robot forward in a straight line
 *      (with respect to its current orientation)
 *      - For mecanum wheels, forward and backward movement is conducted by driving all four
 *          motors at the same rate in the same direction. For forward, each motor is driven
 *          in the normal direction
 * @author Nicholas Kuipers, 20230513
 */
char BOAT_MoveForward(int speed)
{
    uint8_t errorFlag = 0;
    // First, check if speed is within the 0 to max speed threshold. Throw an error if outside threshold
    if((speed < 0) || (speed > 1000))
        errorFlag = 1;
    
    // All four motors are driven at the same speed
    if(BOAT_DriveMotor(FRONT_LEFT,  speed) == ERROR)   errorFlag = 1;
    if(BOAT_DriveMotor(FRONT_RIGHT, speed) == ERROR)   errorFlag = 1;
    if(BOAT_DriveMotor(REAR_LEFT,   speed) == ERROR)   errorFlag = 1;
    if(BOAT_DriveMotor(REAR_RIGHT,  speed)  == ERROR)  errorFlag = 1;
    
    if(errorFlag)    // an error was encountered
    {
        printf("\r\nError encountered in BOAT_MoveForward");
        return ERROR;
    }
    else
    {
        printf("\r\nBOAT_MoveForward Success! Driven at %i speed", speed);
        return SUCCESS;
    }
}

/**
 * @Function BOAT_MoveBackward(int speed)
 * @param speed, speed the bot moves backward. Can be 0 - 1000 (BOAT_MAX_SPEED)
 * @return SUCCESS or ERROR
 * @brief Engages the motors to move the robot backward in a straight line
 *      (with respect to its current orientation)
 *      - For mecanum wheels, forward and backward movement is conducted by driving all four
 *          motors at the same rate in the same direction. For reverse, each motor is driven
 *          in the inverse direction
 * @author Nicholas Kuipers, 20230513
 */
char BOAT_MoveBackward(int speed)
{
    uint8_t errorFlag = 0;
    // First, check if speed is within the 0 to max speed threshold. Throw an error if outside threshold
    if((speed < 0) || (speed > 1000))
        errorFlag = 1;
    
    // All four motors are driven at the same speed
    if(BOAT_DriveMotor(FRONT_LEFT,  -speed) == ERROR)   errorFlag = 1;
    if(BOAT_DriveMotor(FRONT_RIGHT, -speed) == ERROR)   errorFlag = 1;
    if(BOAT_DriveMotor(REAR_LEFT,   -speed) == ERROR)   errorFlag = 1;
    if(BOAT_DriveMotor(REAR_RIGHT,  -speed) == ERROR)   errorFlag = 1;
    
    if(errorFlag)    // an error was encountered
    {
        printf("\r\nError encountered in BOAT_MoveBackward");
        return ERROR;
    }
    else
    {
        printf("\r\nBOAT_MoveBackward Success! Driven at %i speed", speed);
        return SUCCESS;
    }
}

/**
 * @Function BOAT_StrafeLeft(int speed)
 * @param speed, speed the bot moves to the left
 * @return SUCCESS or ERROR
 * @brief Robot strafes left at specified speed
 *      - For strafing, the wheel pairs move in tandem against the direction of the other pair
 *      - For left, FL, RR = driveBackwards and FR, RL = driveForwards
 * @author Nicholas Kuipers, 20230513
 */
char BOAT_StrafeLeft(int speed)
{
    uint8_t errorFlag = 0;
    // First, check if speed is within the 0 to max speed threshold. Throw an error if outside threshold
    if((speed < 0) || (speed > 1000))
        errorFlag = 1;

    // Front Left Motor, Rear-Right Motor are a pair. These drive in reverse
    if(BOAT_DriveMotor(FRONT_LEFT, -speed) == ERROR) errorFlag = 1;
    if(BOAT_DriveMotor(REAR_RIGHT, -speed) == ERROR) errorFlag = 1;

    // Front Right Motor, Rear-Left Motor are a pair. These drive forward
    if(BOAT_DriveMotor(FRONT_RIGHT, speed) == ERROR) errorFlag = 1;
    if(BOAT_DriveMotor(REAR_LEFT,   speed) == ERROR) errorFlag = 1;

    if(errorFlag)    // an error was encountered
    {
        printf("\r\nError encountered in BOAT_StrafeLeft");
        return ERROR;
    }
    else
    {
        printf("\r\nBOAT_StrafeLeft Success! Driven at %i speed", speed);
        return SUCCESS;
    }
}

/**
 * @Function BOAT_StrafeRight(int speed)
 * @param speed, speed the bot moves to the right
 * @return SUCCESS or ERROR
 * @brief Robot strafes right at specified speed
 * @author Nicholas Kuipers, 20230513
 */
char BOAT_StrafeRight(int speed)
{
    uint8_t errorFlag = 0;
    // First, check if speed is within the 0 to max speed threshold. Throw an error if outside threshold
    if((speed < 0) || (speed > 1000))
        errorFlag = 1;

    // Front Left Motor, Rear-Right Motor are a pair. These drive forward
    if(BOAT_DriveMotor(FRONT_LEFT, speed) == ERROR) errorFlag = 1;
    if(BOAT_DriveMotor(REAR_RIGHT, speed) == ERROR) errorFlag = 1;

    // Front Right Motor, Rear-Left Motor are a pair. These drive in reverse
    if(BOAT_DriveMotor(FRONT_RIGHT, -speed) == ERROR) errorFlag = 1;
    if(BOAT_DriveMotor(REAR_LEFT,   -speed) == ERROR)   errorFlag = 1;

    if(errorFlag)    // an error was encountered
    {
        printf("\r\nError encountered in BOAT_StrafeRight");
        return ERROR;
    }
    else
    {
        printf("\r\nBOAT_StrafeRight Success! Driven at %i speed", speed);
        return SUCCESS;
    }
}

/**
 * @Function BOAT_MoveInDirection(double direction, int speed)
 * @param angle, angle theta (radians) from x-axis the bot is moving (in straight line) (0 - 2pi).
 * @param speed, speed at which bot is moving (0 - 1000)
 * @return SUCCESS or ERROR
 * 
 * @brief Bot moves in a STRAIGHT line pertaining to a specified direction and speed. 
 *      Front-Right and Back-Left wheels are driven by: y = sin(x - 1/4pi)
 *      Front-Left and Back-Right wheels are driven by: y = sin(x + 1/4pi)
 * @note Both parameters are sent in via the state machine, where this function is inherently called from.
 *          - The direction is decided by sensor data and state estimation
 *          - The speed is decided by the state machine itself (i.e. different states have different speeds)
 * @author Nicholas Kuipers, 20230513
 */
char BOAT_MoveInStraightLine(double angle, int speed)
{
    double magnitude_PairA = 0;
    double magnitude_PairB = 0;
    double radianOffset = (1/4) * 3.1415926535;      // 1/4*pi used by magnitude calculations
    uint8_t errorFlag = 0;

    // First, check if speed is within the 0 to max speed threshold. Throw an error if outside threshold
    if((speed < 0) || (speed > 1000))
        errorFlag = 1;

    /*
    *   Mecanum wheels allow for the bot to move in a straight line in any direction, given an angle and desired speed.
    *   The wheels are bound in pairs and follow a simple calculation to determine how to drive each motor:
    *       - Front-Right, Back-Left wheels:    y = sin(angle - 1/4pi)     (Pair A)
    *       - Front-Left, Back-Right wheels:    y = sin(angle + 1/4pi)     (Pair B)
    *   These magnitudes are then compared with the ratio of speed/max_speed to determine how quickly to drive the
    *       BOAT in the indicated direction
    */

   // Determine the magnitude driven by the motor pairs to drive in specified direction
   magnitude_PairA = sin(angle - radianOffset);
   magnitude_PairB = sin(angle + radianOffset);
   
   // The magnitude * speed determines the rate at which each pair of motors is driven
   // Pair A 
   if(BOAT_DriveMotor(FRONT_RIGHT, (int)(speed * magnitude_PairA)) == ERROR) errorFlag = 1;
   if(BOAT_DriveMotor(REAR_LEFT,   (int)(speed * magnitude_PairA)) == ERROR) errorFlag = 1;
   // Pair B
   if(BOAT_DriveMotor(FRONT_LEFT, (int)(speed * magnitude_PairB)) == ERROR)  errorFlag = 1;
   if(BOAT_DriveMotor(REAR_RIGHT, (int)(speed * magnitude_PairB)) == ERROR)  errorFlag = 1;

   if(errorFlag)    // an error was encountered
    {
        printf("\r\nError encountered in BOAT_MoveInStraightLine");
        return ERROR;
    }
    else
    {
        printf("\r\nBOAT_MoveInStraightLine Success! Driven at %i speed", speed);
        return SUCCESS;
    }
}

/**
 * @Function BOAT_SpinCCW(int speed)
 * @param speed, speed the bot turns to the left
 * @return SUCCESS or ERROR
 * @brief Robot spins CCW in place at specified speed
 * @note Bot is stationary, axis of rotation is at the center of the bot
 * @author Nicholas Kuipers, 20230513
 */
char BOAT_SpinCCW(int speed)
{
    printf("\r\nEntered BOAT_SpinCCW");
    uint8_t errorFlag = 0;
    // First, check if speed is within the 0 to max speed threshold. Throw an error if outside threshold
    if((speed < 0) || (speed > 1000))
    {
        errorFlag = 1;
        printf("\r\nError in speed");
    }
    
    if(BOAT_DriveMotor(FRONT_LEFT,  -speed)  == ERROR) 
    {
        errorFlag = 1;
        printf("\r\nError with FRONT_LEFT DriveMotor");
    }
    if(BOAT_DriveMotor(FRONT_RIGHT, speed)      == ERROR) 
    {
        errorFlag = 1;
        printf("\r\nError with FRONT RIGHT DriveMotor");
    }
    if(BOAT_DriveMotor(REAR_LEFT,   -speed)      == ERROR) 
    {
        errorFlag = 1;
        printf("\r\nError with REAR LEFT DriveMotor");
    }
    if(BOAT_DriveMotor(REAR_RIGHT,   speed) == ERROR) 
    {
        errorFlag = 1;
        printf("\r\nError with REAR_LEFT DriveMotor");
    }
    
    if(errorFlag)    // an error was encountered
    {
        printf("\r\nError encountered in BOAT_SpinCCW");
        return ERROR;
    }
    else
    {
        printf("\r\nBOAT_SpinCCW Success! Driven at %i speed", speed);
        return SUCCESS;
    }
}

/**
 * @Function BOAT_TurnRight(int speed)
 * @param speed, speed the bot turns to the right
 * @return SUCCESS or ERROR
 * @brief Robot turns right at specified speed
 * @note Bot is stationary, axis of rotation is at the center of the bot
 * @author Nicholas Kuipers, 20230513
 */
char BOAT_SpinCW(int speed)
{
    uint8_t errorFlag = 0;
    // First, check if speed is within the 0 to max speed threshold. Throw an error if outside threshold
    if((speed < 0) || (speed > 1000))
        errorFlag = 1;
    
    BOAT_StopMovement();
    
    if(BOAT_DriveMotor(FRONT_LEFT,  speed)  == ERROR) errorFlag = 1;
    if(BOAT_DriveMotor(FRONT_RIGHT, -speed)      == ERROR) errorFlag = 1;
    if(BOAT_DriveMotor(REAR_LEFT,   speed)      == ERROR) errorFlag = 1;
    if(BOAT_DriveMotor(REAR_RIGHT,   -speed) == ERROR) errorFlag = 1;
    
    if(errorFlag)    // an error was encountered
    {
        printf("\r\nError encountered in BOAT_SpinCW");
        return ERROR;
    }
    else
    {
        printf("\r\nBOAT_SpinCW Success! Driven at %i speed", speed);
        return SUCCESS;
    }
}

/**
 *  @Function BOAT_StopMovement()
 *  @param none
 *  @return SUCCESS or ERROR
 *  @brief Reverts input pins to 0 and turns off all PWM signals
 *      to movement motors
 *  @author Nicholas Kuipers
 *
 */
char BOAT_StopMovement()
{
    uint8_t failFlag = 0;
    if(BOAT_MoveForward(0) == ERROR) failFlag = 1;
    WHEEL_FRONT_LEFT_DIR = 0;
    WHEEL_FRONT_RIGHT_DIR = 0;
    WHEEL_REAR_LEFT_DIR = 0;
    WHEEL_REAR_RIGHT_DIR = 0;
    
    if(failFlag)
        return ERROR;
    
    return TRUE;
}


#if TESTBENCH_MOVEMENT

int main()
{
    BOARD_Init();
    BOAT_Init();
    
    printf("\r\nMovement Test Bench active.");
    printf("\r\nPin Test: Using blocking code, drive motors forwards and backwards at 50% duty cycle to verify all pins functional");
    
    int speed = 500;
    while(1)
    {
        /*
        // Drive forward at 50% DC
        printf("\r\nDriving Forward.");
        if(BOAT_MoveForward(speed) == ERROR)
            printf("\r\nERROR: BOAT_MoveForward");
        for(int i = 0; i < 5000000; i++){}
         */
        /*
        printf("\r\nCascade Motor Test. FL, FR, RL, RR");
        printf("\r\nFront Left ON");
        BOAT_DriveMotor(FRONT_LEFT, speed);
        for(int i = 0; i < 2000000; i++);
        printf("\r\nFront Right ON");
        BOAT_DriveMotor(FRONT_RIGHT, speed);
        for(int i = 0; i < 2000000; i++);
        printf("\r\nRear Left ON");
        BOAT_DriveMotor(REAR_LEFT, speed);
        for(int i = 0; i < 2000000; i++);
        printf("\r\nRear Right ON");
        BOAT_DriveMotor(REAR_RIGHT, speed);
        for(int i = 0; i < 2000000; i++);
        
        printf("\r\nFront Left OFF");
        BOAT_DriveMotor(FRONT_LEFT, 0);
        for(int i = 0; i < 2000000; i++);
        printf("\r\nFront Right OFF");
        BOAT_DriveMotor(FRONT_RIGHT, 0);
        for(int i = 0; i < 2000000; i++);
        printf("\r\nRear Left OFF");
        BOAT_DriveMotor(REAR_LEFT, 0);
        for(int i = 0; i < 2000000; i++);
        printf("\r\nRear Right OFF");
        BOAT_DriveMotor(REAR_RIGHT, 0);
        for(int i = 0; i < 2000000; i++);
        
        BOAT_DriveMotor(FRONT_LEFT, -speed);
        for(int i = 0; i < 2000000; i++);
        printf("\r\nFront Right ON");
        BOAT_DriveMotor(FRONT_RIGHT, -speed);
        for(int i = 0; i < 2000000; i++);
        printf("\r\nRear Left ON");
        BOAT_DriveMotor(REAR_LEFT, -speed);
        for(int i = 0; i < 2000000; i++);
        printf("\r\nRear Right ON");
        BOAT_DriveMotor(REAR_RIGHT, -speed);
        for(int i = 0; i < 2000000; i++);
        
        printf("\r\nFront Left OFF");
        BOAT_DriveMotor(FRONT_LEFT, 0);
        for(int i = 0; i < 2000000; i++);
        printf("\r\nFront Right OFF");
        BOAT_DriveMotor(FRONT_RIGHT, 0);
        for(int i = 0; i < 2000000; i++);
        printf("\r\nRear Left OFF");
        BOAT_DriveMotor(REAR_LEFT, 0);
        for(int i = 0; i < 2000000; i++);
        printf("\r\nRear Right OFF");
        BOAT_DriveMotor(REAR_RIGHT, 0);
        for(int i = 0; i < 2000000; i++);
        
        printf("\r\nCascade Motor Test complete.");
        for(int i = 0; i < 200000; i++);
         */
        
        printf("\r\nForward and Back Test");
        printf("\r\nMoving Forward...");
        BOAT_MoveForward(speed);
        for(int i = 0; i < 2000000; i++);
        printf("\r\nStopping...");
        BOAT_StopMovement();
        for(int i = 0; i < 2000000; i++);
        printf("\r\nMoving Backward...");
        BOAT_MoveBackward(speed);
        for(int i = 0; i < 2000000; i++);
        printf("\r\nStopping...");
        BOAT_StopMovement();
        for(int i = 0; i < 2000000; i++);
        printf("\r\nForward and Backward Test complete");
        
        printf("\r\nStrafe Test");
        printf("\r\nStrafe Left...");
        BOAT_StrafeLeft(speed);
        for(int i = 0; i < 2000000; i++);
        printf("\r\nStopping...");
        BOAT_StopMovement();
        for(int i = 0; i < 2000000; i++);
        printf("\r\nStrafe Right...");
        BOAT_StrafeRight(speed);
        for(int i = 0; i < 2000000; i++);
        printf("\r\nStopping...");
        BOAT_StopMovement();
        for(int i = 0; i < 2000000; i++);
        printf("\r\nStrafe Test complete");
        
        
        
        
        printf("\r\nSpin Test");
        printf("\r\nSpin CounterClockWise...");
        BOAT_SpinCCW(speed);
        for(int i = 0; i < 2000000; i++);
        printf("\r\nStopping...");
        BOAT_StopMovement();
        for(int i = 0; i < 2000000; i++);
        printf("\r\nSpin Clockwise...");
        BOAT_SpinCW(speed);
        for(int i = 0; i < 2000000; i++);
        printf("\r\nStopping...");
        BOAT_StopMovement();
        for(int i = 0; i < 2000000; i++);
        printf("\r\nSpin Test complete");
        
        /*
        printf("\r\nMove in Straight Line Test...");
        BOAT_MoveInStraightLine(145, speed);
        for(int i = 0; i < 3000000; i++);
        printf("\r\nStopping...");
         */
        
        
        
        
        
        
        
        
        
        
        
        /*
        printf("\r\nMoving Forward...");
        BOAT_MoveForward(500);
        for(int i = 0; i < 3000000; i++);
        
        printf("\r\nStopping...");
        BOAT_StopMovement();
        for(int i = 0; i < 3000000; i++);
        
        printf("\r\nMoving Backward...");
        BOAT_MoveBackward(500);
        for(int i = 0; i < 3000000; i++);
        
        printf("\r\nStopping...");
        BOAT_StopMovement();
        for(int i = 0; i < 3000000; i++);
        
        /*
        printf("\r\nStrafing Right...");
        BOAT_StrafeRight(500);
        for(int i = 0; i < 3000000; i++);
        
        printf("\r\nStopping...");
        BOAT_StopMovement();
        for(int i = 0; i < 3000000; i++);
        
        printf("\r\nStrafing Left...");
        BOAT_StrafeLeft(500);
        for(int i = 0; i < 3000000; i++);
        
        printf("\r\nStopping...");
        BOAT_StopMovement();
        for(int i = 0; i < 3000000; i++);
        */
        //*/
        
        /*
        // Front wheels are inverse of rear wheels
        WHEEL_FRONT_LEFT_DIR = 1;
        WHEEL_FRONT_LEFT_DIR_INV = 0;
        WHEEL_FRONT_RIGHT_DIR = 1;
        WHEEL_FRONT_RIGHT_DIR_INV = 0;
        WHEEL_REAR_LEFT_DIR = 1;
        WHEEL_REAR_LEFT_DIR_INV = 0;
        WHEEL_REAR_RIGHT_DIR = 1;
        WHEEL_REAR_RIGHT_DIR_INV = 0;
        if(PWM_SetDutyCycle(WHEEL_FRONT_LEFT_PWM, speed) == ERROR) printf("\r\nERROR");      // 50% Duty Cycle Test
        PWM_SetDutyCycle(WHEEL_FRONT_RIGHT_PWM, speed);      // 50% Duty Cycle Test
        PWM_SetDutyCycle(WHEEL_REAR_LEFT_PWM, speed);      // 50% Duty Cycle Test
        PWM_SetDutyCycle(WHEEL_REAR_RIGHT_PWM, speed);      // 50% Duty Cycle Test
        for(int i = 0; i < 5000000; i++){}
        
        
        
        // Slow to 0
        printf("\r\nStopping.");
        WHEEL_FRONT_LEFT_DIR = 0;
        WHEEL_FRONT_RIGHT_DIR = 0;
        WHEEL_REAR_LEFT_DIR = 0;
        WHEEL_REAR_RIGHT_DIR = 0;
        PWM_SetDutyCycle(WHEEL_FRONT_LEFT_PWM, 0);
        PWM_SetDutyCycle(WHEEL_FRONT_RIGHT_PWM, 0); 
        PWM_SetDutyCycle(WHEEL_REAR_LEFT_PWM, 0);   
        PWM_SetDutyCycle(WHEEL_REAR_RIGHT_PWM, 0); 
        for(int i = 0; i < 3000000; i++){}
        
        // Drive backward at 50% DC
        printf("\r\nDriving backward");
        WHEEL_FRONT_LEFT_DIR = 0;
        WHEEL_FRONT_LEFT_DIR_INV = 1;
        WHEEL_FRONT_RIGHT_DIR = 0;
        WHEEL_FRONT_RIGHT_DIR_INV = 1;
        WHEEL_REAR_LEFT_DIR = 0;
        WHEEL_REAR_LEFT_DIR_INV = 1;
        WHEEL_REAR_RIGHT_DIR = 0;
        WHEEL_REAR_RIGHT_DIR_INV = 1;
        PWM_SetDutyCycle(WHEEL_FRONT_LEFT_PWM, speed);      // 50% Duty Cycle Test
        PWM_SetDutyCycle(WHEEL_FRONT_RIGHT_PWM, speed);      // 50% Duty Cycle Test
        PWM_SetDutyCycle(WHEEL_REAR_LEFT_PWM, speed);      // 50% Duty Cycle Test
        PWM_SetDutyCycle(WHEEL_REAR_RIGHT_PWM, speed);      // 50% Duty Cycle Test
        for(int i = 0; i < 3000000; i++){}
        
        // Slow to 0
        printf("\r\nStopping.");
        WHEEL_FRONT_LEFT_DIR_INV = 0;
        WHEEL_FRONT_RIGHT_DIR_INV = 0;
        WHEEL_REAR_LEFT_DIR_INV = 0;
        WHEEL_REAR_RIGHT_DIR_INV = 0;
        PWM_SetDutyCycle(WHEEL_FRONT_LEFT_PWM, 0);
        PWM_SetDutyCycle(WHEEL_FRONT_RIGHT_PWM, 0); 
        PWM_SetDutyCycle(WHEEL_REAR_LEFT_PWM, 0);   
        PWM_SetDutyCycle(WHEEL_REAR_RIGHT_PWM, 0);
        for(int i = 0; i < 3000000; i++){}
        
        */
        
        //if(speed < 1000)
        //    speed = speed + 100;
    }
}

#endif /* TESTBENCH_MOVEMENT */