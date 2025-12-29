/**
 * File: PingService.c
 * Group: Nick Kuipers
 * 
 * @brief Implementation for Ping Service function, designed to integrate in the
 *      broader ES_Framework built for ECE 118.
 */

#include "BOARD.h"
#include "AD.h"
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "Midterm_Part5_PingService.h"
#include <stdio.h>
#include <serial.h>

/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                    *
 ******************************************************************************/

static uint8_t MyPriority;         // priority of 0 - 8
static uint8_t FRT_Start, FRT_Stop, triggerFlag;

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @brief Initializes the ping service function, called automatically by the ES_Framework
 *      at the beginning of code execution
 * @param Priority - internal variable tracking which event queue is used
 * @return True for success, False otherwise
 */
uint8_t InitPingService(uint8_t Priority)
{
    ES_Event ThisEvent;

    MyPriority = Priority;

    // in here you write your initialization code
    // this includes all hardware and software initialization
    // that needs to occur.
    
    TRISB |= 0x30;     // Activates RB5/Pin 11 and RB4/Pin12
    
    FRT_Start = 0;
    FRT_Stop = 0;
    triggerFlag = 0;

    // post the initial transition event
    ThisEvent.EventType = ES_INIT;
    ES_Timer_InitTimer(0, 100);           // initializes timer 0, triggers service after 100ms
    
    if (ES_PostToService(MyPriority, ThisEvent) == TRUE) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * @brief Wrapper function allowing for post of an event to the respective
 *      queue for the Ping Service Function.
 * @param ThisEvent - the event (a struct with "type" and "param" variables) to
 *      be posted to queue
 * @return TRUE if successful, FALSE otherwise
 */
uint8_t PostPingService(ES_Event ThisEvent)
{
    return ES_PostToService(MyPriority, ThisEvent);
}

/**
 * @brief Holds the actual Ping Service Function, called any time a new event
 *      is passed to the respective event queue.
 *      Service operates as follows:
 *          - Service can be called upon expiry of Timer0 (two instances), or upon 
 *              an EW_Event (specifically when it moves from high to low)
 *          - a static triggerFlag keeps track of the two separate instances when Timer0 calls service
 *          - If the service is called by timer0
 *              - If triggerFlag is 0, flag is set to 1 as the trigger pin is set high
 *                  and Timer0 is set for 1ms
 *              - If the triggerFlag is 1, flag is set back to 0. FRT time (START) is recorded
 *          - If the service is called by EW_Event
 *              - Records the FRT Time (STOP) and calculates the resulting distance
 *              - Prints distance as a terminal output
 * @param ThisEvent - the event (type and param) to be responded to
 * @return event - return event (type and param), that in general should be ES_NO_EVENT
 */

ES_Event RunPingService(ES_Event ThisEvent)
{
    ES_Event ReturnEvent;
    ReturnEvent.EventType = ES_NO_EVENT; // assume no errors
    
    switch(ThisEvent.EventType)
    {
        case ES_INIT:
        {
            return ReturnEvent;
        }
        case ES_TIMEOUT:
        {
            if(triggerFlag == 0)
            {
                triggerFlag = 1;
                LATB |= 0x20;     // asserts Trigger Pin = RB5
                ES_Timer_InitTimer(0, 1);       // sets Timer0 to run for 1ms
            }
            else
            {
                triggerFlag = 0;
                LATB ^= 0x20;    // Toggles Trigger Pin back to 0
            }
        }
    }
    return ReturnEvent;
}


/*******************************************************************************
 * PART3                                                            *
 ******************************************************************************/

/**
 * @brief Takes in an ADC input and returns an accumulated angle output to
 *      some arbitrary service
 *      - Timer runs every 10ms (set by end of this service) that calls this service
 *          upon expiry
 *      - AD pin connected to output of circuit is read, receiving 10-bit value (0-1023)
 *      - Converts value to millivolt equivalent for further calculations, if needed
 *      - If value lies within range of Vref (1.65V), resets timer and ends here
 *      - If value lies outside of range, check which side of Vref voltage lies
 *          and calculate how far away from Vref the ADC voltage is
 *      - Divide this value into 2 (and compensate for noise) to find degrees
 *      - Divide by another 100: value is checked and updated every 10ms, while degree values
 *          represent degree change per second
 *      - Sets a flag if a degree change is detected. This allows the function to directly change
 *          the accumulatedAngle static variable accordingly and send it as event parameter to some
 *          arbitrary service
 *      - Finally, resets the timer and returns the event
 * 
 * @param ThisEvent - the event (type and param) to be responded to
 * @return event - return event (type and param), that in general should be ES_NO_EVENT
 */

#define ADC_TO_MV       3.236

ES_Event RunADC_AngleService(ES_Event ThisEvent)
{
    ES_Event ReturnEvent;
    ReturnEvent.EventType = ES_NO_EVENT; // assume no errors
    uint8_t degreeChangeFlag = 0;
    int degreeChange_Pos = 0;
    int degreeChange_Neg = 0;
    static uint16_t accumulatedAngle = 0;
    
    switch(ThisEvent.EventType)
    {
        case ES_INIT:
        {
            break;
        }
        case ES_TIMEOUT:     // Triggers every 10 ms (arbitrary but we want decent update speed)
        {
            int ADC = AD_ReadADPin(AD_PORTV4);   // pin used connected to output of circuit. Receives 10-bit value
            double ADC_mV = ADC * ADC_TO_MV;   // converts to a millivolt value
            
            if(ADC >= 509.5 && ADC <= 513.5)       // voltage is at Vref
            {
                ES_Timer_InitTimer(0, 10);     // begin timer that wraps around to this function upon expiry
                return ReturnEvent;
            }
            
            if(ADC > 513.5)        // positive degree change
            {
                double ADC_Change = ADC_mV - (511.5 * ADC_TO_MV);  // difference in millivolts
                degreeChange_Pos = ADC_Change / 2;                 // degree change every 2 millivolts
                if(ADC_Change % 2 >= 1)                            // conditional for noise -- if above 50%, count as degree
                    degreeChange_Pos++;  
                degreeChange_Pos = degreeChange_Pos / 100;         // offset for checking every 10ms
                degreeChangeFlag = 1;                 // adjust accumulated angle
                break;
            }
            else                   // negative degree change
            {
                double ADC_Change = (511.5 * ADC_TO_MV) - ADC_mV;  // difference in millivolts
                degreeChange_Neg = ADC_Change / 2;
                if(ADC_Change % 2 >= 1)
                    degreeChange_Neg++;
                degreeChange_Neg = degreeChange_Neg / 100;      // offset for checking every 10ms
                degreeChangeFlag = 1;
                break;
            }
            break;
        }
    }
    if(degreeChangeFlag)
    {
        degreeChangeFlag = 0;     // reset the flag for next time
        if(degreeChange_Pos)
        {
            accumulatedAngle += degreeChange_Pos;
        }
        else if(degreeChange_Neg)
        {
            accumulatedAngle -= degreeChange_Neg;
        }
        else
            break;
        
        // Notional service angle will be returned to
        ReturnEvent.EventType = ANGLE_UPDATE;
        ReturnEvent.EventParam = accumulatedAngle;
        PostARBITRARYService(ReturnEvent);
    }
    ES_Timer_InitTimer(0, 10);     // begin timer that wraps around to this function upon expiry
    return ReturnEvent;
}