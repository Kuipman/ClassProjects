/** buttons.h
 *  @auth Nicholas Kuipers
 *  @purpose Library to interact with the 4 buttons on the I/O shield (daughter board)
 *      of the uC32
 */

//C or board-specific libraries
#include <stdint.h>
#include <xc.h>

#ifndef BUTTONS_H
#define	BUTTONS_H

//Initialize the four buttons on the I/O shield of the uC32
void Buttons_Init();

//Returns the current values of the 4 buttons in the lower 4 bits of a uint8_t output value
uint8_t getButtonValues();

//if any button is pressed, returns 0xFF, else returns 0
uint8_t checkAnyButtonPress();


#endif	/* BUTTONS_H */

