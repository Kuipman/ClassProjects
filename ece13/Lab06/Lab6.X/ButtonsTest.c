// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// User libraries
#include "Leds_Lab06.h"
#include "Buttons.h"

// User libraries

// **** Set macros and preprocessor directives ****

// **** Declare any datatypes here ****

// **** Define global, module-level, or external variables here ****

uint8_t buttonValues = 0;
uint8_t prevValue = 0;
uint8_t tempValues = 0;
uint8_t buttonEvent = FALSE;

// **** Declare function prototypes ****

int main(void)
{
    BOARD_Init();

    // Configure Timer 1 using PBCLK as input. This default period will make the LEDs blink at a
    // pretty reasonable rate to start.
    T1CON = 0; // everything should be off
    T1CONbits.TCKPS = 2; // 1:64 prescaler
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
    printf("Welcome to NKuipers' lab6 part4 (ButtonsTest).  Compiled on %s %s.\n", __TIME__, __DATE__);
    ButtonsInit();
    LEDS_INIT();
    char LED_Pattern = 0x00;

    printf("Please press some buttons!\n");
    
    while(1)
    {
        if(buttonEvent == TRUE)
        {
            //The next two lines are the functional portion of the event. The rest refers to a test seen in CoolTerm
            buttonEvent = FALSE;
            LED_Pattern = buttonValues;
            //The following is a series of outputs for testing purposes. When a button is pressed or released, an
            //output string is sent to the console (CoolTerm)
            
            //First, we print our switches:
            printf("\nActive Switches: ");
            if(SW1 == 1)
                printf("SW1 | ");
            if(SW2 == 1)
                printf("SW2 | ");
            if(SW3 == 1)
                printf("SW3 | ");
            if(SW4 == 1)
                printf("SW4");
            printf("\n");
            
            //Now, we print our button event values
            if(tempValues & BUTTON_EVENT_1DOWN)   
                    printf(" BUTTON_EVENT_1DOWN |");
            else if(tempValues & BUTTON_EVENT_1UP) 
                printf(" BUTTON_EVENT_1UP |");
            if(tempValues & BUTTON_EVENT_2DOWN) 
                printf(" BUTTON_EVENT_2DOWN |");
            else if(tempValues & BUTTON_EVENT_2UP)  
                printf(" BUTTON_EVENT_2UP |");
            if(tempValues & BUTTON_EVENT_3DOWN)
                printf(" BUTTON_EVENT_3DOWN |");    
            else if(tempValues & BUTTON_EVENT_3UP)
                printf(" BUTTON_EVENT_3UP |");
            if(tempValues & BUTTON_EVENT_4DOWN) 
                printf(" BUTTON_EVENT_4DOWN |");
            else if(tempValues & BUTTON_EVENT_4UP)
                printf(" BUTTON_EVENT_4UP |");
            
            //Finally we print our active LEDs by checking each bit value of the LED pattern (1 = ON, 0 = OFF)
            printf("\nLED Pattern: ");
            for(int i = 0x80; i >= 0x01; i>>=1)
            {
                if(LED_Pattern & i)
                    printf("1");
                else
                    printf("0");
            }
            printf("\n=================\n");
        }
        LEDS_SET(LED_Pattern);
    }

    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/
    
    BOARD_End();
    while (1);
}

/**
 * This is the interrupt for the Timer1 peripheral. It should check for button events and stores them in a
 * module-level variable.
 * 
 * You should not modify this function for ButtonsTest.c or bounce_buttons.c!
 */
void __ISR(_TIMER_1_VECTOR, ipl4auto) Timer1Handler(void)
{
    // Clear the interrupt flag.
    IFS0bits.T1IF = 0;

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    
    tempValues = ButtonsCheckEvents();       //value from ButtonsCheckEvents() that gets checked while buttonValues is changed
    if(tempValues != prevValue)
    {
        buttonEvent = TRUE;
        
        //run through series of statements for each set of 2 LEDs, toggling LEDs on/off depending on event from ButtonCheckEvents()
        //1st LEDs : 0x03  or 0b00000011
        if(tempValues & BUTTON_EVENT_1DOWN)     //button was pressed
        {
            if(SW1 == 0)
                buttonValues ^= 0b00000011;
        }
        else if(tempValues & BUTTON_EVENT_1UP)  //button was released
        {
            if(SW1 == 1)
                buttonValues ^= 0b00000011;
        }
        
        //2nd LEDs
        if(tempValues & BUTTON_EVENT_2DOWN)     //button was pressed
        {
            if(SW2 == 0)
                buttonValues ^= 0b00001100;
        }
        else if(tempValues & BUTTON_EVENT_2UP)  //button was released
        {
            if(SW2 == 1)
                buttonValues ^= 0b00001100;
        }
        
        //3rd LEDs
        if(tempValues & BUTTON_EVENT_3DOWN)     //button was pressed
        {
            if(SW3 == 0)
                buttonValues ^= 0b00110000;
        }
        else if(tempValues & BUTTON_EVENT_3UP)  //button was released
        {
            if(SW3 == 1)
                buttonValues ^= 0b00110000;
        }
        
        //4th LEDs
        if(tempValues & BUTTON_EVENT_4DOWN)     //button was pressed
        {
            if(SW4 == 0)
                buttonValues ^= 0b11000000;
        }
        else if(tempValues & BUTTON_EVENT_4UP)  //button was released
        {
            if(SW4 == 1)
                buttonValues ^= 0b11000000;
        }
        
        prevValue = tempValues;
    }

    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}


/*
        buttons = BUTTON_STATES();
        if(buttons && BUTTON_STATE_2)
        {
            temp = 2;
        }
        //END DEBUG
        sprintf(value, "Current Reading:\n%i", buttons);
        if(buttonEvent == TRUE)
        {
            buttonEvent = FALSE;
            OledClear(OLED_COLOR_BLACK);
        }
        else
        {
            OledDrawString(value);
        }
        OledUpdate();
 * 
 * 
 * buttonValues = BUTTON_STATES();
    if(buttonValues != prevValue)
    {
        buttonEvent = TRUE;
    }
        */