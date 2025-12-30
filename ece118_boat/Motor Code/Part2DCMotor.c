/* 
 * File:   Part2DCMotor.c
 * Author: hkjia
 *
 * Created on May 1, 2023, 3:38 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "IO_Ports.h"
#include <BOARD.h>
#include "AD.h"
#include "pwm.h"
#include "LED.h"


/*
 * 
 */
int main(void) {
    BOARD_Init();
    AD_Init();
    LED_Init();
    PWM_Init();
    AD_AddPins(AD_PORTW5);
    PWM_AddPins(PWM_PORTY04);
    LED_AddBanks(LED_BANK1);
    unsigned char LED_Pat;
    unsigned int POT_Val;
    while(1){
        POT_Val = AD_ReadADPin(AD_PORTW5);
        printf("Pot_Val %d \r\n", POT_Val);
        
        PWM_SetDutyCycle(PWM_PORTY04, POT_Val);
        
        LED_Pat = POT_Val/64;
        LED_SetBank(LED_BANK1, LED_Pat);
        printf("LED_Pat %d \r\n", LED_Pat);
        
    }
    return (EXIT_SUCCESS);
}
