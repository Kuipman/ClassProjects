/* 
 * File:   Instrument.c
 * Author: quillanzhen
 *
 * Created on April 8, 2022, 2:10 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "AD.h"
#include "BOARD.h"
#include "Oled.h"
#include "ToneGeneration.h"
#include <math.h>

int main(void) {
    int val;
    double voltage;
    int freq;
    int preVal;
    int freqDiff;
    char string[30];

    BOARD_Init();
    AD_Init();
    OledInit();
    ToneGeneration_Init();

    printf("Begin making music: ");

    AD_AddPins(AD_A0);
    ToneGeneration_ToneOn();

    while (1) {
        if (BTN1) {
            freq = freq + TONE_196;
        }
        if (BTN2) {
            freq = freq + TONE_293;
        }
        if (BTN3) {
            freq = freq + TONE_440;
        }
        if (BTN4) {
            freq = freq + TONE_659;
        } //turn off
        if (freq == 0) {
            ToneGeneration_ToneOff();
            continue;
        }

        //filtering
        val = AD_ReadADPin(AD_A0);

        if (abs(preVal - val) < 20) {
            val = preVal;
        } else {
            preVal = val;
        }

        //voltage reading
        voltage = (val * 3.3) / 1023;

        //Setting Frequency values
        freqDiff = (((double)val * 194)/1023) - 97;
        ToneGeneration_ToneOn();
        ToneGeneration_SetFrequency(freq + freqDiff);

        sprintf(string, "Voltage: %fV\nFrequency: %dHz\nChange: %dHz", voltage, freq, freqDiff);

        //Printing string onto OLED
        OledDrawString(string);
        OledUpdate();
        OledClear(OLED_COLOR_BLACK);
        
        //reset frequency
        freq = 0;
    }
}






