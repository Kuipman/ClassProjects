/*
 * File:   BOAT_Launcher.h
 * Author: Nicholas Kuipers
 *
 * Created on May 13, 2023 at 5:15PM
 *
 * Abstract: Child library of BOAT system responsible for driving the flywheel
 *      (DC motor w/ESC) and Stepper Motor (connection to H-Bridge)
 *
 */

#ifndef BOAT_LAUNCHER_H
#define BOAT_LAUNCHER_H

#include <BOARD.h>

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
 * @Function BOAT_LauncherInit(void)
 * @param None.
 * @return None.
 * @brief Initializes the pins and functionality required for the launcher
 *      - Pin RD3/PORTY03 = Stepper Motor PWM
 *      - Pin RE0/PORTZ-11 = Flywheel_ON  (subject to change)
 * @author Nicholas Kuipers, 20230517
 */
void BOAT_LauncherInit(void);

/**
 * @Function BOAT_SpinFlywheel(void)
 * @param None
 * @return SUCCESS or ERROR
 * 
 * @brief Activates the DC motor on the flywheel via its ESC. Flywheel only
 *      spins one direction.
 * @note This is planned to trigger when the bot has stopped moving
 * @author Nicholas Kuipers, 20230517
 */
char BOAT_SpinFlywheel(void);

/**
 * @Function BOAT_StopFlywheel(void)
 * @param None
 * @return SUCCESS or ERROR
 * 
 * @brief Cuts PWM signal to the ESC of the flywheel motor and stops the motor.
 * 
 * @author Nicholas Kuipers, 20230517
 */
char BOAT_StopFlywheel(void);

/**
 * @Function BOAT_TurnFeeder(void)
 * @param None
 * @return SUCCESS or ERROR
 * 
 * @brief Spins the stepper motor 180 degrees, allowing for a single ball
 *      to be fed into the flywheel
 * @note The first instance this is triggered comes after the flywheel has been given
 *      enough time to get to full spin
 * @author Nicholas Kuipers, 20230517
 */
char BOAT_TurnFeeder(void);


#endif    /* BOAT_LAUNCHER_H */
