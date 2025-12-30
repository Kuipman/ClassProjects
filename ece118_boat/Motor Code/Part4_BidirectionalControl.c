/* 
 * File:   Part4_BidirectionalControl.c
 * Author: hkjia / nkuipers
 *
 * Created on May 2 2023, 12:05pm
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "IO_Ports.h"
#include <BOARD.h>
#include "AD.h"
#include "pwm.h"
#include "LED.h"

// Global Vars
unsigned char LED_Pat;
unsigned int POT_Val;

//Prototypes
void setPinA(int);
void setPinB(int);

/*
 * 
 */
int main(void) {
    BOARD_Init();
    AD_Init();
    LED_Init();
    PWM_Init();
    AD_AddPins(AD_PORTW5);
    // Set switch input pin, determines direction of motor
    //PORTZ03_TRIS;
    //PORTZ03_BIT;
    IO_PortsSetPortInputs(PORTZ, PIN5);    // Sets pin 3 on port z as an input (bit pattern starts at pin 3)
    //IO_PortsSetPortDirection(PORTZ, 0x1);
    // activate enable pin, set to ON
    IO_PortsSetPortOutputs(PORTZ, PIN4);   // Sets pin 4 on port z as an output (enable pin on H-bridge)
    IO_PortsWritePort(PORTZ, PIN4);
    // Set A, B output pins, H/L determined by switch pin
    PWM_AddPins(PWM_PORTY04);   // Sets pin 4 on port y as a pwm output  (Input A on h-bridge)
    PWM_AddPins(PWM_PORTY10);   // Sets pin 10 on port y as a pwm output (Input B on h-bridge)
    
    LED_AddBanks(LED_BANK1);
    //unsigned int direction = 0;    // 0 = CW, 1 = CCW
    while(1){
        // Read potentiometer, set value that determines motor speed
        POT_Val = AD_ReadADPin(AD_PORTW5);
        printf("Pot_Val %d \r\n", POT_Val);
        //PWM_SetDutyCycle(PWM_PORTY04, POT_Val);
        
        // Set LED bank values to reflect current motor speed
        LED_Pat = POT_Val/64;
        LED_SetBank(LED_BANK1, LED_Pat);
        //printf("LED_Pat %d \r\n", LED_Pat);
        
        // Determine direction of motor from port z, pin 3 (CW) and pin 4 (CCW)
        printf("Port Value: %i ", IO_PortsReadPort(PORTZ) & PIN5);
        if(IO_PortsReadPort(PORTZ) & PIN5)
        {
            printf("Direction = CCW\r\n");
            setPinA(0);
            setPinB(1);    // turn CCW
        }
        else
        {
            printf("Direction = CW\r\n");
            setPinA(1);    // turn CW
            setPinB(0);
        }
        
    }
    return (EXIT_SUCCESS);
}

//Implementations
void setPinA(int ON)
{
    if(ON)
        PWM_SetDutyCycle(PWM_PORTY04, POT_Val);
    else
        PWM_SetDutyCycle(PWM_PORTY04, 0);
        
}
void setPinB(int ON)
{
    if(ON)
        PWM_SetDutyCycle(PWM_PORTY10, POT_Val);
    else
        PWM_SetDutyCycle(PWM_PORTY10, 0);
}