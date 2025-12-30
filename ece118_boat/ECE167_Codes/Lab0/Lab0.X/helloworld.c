/* 
 * File:   helloworld.c
 * Author: quillanzhen
 *
 * Created on April 8, 2022, 12:05 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "BOARD.h"
#include "SERIAL.h"

int main(void) {
    BOARD_Init();
    printf("Hello World!\n");
    BOARD_End();
    while (1);
}

