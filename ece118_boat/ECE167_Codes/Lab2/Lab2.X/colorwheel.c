/* 
 * File:   colorwheel.c
 * Author: quillanzhen
 *
 * Created on April 28, 2022, 2:49 PM
 */

//Default Libraries
#include <stdio.h>
#include <stdlib.h>

//User Libraries
#include "BOARD.h"
#include "Oled.h"
#include "QEI.h"
#include "pwm.h"

/*
 * Setup:
 * Pin36 = Pin B
 * Pin37 = Pin A
 * Turn right to increase degrees
 * Turn left to decrease degrees
 * pin 3 = red
 * pin 5 = green
 * pin 6 = blue
 */
#define DUTYCYCLECHANGE 8.3
int position;
int rDuty, gDuty, bDuty;
int curDegree;

int main(void) {
    BOARD_Init();
    OledInit();
    PWM_Init();
    QEI_Init();
    PWM_AddPins(PWM_PORTZ06 | PWM_PORTY12 | PWM_PORTY10);

    position = 0;
    rDuty = 0;
    gDuty = 0;
    bDuty = 1000;

    while (1) {
        position = QEI_GetPosition();
        if (position > 0) {
            curDegree = position % 360;
            if (curDegree <= 120) {
                bDuty = 1000 - (DUTYCYCLECHANGE * curDegree);
                gDuty = (DUTYCYCLECHANGE * curDegree);
                rDuty = 0;
            } else if (curDegree <= 240) {
                bDuty = 0;
                gDuty = 1000 - (DUTYCYCLECHANGE * (curDegree - 120));
                rDuty = DUTYCYCLECHANGE * (curDegree - 120);
            } else if (curDegree <= 360) {
                bDuty = DUTYCYCLECHANGE * (curDegree - 240);
                gDuty = 0;
                rDuty = 1000 - (DUTYCYCLECHANGE * (curDegree - 240));
            }
        } else {
            curDegree = (-1 * position) % 360; //Accounting for negatives
            if (curDegree <= 120) {
                bDuty = 1000 - (DUTYCYCLECHANGE * curDegree);
                rDuty = (DUTYCYCLECHANGE * curDegree);
                gDuty = 0;
            } else if (curDegree <= 240) {
                bDuty = 0;
                rDuty = 1000 - (DUTYCYCLECHANGE * (curDegree - 120));
                gDuty = DUTYCYCLECHANGE * (curDegree - 120);
            } else if (curDegree <= 360) {
                bDuty = DUTYCYCLECHANGE * (curDegree - 240);
                rDuty = 0;
                gDuty = 1000 - (DUTYCYCLECHANGE * (curDegree - 240));
            }
        }

        PWM_SetDutyCycle(PWM_PORTZ06, 1000 - rDuty);
        PWM_SetDutyCycle(PWM_PORTY12, 1000 - gDuty);
        PWM_SetDutyCycle(PWM_PORTY10, 1000 - bDuty);

        char OledString [100];
        sprintf(OledString, "Degrees: %d\nRed: %d\nBlue: %d\nGreen: %d\n", position, rDuty, bDuty, gDuty);
        OledDrawString(OledString);
        OledUpdate();
        OledClear(OLED_COLOR_BLACK);


    }
}

