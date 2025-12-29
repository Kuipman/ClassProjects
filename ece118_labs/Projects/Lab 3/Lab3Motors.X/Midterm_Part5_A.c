/* 
 * File:   Part1Servo.c
 * Author: hkjia
 *
 * Created on May 1, 2023, 11:00 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "IO_Ports.h"
#include <BOARD.h>
#include "AD.h"
#include "RC_Servo.h"
#include "serial.h"
#include "pwm.h"
#include "LED.h"


/*
 * 
 */
int main(void) {
    //AD_Init();
    //SERIAL_Init();
    BOARD_Init();
    /*
    PWM_Init();
    LED_Init();
    AD_AddPins(AD_PORTW3);
    RC_AddPins(RC_PORTV04);
    LED_AddBanks(LED_BANK1);
    unsigned int POT_Val;
    printf("testing0 \r\n");
     * */
    while(1){
        printf("testing1 \r\n");
    }
    
    BOARD_End();
    return (EXIT_SUCCESS);
}

