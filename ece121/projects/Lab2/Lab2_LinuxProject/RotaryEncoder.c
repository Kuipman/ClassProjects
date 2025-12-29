/***
 *  @file RotaryEncoder.c
 *  @version 1.0
 *  @author Nicholas Kuipers
 *  @purpose Provides a serial (COM port) interface between the ECE 121 Main Console
 *      and the microcontroller
 */

/*******************************************************************************
 * #INCLUDES                                                                   *
 ******************************************************************************/

#include "RotaryEncoder.h"

/*******************************************************************************
 * PRIVATE VARIABLES                                                            *
 ******************************************************************************/


/*******************************************************************************
 * PRIVATE FUNCTIONS PROTOTYPES                                                 *
 ******************************************************************************/

/*******************************************************************************
 * PUBLIC FUNCTION IMPLEMENTATIONS                                             *
 ******************************************************************************/

/**
 * @description Initializes the AS5047D Rotary Encoder via SPI by performing the following
 *      steps:
 *      - initialize the SPI module for PIC32
 *          - if DEBUG active, sends a sample command frame then read frame to RE and pushes
 *              received frame back into a Debug packet to Protocol
 * 
 * @param interfaceMode, can be either blocking mode or interrupt mode as specified
 * @return 0 if SUCCESS, 1 if ERROR   */
int RotaryEncoder_Init(char interfaceMode)
{
    if(interfaceMode == ENCODER_BLOCKING_MODE)
    {
        SPI_Init();
    }
    else   // ENCODER_INTERRUPT_MODE
    {
        return 1;       //@todo rewrite SPI.h/.c to allow for interrupts
    }
    return 0;   // SUCCESS
}

/**
 * @brief Accesses the register on the Rotary Encoder via SPI
 * @return 14-bit value representing the raw encoder angle (0 - 16384) */
unsigned short RotaryEncoder_ReadRawAngle(void)
{
    
    return 0;
}

#if DEBUG_ROTARYENCODER

int main()
{
    BOARD_Init();
    Protocol_Init(115200);
    
    SPI_Init();
}

#endif    /* DEBUG_ROTARYENCODER */