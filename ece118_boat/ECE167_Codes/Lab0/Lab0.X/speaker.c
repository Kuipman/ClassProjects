/* 
 * File:   speaker.c
 * Author: quillanzhen
 *
 * Created on April 8, 2022, 1:09 PM
 */
 
#include <stdio.h>
#include <stdlib.h>
#include "BOARD.h"
#include "ToneGeneration.h"
#include <xc.h>

int main(void){
    BOARD_Init();
    ToneGeneration_Init();
    ToneGeneration_SetFrequency(440);
    ToneGeneration_ToneOn();
}

