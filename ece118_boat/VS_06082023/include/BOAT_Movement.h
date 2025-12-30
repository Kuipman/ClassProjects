/*
 * File:   BOAT_Movement.h
 * Author: Nicholas Kuipers
 *
 * Created on May 13, 2023 at 4:55PM
 *
 * Abstract: Driver code for mecanum wheels
 * 
 * @note This is designed specifically for a 4-wheel orientation with the front
 *      two wheels arranged "in-ward" (their 45-degree orientations from top-down
 *      angle inward) and the bottom two wheels arranged outward
 */

#ifndef BOAT_MOVEMENT_H
#define BOAT_MOVEMENT_H

#include <BOARD.h>
#include <BOAT.h>

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/

#define BOAT_MAX_SPEED 100 

// Calibration Values
#define STANDARD_FORWARD_SPEED     700
#define STANDARD_REVERSE_SPEED     700
#define STANDARD_STRAFE_SPEED      700
#define STANDARD_SPIN_SPEED        500
#define SLOW_FORWARD_SPEED         400
#define SLOW_REVERSE_SPEED         400
#define SLOW_STRAFE_SPEED          400
#define SLOW_SPIN_SPEED            350

/*******************************************************************************
 * PUBLIC TYPEDEFS                                                             *
 ******************************************************************************/

typedef enum{
    FRONT_LEFT,
    FRONT_RIGHT,
    REAR_LEFT,
    REAR_RIGHT
}MOTOR;

/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/**
 * @Function BOAT_InitMotors(void)
 * @param None.
 * @return None.
 * 
 * @brief Initializes the motors for the BOAT, including their pins
 * @author Nicholas Kuipers, 20230513
 */
void BOAT_MovementInit(void);

/**
 * @Function BOAT_DriveMotor(MOTOR, int speed)
 * @param sel_motor, which motor to drive
 * @param speed, value from -100 to 100 to drive motor where 100 = max speed
 * @return SUCCESS or ERROR
 * 
 * @brief This sets the speed and direction for the specified motor
 * @author Nicholas Kuipers, 20230513
 */
char BOAT_DriveMotor(MOTOR sel_motor, int speed);

/**
 * @Function BOAT_MoveForward(int speed)
 * @param speed, speed the bot moves forward
 * @return SUCCESS or ERROR
 * 
 * @brief Engages the motors to move the robot forward in a straight line
 *      (with respect to its current orientation)
 * @author Nicholas Kuipers, 20230513
 */
char BOAT_MoveForward(int speed);

/**
 * @Function BOAT_MoveBackward(int speed)
 * @param speed, speed the bot moves backward
 * @return SUCCESS or ERROR
 * 
 * @brief Engages the motors to move the robot backward in a straight line
 *      (with respect to its current orientation)
 * @author Nicholas Kuipers, 20230513
 */
char BOAT_MoveBackward(int speed);

/**
 * @Function BOAT_StrafeLeft(int speed)
 * @param speed, speed the bot moves to the left
 * @return SUCCESS or ERROR
 * 
 * @brief Robot strafes left at specified speed
 * @author Nicholas Kuipers, 20230513
 */
char BOAT_StrafeLeft(int speed);

/**
 * @Function BOAT_StrafeRight(int speed)
 * @param speed, speed the bot moves to the right
 * @return SUCCESS or ERROR
 * 
 * @brief Robot strafes right at specified speed
 * @author Nicholas Kuipers, 20230513
 */
char BOAT_StrafeRight(int speed);

/**
 * @Function BOAT_MoveInStraightLine(double direction, int speed)
 * @param angle, angle theta (radians) from x-axis the bot is moving (in straight line) (0 - 2pi)
 * @param speed, speed at which bot is moving (0 - 100)
 * @return SUCCESS or ERROR
 * 
 * @brief Bot moves in a straight line pertaining to a specified direction and speed. 
 *      Front-Right and Back-Left wheels are driven by: y = sin(x - 1/4pi)
 *      Front-Left and Back-Right wheels are driven by: y = sin(x + 1/4pi)
 * @author Nicholas Kuipers, 20230513
 */
char BOAT_MoveInStraightLine(double angle, int speed);

/**
 * @Function BOAT_TurnLeft(int speed)
 * @param speed, speed the bot turns to the left
 * @return SUCCESS or ERROR
 * 
 * @brief Robot turns left at specified speed
 * @note Bot is stationary, axis of rotation is at the center of the bot
 * @author Nicholas Kuipers, 20230513
 */
char BOAT_SpinCCW(int speed);

/**
 * @Function BOAT_TurnRight(int speed)
 * @param speed, speed the bot turns to the right
 * @return SUCCESS or ERROR
 * 
 * @brief Robot turns right at specified speed
 * @note Bot is stationary, axis of rotation is at the center of the bot
 * @author Nicholas Kuipers, 20230513
 */
char BOAT_SpinCW(int speed);

/**
 *  @Function BOAT_StopMovement()
 *  @param none
 *  @return SUCCESS or ERROR
 *  @brief Reverts input pins to 0 and turns off all PWM signals
 *      to movement motors
 *  @author Nicholas Kuipers
 *
 */
char BOAT_StopMovement();

#endif    /* BOAT_MOVEMENT_H */
