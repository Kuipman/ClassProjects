/*
 * File:   BOAT_Launcher.c
 * Author: Nicholas Kuipers
 *
 * Created on May 17, 2023 at 3:39PM
 *
 * Abstract: Child library of BOAT system responsible for driving the flywheel
 *      (DC motor w/ESC) and Stepper Motor (connection to H-Bridge)
 */

#include <BOARD.h>
#include <BOAT.h>
#include <BOAT_Movement.h>
#include <BOAT_Launcher.h>
#include <BOAT_PinDefs.h>
#include <xc.h>

#include <AD.h>
#include <stdio.h>
#include <math.h>
#include <pwm.h>
#include <serial.h>
#include <AD.h>
#include <timers.h>

/*******************************************************************************
 * PRIVATE #DEFINES                                                             *
 ******************************************************************************/

// Debug value, set to 1 if you want detailed print values to terminal
#define DEBUG_BOATLAUNCHER      1
 
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
 * @Function BOAT_LauncherInit(void)
 * @param None.
 * @return None.
 * @brief Initializes the pins and functionality required for the launcher
 *      - The Stepper Motor relies on a standard PWM signal
 *      - The Flywheel DC motor uses an ESC motor, which uses a servo-style PWM
 * @author Nicholas Kuipers, 20230517
 */
void BOAT_LauncherInit(void)
{
    PWM_AddPins(STEPPER_PWM);
    //PWM_SetDutyCycle(STEPPER_PWM, 200);      // 20% Duty Cycle Test
    //RC_AddPins(FLYWHEEL_ESC);
    //RC_SetPulseTime(FLYWHEEL_ESC, 1500);     // Sets the ESC at 0
    
    // Digital Output pin determines operation of stepper motor
    STEPPER_ENABLE_TRIS = 0;
    STEPPER_ENABLE = 0;
    
    if(DEBUG_BOATLAUNCHER)
        printf("\r\nBoat Launcher Initialization complete.");
}

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
char BOAT_SpinFlywheel(void)
{
    //RC_SetPulseTime(FLYWHEEL_ESC, 1750);     // Drives the ESC
}

/**
 * @Function BOAT_StopFlywheel(void)
 * @param None
 * @return SUCCESS or ERROR
 * 
 * @brief Cuts PWM signal to the ESC of the flywheel motor and stops the motor.
 * 
 * @author Nicholas Kuipers, 20230517
 */
char BOAT_StopFlywheel(void)
{
    //RC_SetPulseTime(FLYWHEEL_ESC, 1000);     // Sets the ESC at 0
}

/**
 * @Function BOAT_TurnFeeder(void)
 * @param None
 * @return SUCCESS or ERROR
 * 
 * @brief Spins the stepper motor 180 degrees, allowing for a single ball
 *      to be fed into the flywheel
 *          - boolean flag RUNNING
 *          - if !RUNNING
 *              - Turns on STEPPER_ENABLE
 *              - Starts timer for 1 second
 *              - RUNNING = true
 *          - if RUNNING
 *              - Turn off STEPPER_ENABLE
 *              - RUNNING = false
 * @note The first instance this is triggered comes after the flywheel has been given
 *      enough time to get to full spin
 * @author Nicholas Kuipers, 20230517
 */
char BOAT_TurnOnFeeder(void)
{
    STEPPER_ENABLE = 1;
}

/*
// PRIVATE FUNCTION
unsigned int convertADToESC_PWM(unsigned int AD_Val)
{
    if(AD_Val == 0)
        return 0;
    if(AD_Val > 1000)
        return 180;
    
    return (180/1023)*AD_Val; 
}
 * */

/*******************************************************************************
 * TEST BENCH - BOAT_Launcher.c                                                *
 ******************************************************************************/

#if TESTBENCH_LAUNCHER


/*
 *  Testbench performs the following:
 *      - Runs through initialization
 *      - Starts a timer that waits for 7 seconds (for the FLYWHEEL)
 *      - Starts a separate timer that runs every two seconds:
 *          - Upon expiry, drives the scooper for 1 second, then resets two second timer
 *      - Upon expiry of 7 second timer, increase the FLYWHEEL speed by ~50 every second
 */
int main()
{
   BOARD_Init();
   BOAT_Init();
   TIMERS_Init();
   
   int FLY_Value = 1500;
   int FLY_Reset = 0;
   int Stepper_ON = 0;
   
   TIMERS_InitTimer(1, 7000);     // Flywheel timer
   TIMERS_InitTimer(2, 2000);     // Stepper timer
   
   printf("\r\nLauncher Test Bench Active.");
   printf("\r\nTimers active.");
   
   while(1)
   {
       if(TIMERS_IsTimerExpired(1))    // Flywheel timer expired
       {
           printf("\r\nTimer 1 expired");
           if(FLY_Value == 2000)
           {
               TIMERS_InitTimer(1, 5000); // Timer runs for 5 seconds, then resets the motor
               FLY_Value = 1500;
               FLY_Reset = 1;
           }
           else if(FLY_Reset == 0)
           {
               FLY_Value += 50;
               RC_SetPulseTime(FLYWHEEL_ESC, FLY_Value);
               TIMERS_InitTimer(1, 500);
           }
           else
           {
               FLY_Reset = 0;
               RC_SetPulseTime(FLYWHEEL_ESC, 0);
               TIMERS_InitTimer(1, 3000);
           }
           printf("\r\nFLY_Value = %i", FLY_Value);
       }
       if(TIMERS_IsTimerExpired(2))     // Stepper timer expired
       {
           printf("\r\nTimer 2 expired  ");
           if(Stepper_ON == 0)
           {
               printf("\r\n Stepper ON");
               Stepper_ON = 1;
               TIMERS_InitTimer(2, 2000);
           }
           else
           {
               printf("\r\n Stepper OFF");
               Stepper_ON = 0;
               TIMERS_InitTimer(2, 2000);
           }
       }
       
   }
}







#endif   /* TESTBENCH_LAUNCHER */










/*
int main()
{
    BOARD_Init();
    BOAT_Init();
    AD_Init();
   
    printf("\r\nLauncher Test Bench active.");
    printf("\r\nTest 1: Drive both PWM pins and verify functionality over oscilloscope.");
    //Test 1: Drive both PWM pins, verify functionality
    
    //Test 1.5: Attempt a STOP signal to ESC to arm it
    PWM_SetDutyCycle(FLYWHEEL_ESC, 1000);
    printf("\r\nSending STOP message...");
    for(int i = 0; i < 1500000; i++) {}
    PWM_SetDutyCycle(FLYWHEEL_ESC, 95);
    printf("\r\nStop message concluded.");
    
    // Test 2: Drive variable PWM signal by reading a potentiometer to an analog pin
    AD_AddPins(AD_PORTV4);
    unsigned int potVal = 0;
    unsigned int prevPotVal = 0;
    unsigned int temp = 0;
    while(1)
    {
        potVal = AD_ReadADPin(AD_PORTV4);
        printf("\r\nPotVal: %i", potVal);
        if(potVal > 1000)
            potVal = 1000;
        if(prevPotVal != potVal)
        {
            float temp1 = 180.0 / 1023.0;
            printf("\r\nTemp1 = %i", temp1);
            float temp2 = temp1 * potVal;
            printf("  Temp2 = %f", temp2);
            //temp = (180/1023)*potVal;
            //printf("\r\nNew Val: %i:", temp);
            PWM_SetDutyCycle(FLYWHEEL_ESC, (int)temp2);
            prevPotVal = potVal;
        }
    }
    
    while(1);
}
 */

/*
int main()
{
    BOARD_Init();
    BOAT_Init();    // initializes BOAT-specific and UNO-operational libraries
    
    printf("\r\nLauncher Test Bench active.");
    printf("\r\nTest 1: Loop with blocking code: Turn on/off stepper motor every so often.");
    
    int toggle = 0;
    while(1)
    {
        if(toggle)
        {
            toggle = 1;
            STEPPER_ENABLE = 0;
        }
        else
        {
            toggle = 0;
            STEPPER_ENABLE = 1;
        }
        for(int i = 0; i < 150000; i++) {}
    }

    
}
 * */