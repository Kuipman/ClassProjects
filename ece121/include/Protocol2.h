/***
 *  @file Protocol2.h
 *  @version 1.0
 *  @author Nicholas Kuipers
 *  @purpose Provides a serial (COM port) interface between the ECE 121 Main Console
 *      and the microcontroller
 */

#ifndef PROTOCOL_H
#define	PROTOCOL_H

#include "MessageIDs.h"
#include "UART.h"
#include "LEDs.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "BOARD.h"
#include <sys/attribs.h>
#include <xc.h> 

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
 * @brief Defines a standard data packet that fulfills the standard for sending and
 *      receiving information between the Microcontroller and the ECE 121 Main Console.
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
 * PUBLIC FUNCTIONS                                                           *
 ******************************************************************************/

/**
 * @brief Initializes the interface between the microcontroller and the ECE 121
 *      Main Console. This involves initializing the UART (via UART.h) as well as 
 *      initializing this library's circular buffer: PBUF
 * @param baudrate , a legal UART baudrate (for this course, generally 115200)
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
 * @brief Determines operation to perform based on the messageID of the received packet
 * @param pointer to the packet containing operation instructions
 * @return 0 if success, 1 if error
 */
int Protocol_Operate(Packet *op_packet);

/***************************************************************/

/**
 * @brief 'Flushes' the Packet Buffer. In other words, resets all buffer values to initial
 * @param none
 * @return none
 * @author Nicholas Kuipers
 */
//void flushPacketBuffer();

/**
 * @brief Converts a Little Endian integer to a Big Endian, or vice versa
 * @param num, the 32-bit/4-byte value to be converted
 * @return the Endian conversion as another unsigned int 
 * @author Nicholas Kuipers
 */
//unsigned int convertEndian(unsigned int *num);
/*******************************************************************************
 * PRIVATE FUNCTIONS
 * Generally these functions would not be exposed but due to the learning nature 
 * of the class some are are noted to help you organize the code internal 
 * to the module. 
 ******************************************************************************/

/**
 * @Function char Protocol_CalcIterativeChecksum(unsigned char charIn, unsigned char curChecksum)
 * @param charIn, new char to add to the checksum
 * @param curChecksum, current checksum, most likely the last return of this function, can use 0 to reset
 * @return the new checksum value
 * @brief Returns the BSD checksum of the char stream given the curChecksum and the new char
 * @author mdunne */
//unsigned char Protocol_CalcIterativeChecksum(unsigned char charIn, unsigned char curChecksum);

/**
 * This macro initializes all LEDs for use. It enables the proper pins as outputs and also turns all
 * LEDs off.
 */
//#define LEDS_INIT() do {LATECLR = 0xFF; TRISECLR = 0xFF;} while (0)

/**
 * Provides a way to quickly get the status of all 8 LEDs into a uint8, where a bit is 1 if the LED
 * is on and 0 if it's not. The LEDs are ordered such that bit 7 is LED8 and bit 0 is LED0.
 */
//#define LEDS_GET() (LATE & 0xFF)

/**
 * This macro sets the LEDs on according to which bits are high in the argument. Bit 0 corresponds
 * to LED0.
 * @param leds Set the LEDs to this value where 1 means on and 0 means off.
 */
//#define LEDS_SET(leds) do { LATE = (leds); } while (0)
#endif	/* PROTOCOL_H */

