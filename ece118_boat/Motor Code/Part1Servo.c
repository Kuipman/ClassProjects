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
#include "pwm.h"
#include "LED.h"


/*
 * 
 */
int main(void) {
    BOARD_Init();
    AD_Init();
    LED_Init();
    RC_Init();
    AD_AddPins(AD_PORTW5);
    RC_AddPins(RC_PORTV04);
    LED_AddBanks(LED_BANK1);
    unsigned char LED_Pat;
    unsigned int POT_Val;
    unsigned short int PulseWidth;
    while(1){
        POT_Val = AD_ReadADPin(AD_PORTW5);
        printf("Pot_Val %d \r\n", POT_Val);
        
        PulseWidth = POT_Val + 1000;
        RC_SetPulseTime(RC_PORTV04, PulseWidth);
        printf("Pulsewidth %d \r\n", PulseWidth);
        
        LED_Pat = POT_Val/64;
        LED_SetBank(LED_BANK1, LED_Pat);
        printf("LED_Pat %d \r\n", LED_Pat);
        
    }
    return (EXIT_SUCCESS);
}

