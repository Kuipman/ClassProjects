#include <stdio.h>
#include <stdint.h>
#include "MessageIDs.h"

#define PACKETBUFFERSIZE 16
#define MAXPAYLOADLENGTH 128 
#define HEAD   0xCC
#define TAIL   0xB9

// Test Bench Defines
#define CHECKSUM_SIMULATION      0
#define BUILDRXPACKET_SIMULATION 1

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

typedef enum
{
    RX_START,
    RX_LEN,
    RX_MESSAGEID,
    RX_PAYLOAD,
    RX_CHECKSUM
} RX_StateMachine;

/*******************************************************************************
 * PRIVATE VARIABLES                                                            *
 ******************************************************************************/

CircBuffer_Packet PBUF;
RX_StateMachine RXSM;

Packet rxPacket, txPacket;
static uint8_t payloadPos_RX, payloadPos_TX;    // index indicators for payloads in rx, tx packets
static uint8_t RXPacketComplete;                // bool flags indicating when RX packet is fully built

uint8_t feedCounter;


/*******************************************************************************
 * PUBLIC FUNCTION IMPLEMENTATIONS                                             *
 ******************************************************************************/

uint8_t getPacketBufferSize()
{
    uint8_t currentSize = PBUF.tail - PBUF.head;

    if(currentSize > 0)
        return currentSize;
    else if(currentSize < 0)
        return PACKETBUFFERSIZE + currentSize;
    else
        return 0;
}

uint8_t Protocol_QueuePacket()
{
    if(PBUF.isFull)
        return 1;   // Packet Buffer is full
    if(getPacketBufferSize() == PACKETBUFFERSIZE - 1)
        PBUF.isFull = 1;
    PBUF.buffer[PBUF.tail++] = rxPacket;
    if(PBUF.tail == PACKETBUFFERSIZE)
        PBUF.tail = 0;
    return 0;             // Success
}

unsigned char Protocol_CalcIterativeChecksum(unsigned char payloadByte, unsigned char curChecksum)
{
    curChecksum = (curChecksum >> 1) + (curChecksum << 7);    // performs circular rotation of bits
    curChecksum += payloadByte;                               // adds new byte to the checksum
    curChecksum &= 0xFF;                                      // bitmask to set any potential above bits to 0 (not really needed here, but
                                                              // may come in handy with larger types later)
    return curChecksum;
}

uint8_t BuildRxPacket (unsigned char receivedByte, Packet *rxPacket, unsigned char reset)
{
    switch(RXSM)
    {
        case RX_START:
        {
            if(receivedByte == HEAD)
                RXSM = RX_LEN;
            break;
        }
        case RX_LEN:
        {
            if(receivedByte < 1 || receivedByte > MAXPAYLOADLENGTH)
                return 1;           // Error  --  specified length of payload is longer than supported by protocol
            rxPacket->len = receivedByte;
            RXSM = RX_MESSAGEID;
            break;
        }
        case RX_MESSAGEID:
        {
            if(receivedByte == 0)
                return 1;           // Error -- message has an invalid ID
            rxPacket->messageID = receivedByte;
            rxPacket->payload[payloadPos_RX++] = receivedByte;
            rxPacket->checksum = Protocol_CalcIterativeChecksum(receivedByte, rxPacket->checksum);
            RXSM = RX_PAYLOAD;
            break;
        }
        case RX_PAYLOAD:
        {
            if(receivedByte != TAIL && payloadPos_RX < rxPacket->len)
            {
                rxPacket->payload[payloadPos_RX++] = receivedByte;
                rxPacket->checksum = Protocol_CalcIterativeChecksum(receivedByte, rxPacket->checksum);
            }
            else if(receivedByte == TAIL)
            {
                if(payloadPos_RX != rxPacket->len)
                    return 1;       // Error  --  tail byte encountered before specified payload length
                RXSM = RX_CHECKSUM;
            }
            else     // payloadPos_RX is greater than the specified length
            {
                return 1;           // Error  --  payload length is longer than specified by the 'len' byte
            }
            break;
        }
        case RX_CHECKSUM:
        {
            if(receivedByte != rxPacket->checksum)
                return 1;           // Error  --  incorrect checksum
            RXPacketComplete = 1;
            RXSM = RX_START;
            break;
        }
    }
    return 0;
}

unsigned char characterFeed_LEDS_SET()
{
    switch(feedCounter)
    {
        case 1: // Head
            return 0xCC;
            break;
        case 2: // Len
            return 0x02;
            break;
        case 3: // MessageID
            return 0x81;
            break;
        case 4: // One-byte payload
            return 0xFF;
            break;
        case 5: // Tail
            return 0xB9;
            break;
        case 6: // Checksum
            return 0xBF;      // Should be our result value
            break;
        case 7: // \r carriage return
            return 0x0D;
            break;
        case 8: // \n Line feed
            return 0x0A;
            break;
        default:
            return 0;
    }
}


///////////////////////////////////////////////////////////////////////

#if CHECKSUM_SIMULATION

int main()
{
    printf("/nChecksum Function Simulation\n");
    unsigned char checksum, payloadByte = 0;
    while(payloadByte != '#')
    {
        printf("Please enter a single character: ");
        payloadByte = getchar();
        if(payloadByte == '\n')
            continue;
        checksum = Protocol_CalcIterativeChecksum(payloadByte, checksum);
        printf("\nYou entered %c. The current checksum is %02x\n\n", payloadByte, checksum);
    }
}

#endif  /* CHECKSUM_SIMULATION */

#if BUILDRXPACKET_SIMULATION



int main()
{
    // Initialize the packet values
    rxPacket.len       = 0;
    rxPacket.messageID = 0;
    rxPacket.checksum  = 0;
    payloadPos_RX      = 0;
    txPacket.len       = 0;
    txPacket.messageID = 0;
    txPacket.checksum  = 0;
    payloadPos_TX      = 0;
    RXPacketComplete   = 0;

    feedCounter        = 1;

    // Finally, the state machine(s)
    RXSM = RX_START;

    while(1)
    {
        if(RXPacketComplete)
        {
            Protocol_QueuePacket();
            feedCounter = 1;
        }
        unsigned char receivedByte = characterFeed_LEDS_SET();
        feedCounter++;
        if(receivedByte != '\n')
        {
            if(BuildRxPacket(receivedByte, &rxPacket, 0))
                RXSM = RX_START;
        }
    }

}

#endif   /* BUILDRXPACKET_SIMULATION*/