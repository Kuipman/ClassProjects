/*
 * File:   BOAT.c
 * Author: Nicholas Kuipers
 *
 * Created on May 13, 2023 at 7:59PM
 *
 * Abstract: Parent library for BOAT system. Incorporates Movement, Launcher,
 *      and UART libraries.
 */

#include <BOARD.h>
#include <BOAT.h>
#include <BOAT_Movement.h>
#include <BOAT_Launcher.h>
#include <BOAT_Sensors.h>
#include <BOAT_PinDefs.h>
#include <xc.h>

#include <stdio.h>
#include <math.h>
#include <pwm.h>
#include <serial.h>
#include <AD.h>
#include <timers.h>    // just for the testbench

#include "ES_Configure.h"
#include "ES_Framework.h"

/*******************************************************************************
 * PRIVATE #DEFINES                                                             *
 ******************************************************************************/

#define PWM_FREQUENCY     1000

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
 * @brief Initializes the motors for the BOAT, including their pins
 * @author Nicholas Kuipers, 20230513
 */
void BOAT_Init(void)
{
    // First, initializes the support libraries for BOAT and its modules
    PWM_Init();
    PWM_SetFrequency(PWM_FREQUENCY);
    RC_Init();
    AD_Init();
    
    BOAT_MovementInit();
    BOAT_SensorsInit();
    //BOAT_LauncherInit();
    
    //SERIAL_Init();
    printf("\r\nBOAT_Init() completed successfully.");
}







#if TESTBENCH_MAIN
/**
 *  Test bench largely uses same structure as ES_Main, with some changes
 */

int main()
{
    ES_Return_t ErrorType;

    BOARD_Init();

    printf("Starting BOAT ES Framework\r\n");
    printf("using the 2nd Generation Events & Services Framework\r\n");

    // Hardware Initialization Function Calls
    BOAT_Init();

    // now initialize the Events and Services Framework and start it running
    ErrorType = ES_Initialize();
    if (ErrorType == Success) {
        ErrorType = ES_Run();

    }
    //if we got to here, there was an error
    switch (ErrorType) {
    case FailedPointer:
        printf("Failed on NULL pointer");
        break;
    case FailedInit:
        printf("Failed Initialization");
        break;
    default:
        printf("Other Failure: %d", ErrorType);
        break;
    }
    for (;;)
        ;
}
#endif

#if TESTBENCH_POC   // proof of concept test

void printPrompt()
{
    printf("\r\nPress a bumper to engage a test:");\
    printf("\r\nTop Left   = Movement front, back, left, right");
    printf("\r\nTop Right  = Launcher Protocol");
    printf("\r\nRear Left  = Measure Tape Sensors and Track Wire");
    printf("\r\nRear Right = Measure 1.5k and 2k beacon detectors");
}

void moveForwardBackTest(int speed)
{
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
}
int main()
{
    BOARD_Init();
    BOAT_Init();
    TIMERS_Init();    // just for this testbench
    
    FLYWHEEL_ON_TRIS = 0;
    FLYWHEEL_ON = 0;
    
    printf("\r\nStarting Proof of Concept Test.");
    printPrompt();
    uint8_t currentBumperValue = 0;
    uint8_t currentTapeValue = 0;
    uint8_t currentTrackWireValue = 0;
    int current1_5kValue = 0;
    int current2kValue = 0;
    
    while(1)
    {
        currentBumperValue = BOAT_ReadBumpers();
        //printf("\r\nCurrent Bumper Value: %i", currentBumperValue);
        if(currentBumperValue)
        {
            printf("\r\nBumper Value read: %i", currentBumperValue);
            if(currentBumperValue & 0b0001)     // Movement forward and reverse
            {
                printf("\r\nFront/Back Movement Test Selected...");
                moveForwardBackTest(500);
                if(BOAT_MoveForward(500) == ERROR) printf("\r\nBOAT_MoveForward ERROR");
                for(int i = 0; i < 10000; i++);
                BOAT_StopMovement();
                for(int i = 0; i < 10000; i++);
                if(BOAT_MoveBackward(500) == ERROR) printf("\r\nBOAT_MoveBackward ERROR");
                for(int i = 0; i < 10000; i++);
                BOAT_StopMovement();
                for(int i = 0; i < 10000; i++);
                if(BOAT_StrafeRight(500) == ERROR) printf("\r\nBOAT_StrafeRight ERROR");
                for(int i = 0; i < 10000; i++);
                BOAT_StopMovement();
                for(int i = 0; i < 10000; i++);
                if(BOAT_StrafeLeft(500) == ERROR) printf("\r\nBOAT_StrafeLeft ERROR");
                for(int i = 0; i < 10000; i++);
                BOAT_StopMovement();
                for(int i = 0; i < 10000; i++);
                printf("\r\nFront/Back Movement Test Complete\r\n");
                printPrompt();
            }
            else if(currentBumperValue & 0b0010)   // Movement left and right
            {
                printf("\r\nLauncher protocol begin");
                printf("\r\nSending high signal to ESP32 to begin Launcher protocol. Setting 10 second timer. Ending test on expiry.");
                
                FLYWHEEL_ON = 1;
                printf("\r\nFlywheel on");
                TIMERS_InitTimer(1, 1000); // sets 1 second timer
                while(TIMERS_IsTimerActive(1)) {}
                FLYWHEEL_ON = 0;
                
                TIMERS_InitTimer(1, 9000);    // sets 9 second timer
                while(TIMERS_IsTimerActive(1)) {}   // waits for timer to finish
                
                printf("\r\nLauncher protocol finished");
                printPrompt();
                
                
                /*
                printf("\r\nReading ToF Sensors...");
                printf("\r\nFor the next 20 seconds, read the current value of the analog pin updating the ToF sensors");
                for(int i = 0; i < 200000; i++)
                {
                    printf("\r\nLeft ToF Sensor = %i", BOAT_ReadTOF(LEFT_TOF));
                }
                printf("\r\nEnd of ToF Sensor Test.");
                printPrompt();
                 * */
                
            }
            else if(currentBumperValue & 0b0100)   // Measure tape and track wire sensors
            {
                printf("\r\nTape and Track Wire Test Selected...");
                printf("\r\nFor the next several seconds, manipulate the tape and track wires as needed to see activity");
                for(int i = 0; i < 10000; i++)
                {
                    currentTapeValue = BOAT_ReadTapeSensors();
                    currentTrackWireValue = BOAT_ReadTrackWireSensor();
                    printf("\r\nTrack Wire: %i    Tape Values: %i", currentTrackWireValue, currentTapeValue);
                }
                printf("\r\nTape and Track Wire Test Complete\r\n");
                printPrompt();
            }
            else if(currentBumperValue & 0b1000)   // Measure 1.5k and 2k beacon detectors
            {
                printf("\r\n1.5k and 2k Beacon Detector Test Selected");
                printf("\r\nFor the next several seconds, manipulate the 1.5k and 2k beacons as needed to see activity");
                for(int i = 0; i < 10000; i++)
                {
                    current1_5kValue = BOAT_ReadBeacon_1_5k();
                    current2kValue = BOAT_ReadBeacon_2k();
                    printf("\r\n1.5k = %i    2k = %i", current1_5kValue, current2kValue);
                }
                printf("\r\n1.5k and 2k Beacon Test Complete\r\n");
                printPrompt();
            }
            else
            {
                printf("\r\nNo Bumpers Read");
            }
        }
    }
    
    
    while(1);
}

#endif