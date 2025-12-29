/**
 * File: Midterm_Part5.c
 * Authors: Nick Kuipers
 * 
 * @brief Library of functions that correspond to the ping sensor
 *      in part 5 of the ECE118 midterm
 */



#include <stdio.h>
#include "Midterm_Part5.h"
#include "EventChecker.h"
#include "ES_Configure.h"
#include "ES_Events.h"
#include "serial.h"
#include "AD.h"
#include "roach.h"

/***************************************************************/\
/***                    Helper Functions Prototypes          ***/
/***************************************************************/

uint8_t readEWPin();

/***************************************************************/\
/***                    Function Declarations                ***/
/***************************************************************/

// As name implies, activates the sensor pins with EW input pin and trigger output pin
void PingSensor_Init()
{
    TRISB |= 0x30;     // Activates RB5/Pin 11 and RB4/Pin12
    //LATB  &= 0x30;    // Sets RB5/Pin11 as an output, leaving the rest of the pins alone
    // RB4/Pin12 is an input, and left alone here
}

/**
 * @brief This function uses blocking code to ping the sensor (using RB5/pin11 as
 *      the trigger pin) for 1ms (fastest we can go). Once the ping is finished we 
 *      record the current FRT value and listen on the EW output pin (RB4/pin12)
 *      until its value drops to 0. The time difference recorded here is calculated by
 *      (EW*1000)/148 and returned as a distance value
 * @param Nothing
 * @return uint8_t, distance value in inches
 */
uint8_t getPingSensorMeasurement_V1()
{
    int FRT_Start = 0, FRT_Stop = 0, FRT_Change = 0, theResult = 0;
    
    // It is assumed the ping sensor pins are initialized by the init function above,
    //  whether in the main function or some other function
    
    // First, assert the trigger pin high. Then immediately read the FRT
    LATB |= 0x20;     // Trigger Pin = RB5
    FRT_Start = ES_Timer_GetTime();
    
    // We need to give the sensor enough time to register the trigger and send its pulse
    //  before it asserts its EW pin. So, we read the timer until 1ms has passed
    while(~FRT_Change)
    {
        FRT_Change = ES_Timer_GetTime() - FRT_Start;
    }
    LATB ^= 0x20;    // Toggles Trigger Pin back to 0
    
    // Now, the sensor should be asserting its EW pin high. We will read it
    //  until it drops back to low
    FRT_Start = ES_Timer_GetTime();    // Start of ECHO output (from what we can see)
    while(readEWPin()) {}              // Blocking code until pin is deasserted
    FRT_Stop = ES_Timer_GetTime();     // Records end of ECHO output
    
    // Finally, we calculate the distance using the measurement (EW*1000)/148
    // ( the 1000 is needed because our number is in a factor of 1ms versus the 1us required)
    theResult = FRT_Stop - FRT_Start;   // EW
    theResult = (theResult*1000)/148;
    
    return (uint8_t)theResult;
}

uint8_t getPingSensorMeasurement_V2()
{
    
}

// Returns a high value if Pin is asserted high and 0 otherwise
uint8_t readEWPin()
{
    if(PORTB & 0x800)    // will be asserted high if there is a high voltage on the EW pin
        return 0xFF;
    else
        return 0;
}

