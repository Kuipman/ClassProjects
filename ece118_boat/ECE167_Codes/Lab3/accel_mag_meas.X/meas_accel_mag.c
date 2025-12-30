/* 
 * File:   meas_accel_mag.c
 * Author: quillanzhen
 *
 * Created on May 12, 2022, 2:43 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "BOARD.h"
#include "timers.h"
#include "BNO055.h"


#define FIFTYHZ 20

/*
 * 
 */
int main(void) {
    BOARD_Init();
    TIMERS_Init();
    BNO055_Init();

//    if (BNO055_Init() != 1) {
//        printf("Reading Failed");
//    }

    //Accel readings
    //    printf("%d\r\n", BNO055_ReadAccelX());
    //    printf("%d\r\n", BNO055_ReadAccelY());
    //    printf("%d\r\n", BNO055_ReadAccelZ());

    //Mag readings
    //    printf("X: %d Y: %d Z: %d", BNO055_ReadMagX(), BNO055_ReadMagY(), BNO055_ReadMagZ());

    while (1) {

        if (TIMERS_GetMilliSeconds() % FIFTYHZ == 0) {
            //printf("X: %d Y: %d Z: %d\r\n", BNO055_ReadMagX(), BNO055_ReadMagY(), BNO055_ReadMagZ());
            //printf("%d\r\n", BNO055_ReadMagZ());
            printf("X: %d, Y: %d, Z: %d\r\n", BNO055_ReadMagX(), BNO055_ReadMagY(), BNO055_ReadMagZ());//BNO055_ReadAccelX(), BNO055_ReadAccelY(), BNO055_ReadAccelZ());//, BNO055_ReadMagX(), BNO055_ReadMagY(), BNO055_ReadMagZ());
        }
    }
}



