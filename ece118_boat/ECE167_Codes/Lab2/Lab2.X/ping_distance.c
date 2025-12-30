/* 
 * File:   ping_distance.c
 * Author: quillanzhen
 *
 */

/*
 * Setup:
 * Pin 35 = Trigger
 * Pin 34 = Echo 
 * Pin 3 = Audio Amp
 */
//Default Libraries
#include <stdio.h>
#include <stdlib.h>

//User Libraries
#include "xc.h"
#include "Oled.h"
#include "PING.h"
#include "timers.h"
#include "ToneGeneration.h"
#include "AD.h"

/*
 * 
 */
#define DISTANCETOFREQ 25
#define BUFFERLEN 20
#define PINGTHRESHOLD 1

//for noise
int averageCounter;
int averageVal;
int buffer_distance[BUFFERLEN];
int i;
int sum;

int prev;
int freq;

int main(void) {
    BOARD_Init();
    OledInit();
    PING_Init();
    ToneGeneration_Init();

    averageCounter = 0;
    averageVal = 0;
//    prevSample = BUFFERLEN - 1;
    prev = 0;
    sum = 0;


    int distance = 0;
    char string [100];
    while (1) {
        distance = PING_GetDistance();

        //adds distance into buffer
        buffer_distance[averageCounter % BUFFERLEN] = distance;


        //finds average ADC reading
        sum = 0;
        for (i = 0; i < BUFFERLEN; i++) {
            sum += buffer_distance[i];
        }
        averageVal = sum / BUFFERLEN;
        //Filter
        if (abs(averageVal - prev) < PINGTHRESHOLD) {
            distance = prev;
        } else {
            prev = averageVal;
        }

        freq = DISTANCETOFREQ * averageVal;
        if (freq > 1000) {
            freq = 1000;
        } else if (freq < 0) {
            freq = 0;
        }

        ToneGeneration_SetFrequency(freq);
        sprintf(string, "Distance: %d\nFrequency: %d", distance, freq);
        OledDrawString(string);
        OledUpdate();
        OledClear(OLED_COLOR_BLACK);

        averageCounter++;
    }
}

