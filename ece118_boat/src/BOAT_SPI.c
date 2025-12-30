/*
 * File:   BOAT_SPI.c
 * Author: Nicholas Kuipers
 *
 * Created on May 19, 2023 at 4:10PM
 *
 * Abstract: Library for packet-based SPI communication with the UNO32 and
 *      another microcontroller
 * @author Nicholas Kuipers
 */

#include <BOARD.h>
#include <BOAT.h>
#include <BOAT_Movement.h>
#include <BOAT_Launcher.h>
#include <BOAT_PinDefs.h>
#include <BOAT_SPI.h>
#include <xc.h>

#include <stdio.h>
#include <math.h>
#include <pwm.h>
#include <serial.h>
#include <AD.h>

/*******************************************************************************
 * PRIVATE #DEFINES                                                             *
 ******************************************************************************/

/*******************************************************************************
 * PRIVATE TYPEDEFS                                                             *
 ******************************************************************************/

/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/*******************************************************************************
 * PUBLIC FUNCTION IMPLEMENTATIONS                                             *
 ******************************************************************************/

/**
 * @Function BOAT_SPIInit(void)
 * @param None.
 * @return None.
 * @brief Initializes the registers, interrupts, and pins to drive 
 *      the SPI module on the UNO32 (specifically the PIC32MX320F128H)
 * @author Nicholas Kuipers, 20230519
 */
void BOAT_SPIInit(void)
{
    
}

/**
 * @Function SPI_Read(void)
 * @param none
 * @return Packet with up to 128 byte payload
 * @brief Reads a payload from the SPI buffer and returns a packet
 * @author Nicholas Kuipers
 */
Packet SPI_Read(void)
{
    
}

/**
 * @Function SPI_Write(void)
 * @param sendPacket, information to send over SPI
 * @return SUCCESS or FAILURE
 * @brief Writes a payload to the SPI buffer
 * @author Nicholas Kuipers
 */
char SPI_Write(Packet sendPacket)
{
    
}