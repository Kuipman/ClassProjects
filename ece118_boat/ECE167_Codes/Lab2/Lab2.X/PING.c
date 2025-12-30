/* 
 * File:   PING.c
 * Author: quillanzhen
 *
 */

//Default Libraries
#include <stdio.h>
#include <stdlib.h>

//User Libraries
#include "xc.h"
#include "PING.h"
#include "timers.h"
#include "AD.h"

//Defining globals
#define TRIGGERPIN PORTDbits.RD11 //pin 35
#define DELAYLEN 3750 // 60ms
#define LISTENLEN 736 // 11.7ms
#define SLOPE 0.0170
#define YINT -9.1565

#define BUFFERLENGTH 100

enum sensorState {
    delay,
    trigger,
    listen
} pingSensorState;

int startTime;
int listenTimer;
int delayTimer;

int curTime;

//Helper Functions
int avgVal;
int avgCounter;
int buffer[BUFFERLENGTH];

int changingValAvg(int val, int bufferLength, int *bufferMatrix, int *count, int *avg) {
    if (val < 0) {
        return;
    }
    bufferMatrix[(*count) % bufferLength] = val / bufferLength;
    *avg = *avg + (val / bufferLength) - bufferMatrix[((*count) + 1) % bufferLength];
}

char PING_Init(void) {
    // following block inits the timer
    T4CON = 0;
    T4CONbits.TCKPS = 0b110;
    PR4 = 0x000A; // this is not the timer value wanted -> changed to every 16us
    T4CONbits.ON = 1;
    IFS0bits.T4IF = 0;
    IPC4bits.T4IP = 3;
    IEC0bits.T4IE = 1;

    // following block inits change notify
    CNCONbits.ON = 1; // Change Notify On
    CNENbits.CNEN14 = 1;
    int temp = PORTD; // this is intentional to ensure a interrupt occur immediately upon enabling
    IFS1bits.CNIF = 0; // clear interrupt flag
    IPC6bits.CNIP = 1; //set priority
    IPC6bits.CNIS = 3; // and sub priority
    IEC1bits.CNIE = 1; // enable change notify
    //Anything else that needs to occur goes here

    TIMERS_Init();
    TRISDbits.TRISD11 = 0; //setting appropriate pin (35) as output
    delayTimer = 0;
    listenTimer = 0;
    TRIGGERPIN = 0;
    pingSensorState = delay;


}

unsigned int PING_GetDistance(void) {
    return SLOPE * curTime + YINT;
}

unsigned int PING_GetTimeOfFlight(void) {
    return curTime;
}

void __ISR(_CHANGE_NOTICE_VECTOR) ChangeNotice_Handler(void) {
    static char readPort = 0;
    readPort = PORTD; // this read is required to make the interrupt work
    IFS1bits.CNIF = 0;
    //Anything else that needs to occur goes here
    curTime = TIMERS_GetMicroSeconds() - startTime;

}

void pingSensorStateMachine() {
    switch (pingSensorState) {
        case delay:
            delayTimer++;
            if (delayTimer > DELAYLEN) {
                pingSensorState = trigger;
            }
            break;
        case trigger:
            startTime = TIMERS_GetMicroSeconds();
            TRIGGERPIN = TRUE;
            delayTimer = 0;
            pingSensorState = listen;
            break;
        case listen:
            TRIGGERPIN = FALSE;
            delayTimer++;
            listenTimer++;
            if (listenTimer > LISTENLEN) {
                pingSensorState = delay;
            }
            break;
        default:
            printf("Ping Sensor State Machine Error");
    }
}

void __ISR(_TIMER_4_VECTOR) Timer4IntHandler(void) {
    IFS0bits.T4IF = 0;
    //Anything else that needs to occur goes here
    pingSensorStateMachine();
}
