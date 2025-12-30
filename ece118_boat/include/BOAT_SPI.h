/*
 * File:   BOAT_SPI.h
 * Author: Nicholas Kuipers
 *
 * Created on May 19, 2023 at 3:47PM
 *
 * Abstract: Library for packet-based SPI communication with the UNO32 and
 *      another microcontroller
 * @author Nicholas Kuipers
 */

#ifndef BOAT_SPI_H
#define BOAT_SPI_H

#include <BOARD.h>

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/

#define MAXPAYLOADLENGTH 128 

/*******************************************************************************
 * PUBLIC TYPEDEFS                                                             *
 ******************************************************************************/

typedef enum{
    INIT,
    INIT_RES,
    LOC_UPDATE,
    PACKET_ERROR
}Packet_Type;

/**
 * @brief SPI Packet protocol
 * @note Draws heavy inspiration from ECE 121 Packet Protocol
 * 
 * @author Nicholas Kuipers
 */
typedef struct {
    unsigned char len;                           // length of payload in bytes
    unsigned char packetType;                    // defined in above enum
    unsigned char payload[MAXPAYLOADLENGTH];     // variable length, 1st byte = messageID
    unsigned char checksum;                      // calculated over the payload
} Packet;

/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/**
 * @Function BOAT_SPIInit(void)
 * @param None.
 * @return None.
 * @brief Initializes the registers, interrupts, and pins to drive 
 *      the SPI module on the UNO32 (specifically the PIC32MX320F128H)
 * @author Nicholas Kuipers, 20230519
 */
void BOAT_SPIInit(void);

/**
 * @Function SPI_Read(void)
 * @param none
 * @return Packet with up to 128 byte payload
 * @brief Reads a payload from the SPI buffer and returns a packet
 * @author Nicholas Kuipers
 */
Packet SPI_Read(void);

/**
 * @Function SPI_Write(void)
 * @param sendPacket, information to send over SPI
 * @return SUCCESS or FAILURE
 * @brief Writes a payload to the SPI buffer
 * @author Nicholas Kuipers
 */
char SPI_Write(Packet sendPacket);


#endif    /* BOAT_H */
