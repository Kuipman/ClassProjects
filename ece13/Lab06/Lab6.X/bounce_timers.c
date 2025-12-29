// **** Include libraries here ****
// old bounce
// Standard libraries
#include <stdio.h>
#include <GenericTypeDefs.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// User libraries
#include "Leds_Lab06.h"


// **** Declare any datatypes here ****

//since the timer ISR is called 38 times per second, we set each max value for our timers to reflect that * however many seconds we want
#define TIMER_A_SETVAL 38*2
#define TIMER_B_SETVAL 38*3
#define TIMER_C_SETVAL 38*5

struct Timer {
    uint8_t event;
    int16_t timeRemaining;
};

// **** Define global, module-level, or external variables here ****
struct Timer timerA, timerB, timerC;  //these are declared here so the ISR can access these as well

// **** Declare function prototypes ****

int main(void)
{
    BOARD_Init();

    // Configure Timer 1 using PBCLK as input. This default period will make the LEDs blink at a
    // pretty reasonable rate to start.
    T1CON = 0; // everything should be off
    T1CONbits.TCKPS = 1; // 1:8 prescaler
    PR1 = 0xFFFF; // interrupt at max interval
    T1CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T1IF = 0; //clear the interrupt flag before configuring
    IPC1bits.T1IP = 4; // priority of  4
    IPC1bits.T1IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T1IE = 1; // turn the interrupt on

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    printf("Welcome to NKuipers' lab6 part1 (timers).  Compiled on %s %s.\n", __TIME__, __DATE__);
    //set initial values to their max values
    timerA.timeRemaining = TIMER_A_SETVAL;
    timerB.timeRemaining = TIMER_B_SETVAL;
    timerC.timeRemaining = TIMER_C_SETVAL;
    //this is the central variable behind changes to the LED lights on the board
    char LED_Pattern = 0x00;

    LEDS_INIT();    //from Leds_Lab06.c, initializes our LEDs

    /*
     *  Runs in an infinite loop:
     *      - checks each timer event flag. If any are true, resets the event flag, prints the respective
     *        letter corresponding to the timer, and adjusts the LED pattern to reflect on the board.
     *      - the LEDs require a continuous loop to state when they are on, otherwise they default to off
     */
    while (1) {
        //poll timer A
        if(timerA.event == 1)
        {
            timerA.event = 0;
            printf("A ");
            LED_Pattern ^= 0x01;      //toggles LED 1
        }
        if(timerB.event == 1)
        {
            timerB.event = 0;
            printf("B ");
            LED_Pattern ^= 0x02;      //toggles LED 2
        }
        if(timerC.event == 1)
        {
            timerC.event = 0;
            printf("C ");
            LED_Pattern ^= 0x04;      //toggles LED 3
        }
        //Testing the LEDS
        LEDS_SET(LED_Pattern);
            //react to timer A events
            //clear timer A event flag
    }
    
    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}

/**
 * This is the interrupt for the Timer1 peripheral. It will trigger at the frequency of the peripheral
 * clock, divided by the timer 1 prescaler and the interrupt interval.
 * 
 * It should not be called, and should communicate with main code only by using module-level variables.
 */
void __ISR(_TIMER_1_VECTOR, ipl4auto) Timer1Handler(void)
{
    // Clear the interrupt flag.
    IFS0bits.T1IF = 0;
    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    
    //decrement each timer
    timerA.timeRemaining--;
    timerB.timeRemaining--;
    timerC.timeRemaining--;
    
    //series of if statements set event flags and reset values for their respective timers
    if(timerA.timeRemaining == 0)
    {
        timerA.event = 1;
        timerA.timeRemaining = TIMER_A_SETVAL;
    }
    if(timerB.timeRemaining == 0)
    {
        timerB.event = 1;
        timerB.timeRemaining = TIMER_B_SETVAL;
    }
    if(timerC.timeRemaining == 0)
    {
        timerC.event = 1;
        timerC.timeRemaining = TIMER_C_SETVAL;
    }
    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}