#include <stdint.h>

//ECE 13 - Support Library
#include "BOARD.h"
#include <xc.h>
#include "Buttons.h"


//Global Variables
uint8_t buttons_priorVal = 0x0;
uint8_t debounceCounter = 0;
/*
 *  Initializes the pins on the board so that the four buttons can be used
 */
void ButtonsInit(void)
{
    TRISD |= 0x00E0;
    TRISF |= 0x0002;
}

/*
 *  
 */
uint8_t ButtonsCheckEvents(void)
{   
    uint8_t buttons = BUTTON_STATES();
    uint8_t returnStatement = 0;
    if(buttons == buttons_priorVal)
        return BUTTON_EVENT_NONE;
    
    /*
     *  Current implementation of debounce counter makes the program run way too slow. Commented out for now.
     * 
    debounceCounter++;
    if(debounceCounter < BUTTONS_DEBOUNCE_PERIOD)
        return BUTTON_EVENT_NONE;
    debounceCounter = 0;
     * */
    
    //set bit difference between present and prior values for the buttons to a separate variable 'difference'
    uint8_t difference = buttons ^ buttons_priorVal;
    
    //run through series of statements pertaining to each button value
    if(difference & 0b0001)
    {
        if(buttons_priorVal && 0b0001)
            returnStatement |= BUTTON_EVENT_1UP;     //indicate the button was released
        else
            returnStatement |= BUTTON_EVENT_1DOWN;   //indicate the button was pressed
    }
    if(difference & 0b0010)
    {
        if(buttons_priorVal && 0b0010)
            returnStatement |= BUTTON_EVENT_2UP;
        else
            returnStatement |= BUTTON_EVENT_2DOWN;
    }
    if(difference & 0b0100)
    {
        if(buttons_priorVal && 0b0100)
            returnStatement |= BUTTON_EVENT_3UP;
        else
            returnStatement |= BUTTON_EVENT_3DOWN;
    }
    if(difference & 0b1000)
    {
        if(buttons_priorVal && 0b1000)
            returnStatement |= BUTTON_EVENT_4UP;
        else
            returnStatement |= BUTTON_EVENT_4DOWN;
    }
    buttons_priorVal = buttons;
    return returnStatement;
}

