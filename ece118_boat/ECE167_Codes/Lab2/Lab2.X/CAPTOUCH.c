/* 
 * File:   CAPTOUCH.c
 * Author: quillanzhen
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "xc.h"
#include "CAPTOUCH.h"

#define BUFFERLENGTH 30
#define CAPTHRESHOLD 800
#define SECPTICK 0.0000002

enum SquareWave {
    one,
    two
} STATE;

int freq;
int averageVal;
int averageCounter;
int buffer[BUFFERLENGTH] = {0};
int periodT;
int startTime;
int endTime;

//Helper functions
int returnFreq(void) {
    return averageVal;
}

//helps average the signal to increase it to noise
int changingAvgVal(int val, int bufferlength, int *buffarray, int *averageCount, int *average){
    buffarray[(*averageCount)%bufferlength] = val/bufferlength;
    *average = *average + (val/bufferlength) - buffarray[((*averageCount)+1)%bufferlength];
    *averageCount += 1;
} 

char CAPTOUCH_Init(void) {
    // following block inits the timer
    T2CON = 0;
    T2CONbits.TCKPS = 0b011;
    PR2 = 0xFFFF;
    T2CONbits.ON = 1;

    //this block inits input capture
    IC4CON = 0;
    IC4CONbits.ICTMR = 1;
    IC4CONbits.ICM = 0b010;

    IFS0bits.IC4IF = 0;
    IPC4bits.IC4IP = 7;
    IEC0bits.IC4IE = 1;
    IC4CONbits.ON = 1;
    // whatever else you need to do to initialize your module
    STATE = one;
    averageCounter = 0;
    averageVal = 0;

}

char CAPTOUCH_IsTouched(void) {
    if (averageVal < CAPTHRESHOLD) {
        return TRUE;
    }
    return FALSE;
}


//State machine determines the timer of the sensor and finds the average frequency through the noise
void capStateMachine() {
    switch (STATE) {
        case one:
            startTime = IC4BUF;
            STATE = two;
            break;
        case two:
            endTime = IC4BUF;
            periodT = (endTime - startTime) * SECPTICK;
            if (periodT < 0) {
                STATE = one;
                startTime = endTime;
                break;
            }
            freq = 1 / (periodT);
            changingAvgVal(freq, BUFFERLENGTH, &buffer, &averageCounter, &averageVal);
            STATE = one;
            startTime = endTime;
            break;
        default:
            printf("Cap State Machine Error");
    }
}


void __ISR(_INPUT_CAPTURE_4_VECTOR) InputCapture_Handler(void) {
    IFS0bits.IC4IF = 0;
    // IC4BUF contains the timer value when the rising edge occurred.
    capStateMachine();
}

