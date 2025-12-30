/***
 *  @file ARD_Protocol2.h
 *  @version 1.0
 *  @author Nicholas Kuipers
 *  @purpose Packet library for ARD that parses incoming/outgoing data from PIC
 *  @note Imported and repurposed from prior work in ECE 121
 */

#pragma once

#include "MessageIDs.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>

/*******************************************************************************
 * PUBLIC #DEFINES                                                            *
 ******************************************************************************/

#define PACKETBUFFERSIZE 16
#define MAXPAYLOADLENGTH 128 
#define HEAD   0xCC
#define TAIL   0xB9

#define DEBUG_PROTOCOL    0

/*******************************************************************************
 * PUBLIC TYPEDEFS
 ******************************************************************************/

/**
 * @brief Defines a standard data packet sent between the PIC and ARD
 * 
 * @author Nicholas Kuipers
 */
typedef struct Packet
{
    unsigned char len;                           // length of payload in bytes
    unsigned char messageID;                     // defined in MessageIDs.h
    unsigned char payload[MAXPAYLOADLENGTH];     // variable length, 1st byte = messageID
    unsigned char checksum;                      // calculated over the payload
} Packet;

/**
 * @brief Circular Buffer designed for tracking and storage of various Packet
 *      structures (defined above). Similar in design to the CircBuffer typedef
 *      found in UART.h
 * @author Nicholas Kuipers
 */
typedef struct CircBuffer_Packet
{
    Packet buffer[PACKETBUFFERSIZE];
    int head;
    int tail;
    int isFull;
} CircBuffer_Packet;

/**
 * @brief State machine designed for receiving a packet from the console one byte
 *      at a time. Used in BuildRXPacket() function
 */
typedef enum
{
    PSM_START,
    PSM_LEN,
    PSM_MESSAGEID,
    PSM_PAYLOAD,
    PSM_CHECKSUM
} Packet_StateMachine;

/*******************************************************************************
 * PUBLIC VARIABLES                                                           *
 ******************************************************************************/
//extern CircBuffer_Packet PBUF;
//extern Packet_StateMachine PSTATE;


//extern Packet rxPacket, txPacket;
//extern uint8_t payloadPos_RX, payloadPos_TX;
//extern uint8_t RXPacketComplete;

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                           *
 ******************************************************************************/

// This is important for the arduino to recognize this is C, not C++
//#ifdef __cplusplus
// extern "C" {
//#endif



/**
 * @brief Initializes the interface between the PIC and ARD. This involves initializing
 *      the UART (UART.h) and initializing the library's circular buffer, PBUF
 * @param baudrate , a legal UART baudrate (115200)
 * @return 0 if success, 1 if error
 * @author Nicholas Kuipers
 */
int Protocol_Init(unsigned long baudrate);

/**
 * @brief Checks for a completed incoming packet. If one is present, the packet
 *      is queued into the packet buffer (i.e. written to tail).
 * @note This is best implemented either in the main event loop or in a timer, so it
 *      can continually check for completed incoming packets
 * @param none
 * @return isFull variable from PBUF -- 1 if the packet buffer is full, 0 otherwise
 * @author Nicholas Kuipers
 */
uint8_t Protocol_QueuePacket();

/**
 * @brief Reads the next packet (from 'head') from the packet buffer, and
 *      executes an operation based on the messageID
 * @param *type , packet/message type     (messageID variable)
 * @param *len  , length of the payload   (length variable)
 * @param *msg  , payload                 (payload array)
 * @return 0 if success, 1 if error
 * @author Nicholas Kuipers
 */
int Protocol_DeQueuePacket();

/**
 * @brief Composes and sends a full packet to the ECE 121 Main Console
 * @param len, length of full payload (data array in the packet)
 * @param ID , type of message to be sent (messageID)
 * @param Payload, pointer to the first unsigned char in payload/data array
 * @return 0 if success, 1 if error
 * @author Nicholas Kuipers
 */
int Protocol_SendPacket(unsigned char len, unsigned char ID, void *Payload);

/**
 * @brief Takes in a C-formatted string and uses the ID_DEBUG message format to deliver a
 *      payload to the terminal (i.e. this is the protocol version of printf)
 * @param Message, the payload to be printed to terminal (built via a char array)
 * @return 0 if success, 1 if error
 * @author Nicholas Kuipers
 */
int Protocol_SendDebugMessage(char *Message);

/**
 * @brief Reads the message ID of the next available packet
 * @param none
 * @return ID, or 0 if no packets are available
 * @author Nicholas Kuipers
 */
unsigned char Protocol_ReadNextPacketID();

/**
 * @brief Primary driver function for receiving and building an RX packet from the circular buffer in UART.h.
 *      When this is called in some main() function, this first checks that the reset value is not set, then
 *      checks the current value of the RX_StateMachine (through switch/case) and performs a respective action
 *      based on the state (usually, writing a byte from the RX Circular Buffer to an indicated field in the packet).
 * 
 * @param receivedByte, byte from the RX buffer to be placed into the packet
 * @param rxPacket    , a pointer to the RX packet struct info from the RX circular buffer is being read to
 * @param reset       , when this value is set to anything but 0, the state machine is reverted to IDLE and the
 *      packet is dropped
 * @return 0 if success, 1 if error
 * 
 */
uint8_t BuildRxPacket (unsigned char receivedByte, Packet *rxPacket, unsigned char reset);

/**
 * @brief ARD Driver function that takes in a completed string of received characters over UART
 *      and parses them into the rxPacket. If something is wrong with the packet, this will return 
 *      an ERROR (1), prompting for the .ino file to send an ERROR message back to the UNO.
 *      Function then calls the operate() function to determine what to do with the received packet
 * @param inputString, a pointer to the next packet to be parsed (serial RX is handled in .ino)
 * @return 0 if success, 1 if error
 * @author Nicholas Kuipers
 */
uint8_t ARD_ProcessRXPacket(void *inputString);

/**
 * @brief Determines operation to perform based on the messageID of the received packet
 * @param pointer to the packet containing operation instructions
 * @return 0 if success, 1 if error
 */
int Protocol_Operate(Packet *op_packet);

//#ifdef __cplusplus
//}
//#endif

