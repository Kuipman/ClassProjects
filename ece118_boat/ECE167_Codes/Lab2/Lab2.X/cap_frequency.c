/* 
 * File:   cap_frequency.c
 * Author: quillanzhen
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "xc.h"
#include "CAPTOUCH.h"
#include "BOARD.h"
#include "Oled.h"

/*Set up:
 * Pin 35 -> Timer Output
 */


char string[50];
int touching;

int main(void) {
    BOARD_Init();
    OledInit();
    CAPTOUCH_Init();

    while (1) {
        touching = CAPTOUCH_IsTouched();
        if (touching) {
            sprintf(string, "Contact");
        } else {
            sprintf(string, "No Contact");
        }

        sprintf(string, "Frequency: %d", returnFreq());
        OledDrawString(string);
        OledUpdate();
        OledClear(OLED_COLOR_BLACK);
    }
}
