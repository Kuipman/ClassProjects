/** LEDs.c
 *  @auth Nicholas Kuipers
 *  @purpose Definitions for the LEDs.h library
 */

#include "LEDs.h"
#include <stdint.h>
#include <xc.h>

/*  Initializes the 8 LEDs on the board and writes a '0' to each ("off")
 *  All 8 LEDs are on 'device E' on the board -- by writing a '0' to each TRIS register on device E this sets
 *      all eight LEDs to be outputs on the device
 *  Next, LATE essentially tracks the values of the 8 bits of the E device. By writing a 0 to each bit, this
 *      ensures each LED is initially turned off
 */
void LEDs_Init()
{
    TRISE = 0x00;     // Initialize LEDs to output
    LATE  = 0x00;     // Writes a '0' to all components on device E
}

//LATE tracks the values of the 8 bits of the E device -- reading from LATE gives the current values of the LEDs
uint8_t getLEDValues()
{
    return LATE;
}

//Writing a new set of values to LATE will change the current values of the 8 LEDs
void setLEDValues(uint8_t newLEDValues)
{
    LATE = newLEDValues;
}
