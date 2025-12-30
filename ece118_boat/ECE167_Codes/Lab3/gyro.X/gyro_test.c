/* 
 * File:   gyro_test.c
 * Author: quillanzhen
 *
 * Created on May 10, 2022, 6:29 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "BOARD.h"
#include <timers.h>
#include <BNO055.h>


/*
 * 
 */
#define TEN 10000
#define HOUR 3600000
#define FIFTYHZ 20

int main(void) {
    BOARD_Init();
    TIMERS_Init();
    BNO055_Init();
    //printf("\nBegin\n");
    //printf("X \t Y \t Z \t Time\r\n");
    while (1) {
        while (TIMERS_GetMilliSeconds() < TEN) {
            //printf("X%d,Y: %d,Z: %d", BNO055_ReadGyroX(), BNO055_ReadGyroY(), BNO055_ReadGyroZ());
            //        }
            //        printf(Hour)
            //while(TIMERS_GetMilliSeconds()<HOUR){
            if (TIMERS_GetMilliSeconds() % FIFTYHZ == 0) {
                //printf("%5d \t %5d \t %5d \t %5d\r\n",BNO055_ReadGyroX(),BNO055_ReadGyroY(),BNO055_ReadGyroZ(),TIMERS_GetMilliSeconds());
                //printf("X: %d, Y: %d, Z: %d\r\n", BNO055_ReadGyroX(), BNO055_ReadGyroY(), BNO055_ReadGyroZ());
                printf("%d\r\n", BNO055_ReadGyroZ());

            }
        }
    }
}





