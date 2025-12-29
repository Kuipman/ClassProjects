/**
 *  File:     HelloWorld.c
 *  Project:  ECE 118 - Lab 0
 *  Author:   Nicholas Kuipers
 *
 */

#include <BOARD.h>
#include <roach.h>
#include <stdio.h>
#include "xc.h"

#define HELLOWORLDTEST 0

#if HELLOWORLDTEST

int main() {
    
    BOARD_Init();
    Roach_Init();
    
    printf("\n");   // allows the GUI to read output properly
    printf("Hello World!");
    while(1) {}
    
    return 0;
}

#endif  /* HELLOWORLDTEST */