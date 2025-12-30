/* 
 * File:   Part6_StepperBoard.c
 * Author: hkjia / nkuipers
 *
 * Created on May 2 2023, 12:05pm
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "IO_Ports.h"
#include <BOARD.h>
#include <Stepper.h>
#include "AD.h"
#include "pwm.h"
#include "LED.h"


int main(void) {
    BOARD_Init();
    AD_Init();
    LED_Init();
    PWM_Init();
    Stepper_Init();
    // Enable Pin
    IO_PortsSetPortOutputs(PORTZ, PIN5);    // Sets pin 3 on port z as an input (bit pattern starts at pin 3)
    // Step pin
    IO_PortsSetPortOutputs(PORTZ, PIN3);   // Sets pin 4 on port y as a pwm output  (Input A on h-bridge)
    // Direction Pin
    IO_PortsSetPortOutputs(PORTZ, PIN4);
    IO_PortsWritePort(PORTZ, PIN4 + PIN5);
    
    int toggle = 0;
    while(1){
        for(int i = 0; i < 1000; i++);
        if(IO_PortsReadPort(PORTZ) & PIN3)
        {
            IO_PortsWritePort(PORTZ, PIN5 + PIN4);
        }
        else
        {
            IO_PortsWritePort(PORTZ, PIN5 + PIN3 + PIN4);
        }
        
        
    }
    return 0;
}