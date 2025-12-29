// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
					
//CMPE13 Support Library
#include "BOARD.h"

//Personal Libraries
#include "Leds_Lab06.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// **** Declare any datatypes here ****

#define TIMER_DEFAULT_MAX 1
#define LEFT 0
#define RIGHT 1

typedef struct {
    uint8_t event;
    int16_t timeRemaining;
} Timer;

// **** Define global, module-level, or external variables here ****
Timer timerA;	
uint8_t state = LEFT;    //initial state sends LED bounce in left direction
unsigned char LED_Pattern = 0x01; //rightmost LED begins in the on position, needs to be unsigned for 0x80

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
    printf("Welcome to NKuipers' lab6 part2 (bounce_switch).  Compiled on %s %s.\n",__TIME__,__DATE__);
    timerA.timeRemaining = TIMER_DEFAULT_MAX;
    //this is the central variable behind changes to the LED lights on the board

    LEDS_INIT();    //from Leds_Lab06.c, initializes our LEDs
							 
	/*
     *  Runs in an infinite loop:
     *      - checks the timerA event flag. If true, sets to false then performs an appropriate bitwise shift of 
     *          LED_Pattern (thus changing the currently lit LED on the board)
     */
    while (1) {
        if(timerA.event == 1)
        {
            timerA.event = 0;
            if(LED_Pattern >= 0x80)
            {
                state = RIGHT;
            }
            else if(LED_Pattern <= 0x1)
                state = LEFT;
            
            if(state == RIGHT)
                LED_Pattern >>= 1;
            else
                LED_Pattern <<= 1;
        }
        LEDS_SET(LED_Pattern);
    }		
    
    BOARD_End();
    while(1);


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
    timerA.timeRemaining--;
    int additionalTime = 0;
    /*
     *  Below for loop checks each switch position from right to left. If the switch is on, this adds additional time to
     *  the timer at the end of the ISR. This uses a bitwise shift to cycle through each switch and check if each are on.
     */
    char temp = SWITCH_STATES();
    for(int i = 0; i < 4; i++)
    {
        if((temp % 2) == 1)
            additionalTime += 2;
        temp >>= 1;
    }
    //The timer was decremented at the beginning of this function. If it is 0, the event flag is set to true and the timer is reset
    if(timerA.timeRemaining == 0)
    {
        timerA.event = 1;
        timerA.timeRemaining = additionalTime + TIMER_DEFAULT_MAX;
    }
    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/									
	 
}


/*SPARE CODE
 * if(timerA.event == 1)
        {
            timerA.event = 0;
            if(LED_Pattern >= 0x80)    //this breaks when set to 0x80
                state = RIGHT;
            else if(LED_Pattern <= 0x1)
                state = LEFT;
            
            if(state == RIGHT)
                LED_Pattern >>= 1;
            else
                LED_Pattern <<= 1;
        }
 * 
 * 
 * 
 * 
 * 
 */