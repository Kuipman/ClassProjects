/* 
 * File:   ADReader.c
 * Author: quillanzhen
 *
 * Created on April 8, 2022, 12:41 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "BOARD.h"
#include "SERIAL.h"
#include "AD.h"
#include "Oled.h"

int reading;
double voltage;
char string[30];
int i;

int main(void) {
    BOARD_Init();
    AD_Init();
    OledInit();
    printf("Begin AD Reader: ");
            
    AD_AddPins(AD_A0);
    
    while(1){
        //Reads potentiometer value and converts that value into voltage
        reading = AD_ReadADPin(AD_A0);
        voltage = (reading*3.3)/1023;
        
        //Creates string from int for the Oled
        sprintf(string, "Voltage: %f ", voltage);
        
        //Printing string onto OLED
        OledDrawString(string);
        OledUpdate();
        OledClear(OLED_COLOR_BLACK);
    }
}

