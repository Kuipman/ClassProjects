/* 
 * File:   QEI.c
 * Author: quillanzhen
 *
 */

//Default libraries
#include <stdio.h>
#include <stdlib.h>
//user libraries
#include "xc.h"
#include "QEI.h"

#define PHASEA PORTDbits.RD6 // Pin 36
#define PHASEB PORTDbits.RD7 // Pin 37
#define DEGREESPERTURN 3.75

enum turning {
    dir_init,
    CW,
    CCW
} dir;

enum phaseBits { // A & B
    zero, // 0 | 0
    one, // 0 | 1
    two, // 1 | 0
    three, // 1 | 1
    skipping
} state;

int AB;
int degrees;
int A;
int B;

char QEI_Init(void) {
    // INIT Change notify
    CNCONbits.ON = 1; // Change Notify On
    CNENbits.CNEN15 = 1; //enable one phase
    CNENbits.CNEN16 = 1; //enable other phase
    int temp = PORTD; // this is intentional to ensure a interrupt occur immediately upon enabling
    IFS1bits.CNIF = 0; // clear interrupt flag
    IPC6bits.CNIP = 1; //set priority
    IPC6bits.CNIS = 3; // and sub priority
    IEC1bits.CNIE = 1; // enable change notify

    // the rest of the function goes here

    degrees = 0;
    //Initialize States
    AB = PHASEA * 2 + PHASEB;
    switch (AB) {
        case 0:
            state = zero;
            break;
        case 1:
            state = one;
            break;
        case 2:
            state = two;
            break;
        case 3:
            state = three;
            break;
        default:
            break;

    }

    //Initialize direction
    dir = dir_init;
}

int QEI_GetPosition(void) {
    return degrees;
}

void QEI_ResetPosition() {
    degrees = 0;
    state = zero;
}

/*in state machine:
 * state zero:
 * if phase A is changed, it is moving ccw, else phase B is changed,
 * if both phases change, skip the state
 * state one:
 * if phase A changes, it is moving cw, else phase B is changing
 * state two:
 * if phase A is constant, it is moving ccw, else if phases A changes, go cw
 * state three:
 * if phase A is constant it is moving right, else if phases A changes, go ccw
 * case skipping:
 * go back to init
 * 
 */
void state_machine() {
    switch (state) {
        case zero:
            if (!A && B) {
                dir = CW;
                degrees += DEGREESPERTURN;
                state = one;
            } else if (A && !B) {
                dir = CCW;
                degrees -= DEGREESPERTURN;
                state = two;
            } else if (A && B) {
                state = skipping;
            }
            break;
        case one:
            if (A && B) {
                dir = CW;
                degrees += DEGREESPERTURN;
                state = three;
            } else if (!A && !B) {
                dir = CCW;
                degrees -= DEGREESPERTURN;
                state = zero;
            } else if (!A && B) {
                state = skipping;
            }
        case two:
            if (!A && !B) {
                dir = CW;
                degrees += DEGREESPERTURN;
                state = zero;
            } else if (A && B) {
                dir = CCW;
                degrees -= DEGREESPERTURN;
                state = three;
            } else if (!A && B) {
                state = skipping;
            }
            break;
        case three:
            if (A && !B) {
                dir = CW;
                degrees += DEGREESPERTURN;
                state = two;
            } else if (!A && B) {
                dir = CCW;
                degrees -= DEGREESPERTURN;
                state = one;
            } else if (!A && !B) {
                state = skipping;
            }
            break;
        case skipping:
            state = PHASEA * 2 + PHASEB;
            break;
        default:
            printf("State Machine Error");
    }
}

void __ISR(_CHANGE_NOTICE_VECTOR) ChangeNotice_Handler(void) {
    static char readPort = 0;
    readPort = PORTD; // this read is required to make the interrupt work
    IFS1bits.CNIF = 0;
    //anything else that needs to happen goes here
    A = PHASEA;
    B = PHASEB;
    state_machine();
}