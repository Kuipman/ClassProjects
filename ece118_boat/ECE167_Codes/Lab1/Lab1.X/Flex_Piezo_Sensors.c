/* 
 * File:   Flex_Piezo_Sensors.c
 * Author: quillanzhen
 *
 */

//default libraries
#include <stdio.h>
#include <stdlib.h>

//user libraries
#include "Board.h"
#include "ToneGeneration.h"
#include "Oled.h"
#include "AD.h"
#include "math.h"

/*
 * 
 */
#define BUFFERLENGTH 16 // # of sampled values to average
#define NOISETHRESHOLD 10 // Diff btw recent and prev values to considered an event
#define PIEZOTHRESHOLD 150 // Lower bound for ADC to be considered an event
#define MUSIC_PLAYTIME 150 // How long music is played after the piezo is activated


int buffer[BUFFERLENGTH] = {0};
int averageCounter, averageV, sum, i, preV; // To find the average and filter noise
int soundTimer;
int flexADC, angle; //flex values
char string[30];

int main(void) {
    //Initializing BOARD, AD, Oled, and ToneGeneration
    //and adding appropriate pins
    BOARD_Init();
    AD_Init();
    OledInit();
    ToneGeneration_Init();

    AD_AddPins(AD_A1 | AD_A2);

    //Initialize counter and holders
    averageCounter = 0;
    preV = 0;
    soundTimer = 0;

    while (1) {
        //Read ADC voltage from the flex sensor
        flexADC = AD_ReadADPin(AD_A1);

        //adds flexADC into buffer
        buffer[averageCounter % BUFFERLENGTH] = flexADC;


        //finds average ADC reading
        sum = 0;
        for (i = 0; i < BUFFERLENGTH; i++) {
            sum += buffer[i];
        }
        averageV = sum / BUFFERLENGTH;

        //Filter noise using the avg adc, as well as rapid changes of tones
        if (abs(averageV - preV) < NOISETHRESHOLD) {
            flexADC = preV;
        } else {
            preV = averageV;
        }

        //Converts ADC reading from flex sensor into degrees
        angle = (.0003 * (flexADC * flexADC)) - 0.0559 * (flexADC) - 17.09;



        //Converts angle into freq., accounts for negative freq.
        int freq = (480 / 90) * angle;
        if (freq < 0) {
            freq = 0;
        }

        //If Piezo gets tapped above 600mV, then it plays music
        int piezoADC = AD_ReadADPin(AD_A2); //Appro spike for 600mV
        if (piezoADC > PIEZOTHRESHOLD) {
            ToneGeneration_ToneOn();
            ToneGeneration_SetFrequency(freq);
            soundTimer = 0; //resets timer    
        } else if (soundTimer > MUSIC_PLAYTIME) {
            ToneGeneration_ToneOff();
        }

        //Create and to print string on Oled
        sprintf(string, "ADC: %d \nDegrees: %d\nFrequency: %dHz", flexADC, angle, freq);
        OledDrawString(string);
        OledUpdate();
        OledClear(OLED_COLOR_BLACK);

        //increment timers
        soundTimer++;
        averageCounter++;
    }
}

