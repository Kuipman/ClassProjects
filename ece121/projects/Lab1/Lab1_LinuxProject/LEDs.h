/** LEDs.h
 *  @auth Nicholas Kuipers
 *  @purpose Library to interact with the 8 LEDs on the I/O shield (daughter board)
 *      of the uC32
 */

//C or board-specific libraries
#include <stdint.h>
//#include <xc.h>

#ifndef LEDS_H
#define	LEDS_H

//Initializes the 8 LEDs on the I/O shield of the uC32
void LEDs_Init();

//Returns a uint8_t value that reflects the current values of the LEDs
uint8_t getLEDValues();

//LED setters
void setLEDValues(uint8_t);

#endif	/* LEDS_H */

