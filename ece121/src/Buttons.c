/** buttons.c
 *  @auth Nicholas Kuipers
 *  @purpose Definitions for the Buttons.h library
 */

//Associated, student-created library
#include "Buttons.h"

//C or board-specific libraries (needed for MPLAB to compile properly)
#include <xc.h>
#include <stdint.h>

/* 3 buttons reside on the D device, while 1 button resides on the F device. Therefore
 *    two calls to TRIS are called for each device. The buttons will be inputs, so
 *    a '1' needs to be written to the respective bits
 */ 
void Buttons_Init()
{
    TRISD |= 0xE0;    //sets respective buttons to inputs   0b11100000
    TRISF |= 0x02;   //sets remaining button to input       0b00000010
}

/*  Reads the respective values of the four buttons and returns them as an 8-bit value
 *  @todo Bitshift these values so the button values are returned in the lower 4 bits of rValue
 */
uint8_t getButtonValues()
{
    uint8_t rValue = 0;
    rValue |= (PORTD & 0b11100000);  //0b11100000 --> 0b00001110   >>4
    rValue |= (PORTF & 0b00000010);  //0b00000010 --> 0b00000001   >>1
    return rValue;
}

/*  Checks if any button is pressed -- unspecific as to which button
 */
uint8_t checkAnyButtonPress()
{
    if(getButtonValues())
        return 0xFF;
    return 0x00;
}
