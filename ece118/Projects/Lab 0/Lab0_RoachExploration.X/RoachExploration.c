/**
 *  File:     RoachExploration.c
 *  Project:  ECE 118 - Lab 0 (Roach Exploration - Part 4)
 *  Author:   Nicholas Kuipers
 *
 */


#include <BOARD.h>
#include <roach.h>
#include <stdio.h>
#include <stdlib.h>
#include "xc.h"

#define ROACHEXPLORATION 1

/* Local Function Declarations */
void delay_ms(int milliseconds);
void blinkLEDBar(uint8_t numtimes);
void printInstructions();
uint8_t FrontLeftTest();
uint8_t FrontRightTest();
uint8_t RearLeftTest();
uint8_t RearRightTest();

#if ROACHEXPLORATION

int main() {
    
    BOARD_Init();
    Roach_Init();
    
    printf("\nRoach Exploration v0.1. Compiled on: %s at %s\n", __DATE__, __TIME__);
    printf("\r\nInitializing...");
    blinkLEDBar(4);
    printf("\r\nInitialization complete!");
    
    printInstructions();
    
    while(1)
    {
        if(Roach_ReadFrontLeftBumper())
        {
            FrontLeftTest();
            printInstructions();
        }
        else if(Roach_ReadFrontRightBumper())
        {
            FrontRightTest();
            printInstructions();
        }
        else if(Roach_ReadRearLeftBumper())
        {
            RearLeftTest();
            printInstructions();
        }
        else if(Roach_ReadRearRightBumper())
        {
            RearRightTest();
            printInstructions();
        }
    }
    
    
    while(1) {}     // End of program
}

#endif  /* ROACHEXPLORATION */

/* Local Function Implementations */
void delay_ms(int milliseconds)  // delay = 1000 --> one second
{
    double loop_count = milliseconds * 70;
    for(double i = 0; i < loop_count; i++);
}

void blinkLEDBar(uint8_t numtimes)
{
    Roach_LEDSSet(0);
    for (int i = 0; i < numtimes; i++) {
        Roach_LEDSSet(0xFFF);
        delay_ms(200);
        Roach_LEDSSet(0x000);
        delay_ms(200);
    }
}

void printInstructions()
{
    delay_ms(500);
    printf("\r\n\r\nTest Harness Instructions:\n");
    printf("\r\nFront Left Bumper  : Forwards/Backwards Movement Test\n");
    printf("\r\nFront Right Bumper : Turn Left, Right Movement Test\n");
    printf("\r\nRear Left Bumper   : Read the current light sensor value\n");
    printf("\r\nRear Right Bumper  : Read the current battery voltage\n");
    printf("\r\n");
}

/**
 * @brief Upon Front Left Bumper Press, performs the following test:
 *      - Blinks the LED bar for a few seconds
 *      - Both motors are set to +100 (drives forward)
 *          - Green half of LED bar lit
 *      - Both motors are set to -100 (drives backward)
 *          - Red half of LED bar lit
 *      - Motors stop. LED bar blinks for a few seconds. Test is over
 *
 *  @return 0 if success, 1 if an error is encountered
 */
uint8_t FrontLeftTest()
{
    printf("\r\nForwards/Backwards Movement Test starting...");
    blinkLEDBar(4);    // Standard indicator a test is about to occur
    // First Test: Drive the roach forward by +30 on both motors
    printf("\r\nDriving forward.");
    Roach_LeftMtrSpeed(100);
    Roach_RightMtrSpeed(100);
    Roach_LEDSSet(0xFC0);   // Left side of LED bar lit
    delay_ms(3000);
    printf("\r\nStopping...");
    // Stop the motors briefly
    Roach_LeftMtrSpeed(0);
    Roach_RightMtrSpeed(0);
    Roach_LEDSSet(0x0);
    delay_ms(2000);
    printf("\r\nDriving in reverse.");
    Roach_LeftMtrSpeed(-100);
    Roach_RightMtrSpeed(-100);
    Roach_LEDSSet(0x03F);   // Right side of LED bar lit
    delay_ms(3000);
    printf("\r\nStopping...");
    // Stop the motors briefly
    Roach_LeftMtrSpeed(0);
    Roach_RightMtrSpeed(0);
    Roach_LEDSSet(0x0);
    delay_ms(2000);
    printf("\r\nEnd of Forwards/Backwards Movement Test.");
    
    return 0;
}

/**
 * @brief Upon Front Right Bumper Press perform the following:
 *      - Drive left motor forward, right motor backward (sharp right turn)
 *      - Stop
 *      - Drive right motor forward, left motor backward (sharp left turn)
 *      - Stop
 * 
 * @return 0 if success, 1 if error
 */
uint8_t FrontRightTest()
{
    printf("\r\nTurn Left/Right Movement Test starting...");
    blinkLEDBar(4);    // Standard indicator a test is about to occur
    // First Test: Drive the roach forward by +30 on both motors
    printf("\r\nSharp Turn Right");
    Roach_LeftMtrSpeed(100);
    Roach_RightMtrSpeed(-100);
    Roach_LEDSSet(0xFC0);   // Left side of LED bar lit
    delay_ms(3000);
    printf("\r\nStopping...");
    // Stop the motors briefly
    Roach_LeftMtrSpeed(0);
    Roach_RightMtrSpeed(0);
    Roach_LEDSSet(0x0);
    delay_ms(2000);
    printf("\r\nSharp Turn Left.");
    Roach_LeftMtrSpeed(-100);
    Roach_RightMtrSpeed(100);
    Roach_LEDSSet(0x03F);   // Right side of LED bar lit
    delay_ms(3000);
    printf("\r\nStopping...");
    // Stop the motors briefly
    Roach_LeftMtrSpeed(0);
    Roach_RightMtrSpeed(0);
    Roach_LEDSSet(0x0);
    delay_ms(2000);
    printf("\r\nEnd of Turn Left/Right Movement Test.");
    
    return 0;
}
/**
 * @brief Reads the light sensor value and outputs to terminal a few times, then ends test
 * @return 0 if success, 1 if error
 */
uint8_t RearLeftTest()
{
    printf("\r\nReading the current light level...");
    delay_ms(500);
    for(int i = 0; i < 8; i++)
    {
        printf("\r\nLight level = %i", Roach_LightLevel());
        delay_ms(1000);
    }
    printf("\r\nEnd of Light Level Test.");
    return 0;
}
/**
 * @brief Reads the battery voltage value and outputs to terminal a few times, then ends test
 * @return 0 if success, 1 if error
 */
uint8_t RearRightTest()
{
    printf("\r\nReading the current battery voltage...");
    delay_ms(500);
    uint16_t batteryVoltage;
    for(int i = 0; i < 4; i++)
    {
        batteryVoltage = Roach_BatteryVoltage();     // returns a 10-bit value, each count = 32mV
        double trueVoltage = (batteryVoltage*32)/1000;  // converts 10-bit value to readable voltage
        printf("\r\nBattery Voltage = %.2f V", trueVoltage);
        delay_ms(1000);
    }
    printf("\r\nEnd of Battery Voltage Test.");
    return 0;
}
