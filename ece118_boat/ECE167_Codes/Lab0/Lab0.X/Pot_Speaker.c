/* 
 * File:   Pot_Speaker.c
 * Author: quillanzhen
 *
 * Created on April 8, 2022, 1:55 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "AD.h"
#include "BOARD.h"
#include "Oled.h"
#include "ToneGeneration.h"
#include <math.h>

int val;
double voltage;
int freq;
char string[30];
int preVal;

int main(void){
    BOARD_Init();
    AD_Init();
    OledInit();
    ToneGeneration_Init();
    
    printf("Begin Tone Adjusting via Potentiometer: ");
    
    AD_AddPins(AD_A0);
    ToneGeneration_ToneOn();
    
    while(1){
        
        //filter
        val = AD_ReadADPin(AD_A0);
        
        if (abs(preVal - val) < 20){
            val = preVal;
        }
        else{
            preVal = val;
        }
          voltage = (val*3.3)/1023;
    //frequency range from 20-1000
    freq = pow(1.5,(((double)val*10)/1023)+7);
    ToneGeneration_SetFrequency(freq);
    
    //Oled
    sprintf(string, "Voltage: %fV \nFrequency: %d", voltage, freq);
    OledDrawString(string);
    OledUpdate();
    OledClear(OLED_COLOR_BLACK);  
    
    }        
}




