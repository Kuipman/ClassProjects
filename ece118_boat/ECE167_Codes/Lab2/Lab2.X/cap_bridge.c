/* 
 * File:   cap_bridge.c
 * Author: quillanzhen
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "xc.h"
#include "BOARD.h"
#include "Oled.h"
#include "AD.h"
#include "CAPTOUCH.h"

/*
 * Set up:
 * Use 3.3V to drive circuit
 * OPAMP connects to A1 
 */

#define ADTOVOLTAGE 3.3/1023 //adc reading to voltage
#define UPPERVOLTTHRESHOLD 2.0 // upper threshold for volt
#define LOWERVOLTTHRESHOLD 1.0 // lower threshold for volt
#define COUNTERTHRESHOLD 5 // counter cannot count pass this point | used for no contact

enum signalType {
    touch,
    off,
    noContact
} state;

int input;
int voltInput;
int counter;
char string[60];

int main(void) {
    BOARD_Init();
    AD_Init();
    OledInit();
    AD_AddPins(AD_A1); // OPAMP output to A1

    state = noContact;
    counter = 0;

    while (1) {
        input = AD_ReadADPin(AD_A1);
        voltInput = input * ADTOVOLTAGE;
        switch (state) { // state machine assigns voltage levels to state
            case noContact:
                if (voltInput > UPPERVOLTTHRESHOLD) {
                    state = touch;
                } else {
                    sprintf(string, "No Contact");
                }
                break;
            case touch:
                counter = 0;
                if (voltInput < LOWERVOLTTHRESHOLD) {
                    state = off;
                } else {
                    sprintf(string, "Contact");
                }
                break;
            case off: // after sensor is touched
                counter++;
                if (voltInput > LOWERVOLTTHRESHOLD) {
                    state = touch;
                } else if (counter < COUNTERTHRESHOLD) {
                    state = noContact;
                } else {
                    sprintf(string, "Contact");
                }
                break;
            default:
                printf("Error in state machine");
        }

        OledDrawString(string);
        OledUpdate();
        OledClear(OLED_COLOR_BLACK);
    }
}

