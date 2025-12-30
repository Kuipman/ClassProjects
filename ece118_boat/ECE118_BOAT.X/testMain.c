/*
 * File:   testMain.c
 * Author: Nicholas Kuipers
 *
 * Created on May 13, 2023, 3:44 PM
 * 
 * @note NOT intended for inclusion in final project -- proof of concept file
 */

#include "BOARD.h"
#include "AD.h"
#include "IO_Ports.h"
#include "LED.h"
#include "pwm.h"
#include "RC_Servo.h"
#include "serial.h"
#include "timers.h"
#include "xc.h"
#include <stdio.h>

int main(void) {
    BOARD_Init();
    SERIAL_Init();
    
    // Tests single input low and high -- verified 5/17
    _TRISB3 = 0;
    LATBbits.LATB3 = 0;     // V4
    _TRISB2 = 0;
    LATBbits.LATB2 = 1;     // V3
    
    // Tests PWM signal on standard oscillator pin
    PWM_Init();
    PWM_SetFrequency(1000);
    PWM_AddPins(PWM_PORTX11);
    PWM_SetDutyCycle(PWM_PORTX11, 100);
    
    
    while(1)
    {
        printf("Hello World!\n");
    }
    return 0;
}
