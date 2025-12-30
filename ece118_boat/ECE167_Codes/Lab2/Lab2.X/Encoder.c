/* 
 * File:   Encoder.c
 * Author: quillanzhen
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "xc.h"
#include "BOARD.h"
#include "Oled.h"
#include "QEI.h"

/*
 * Set up:
 * pin36 connects to pinA of encoder
 * pin37 connects to pinB of encoder
 */

//Setting Initials:
int position_QEI;
char string[30];

int main(void) {
    BOARD_Init();
    OledInit();
    QEI_Init();

    position_QEI = 0;
    printf("\nBegin\n");
    while (1) {
        position_QEI = QEI_GetPosition();
        sprintf(string, "\nDegrees:%d \n", position_QEI);
        OledDrawString(string);
        OledUpdate();
        OledClear(OLED_COLOR_BLACK);
    }
}

