// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"
#include "Leds_Lab06.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

#include "Ascii.h"
#include "Oled.h"
#include "OledDriver.h"

int main() {

    BOARD_Init();
    printf("Initializing LEDs: Part 1\n");
    LEDS_INIT();
    char LED_Pattern = 0x01;
    while(1)
    {
        for(int i = 0; i < 100000; i++)
            LEDS_SET(LED_Pattern);
        LED_Pattern++;
    }
    
    //LEDS_INIT();
    //char newPattern = 'a';
    //LEDS_SET(newPattern);
    
    BOARD_End();
    while(1);
}


/*  SPARE CODE
 * //THIS RUNS THE CODE IN A CONTINUOUS BINARY ADDITION (AUTOMATICALLY RESETS TOO)
    while(1)
    {
        for(int i = 0; i < 100000; i++)
            LEDS_SET(LED_Pattern);
        LED_Pattern++;
    }
 
 
 
 
 
 
 */

