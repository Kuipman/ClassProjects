/***
 *  @file Protocol2.c
 *  @version 1.0
 *  @author Nicholas Kuipers
 *  @purpose Library for Protocol2.h -- provides a serial (COM port) interface between the ECE 121 Main Console
 *      and the microcontroller
 */

/*******************************************************************************
 * #INCLUDES                                                                   *
 ******************************************************************************/

#include "Protocol2.h"

/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/

/*******************************************************************************
 * PRIVATE VARIABLES                                                            *
 ******************************************************************************/

CircBuffer_Packet   PBUF;
Packet_StateMachine PSTATE;

Packet rxPacket, txPacket;
static uint8_t payloadPos_RX, payloadPos_TX;    // index indicators for payloads in rx, tx packets
static uint8_t RXPacketComplete;                // bool flags indicating when RX packet is fully built

/*******************************************************************************
 * PRIVATE FUNCTIONS PROTOTYPES                                                 *
 ******************************************************************************/

void          flushPacketBuffer();
unsigned int  convertEndian(unsigned int *num);
uint8_t       getPacketBufferSize();
unsigned char Protocol_CalcIterativeChecksum(unsigned char payloadByte, unsigned char curChecksum);
unsigned int  CalcPong(unsigned int ping);

/*******************************************************************************
 * PUBLIC FUNCTION IMPLEMENTATIONS                                             *
 ******************************************************************************/

/**
 * @brief Initializes the interface between the microcontroller and the ECE 121
 *      Main Console. This involves initializing the UART (via UART.h) as well as 
 *      initializing this library's circular buffer: PBUF
 * @param baudrate , a legal UART baudrate (for this course, generally 115200)
 * @return 0 if success, 1 if error
 * @author Nicholas Kuipers
 */
int Protocol_Init(unsigned long baudrate)
{
    // First, set up the UART with its circular buffers and baudrate parameter
    initializeUART(baudrate);
    // Next, since several functions influence the I/O LEDs, these must be initialized as well
    LEDs_Init();
    // Initialize values for the packet buffer -- can be performed nicely with flushPacketBuffer()
    flushPacketBuffer();
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
    // Finally, the state machine(s)
    PSTATE = PSM_START;
    
    return 0;    // Success
}

/**
 * @brief Checks for a completed incoming packet. If one is present, the packet
 *      is queued into the packet buffer (i.e. written to tail).
 * @note This is best implemented either in the main event loop or in a timer, so it
 *      can continually check for completed incoming packets
 * @param none
 * @return isFull variable from PBUF -- 1 if the packet buffer is full, 0 otherwise
 * @author Nicholas Kuipers
 */
uint8_t Protocol_QueuePacket()
{
    if (PBUF.isFull)
        return 1;   // Packet Buffer is full
    if (getPacketBufferSize() == PACKETBUFFERSIZE - 1)
        PBUF.isFull = 1;
    PBUF.buffer[PBUF.tail++] = rxPacket;
    if (PBUF.tail == PACKETBUFFERSIZE)
        PBUF.tail = 0;
    return 0;       // Packet buffer not full, insertion successful
}

/**
 * @brief Reads the next packet (from 'head') from the packet buffer and
 *      executes an operation based on the message ID
 * @return 0 if success, 1 if error
 * @author Nicholas Kuipers
 */
int Protocol_DeQueuePacket()
{
    if(getPacketBufferSize() == 0 && !PBUF.isFull)
        return 1;      // no packets in buffer

    Packet* op_packet = &PBUF.buffer[PBUF.head];
    Protocol_Operate(op_packet);

    if(++PBUF.head == PACKETBUFFERSIZE)
        PBUF.head = 0;
    if(PBUF.isFull)
        PBUF.isFull = 0;
    
    return 0;   // Success
}

/**
 * @brief Composes and sends a full packet to the ECE 121 Main Console
 * @param len, length of full payload (data array in the packet)
 * @param ID , type of message to be sent (messageID)
 * @param Payload, pointer to the first unsigned char in payload/data array
 * @return 0 if success, 1 if error
 * @author Nicholas Kuipers
 */
int Protocol_SendPacket(unsigned char len, unsigned char ID, void *Payload)
{
    unsigned char checksum = 0;
    putchar(0xCC);                 // Send Head
    putchar(len);                  // Send len
    if(ID == ID_DEBUG)
    {
        putchar(ID);
        checksum = Protocol_CalcIterativeChecksum(ID, checksum);
        len = len - 1;
    }
    for(int i = 0; i < len; i++) 
    {
        // First convert the void ptr to unsigned char ptr, then dereference the ptr
        unsigned char* temp = (unsigned char*)Payload + i;
        putchar(*temp);      // Send Payload
        checksum = Protocol_CalcIterativeChecksum(*temp, checksum);
    }
    putchar(0xB9);                 // Send Tail
    putchar(checksum);             // Send calculated checksum
    putchar('\r');                 // Send carriage return
    putchar('\n');                 // Send new line
    
    return 0;    // Success
}

/**
 * @brief Takes in a C-formatted string and uses the ID_DEBUG message format to deliver a
 *      payload to the terminal (i.e. this is the protocol version of printf)
 * @param Message, the payload to be printed to terminal (built via a char array)
 * @return 0 if success, 1 if error
 * @author Nicholas Kuipers
 */
int Protocol_SendDebugMessage(char *Message)
{
    unsigned char* temp = 0;
    int len = 0; 
    for(len = 0; len < MAXPAYLOADLENGTH - 1; len++)
    {
        temp = (unsigned char*)Message + len;
        if((*temp) == 0)
            break;
    }
    Protocol_SendPacket(len + 1, ID_DEBUG, Message);
    return 0;
}

/**
 * @brief Reads the message ID of the next available packet
 * @param none
 * @return ID, or 0 if no packets are available
 * @author Nicholas Kuipers
 */
unsigned char Protocol_ReadNextPacketID()
{
    if(getPacketBufferSize() == 0)
        return 0;    // No packets are available
    return PBUF.buffer[PBUF.head].messageID;
}

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
uint8_t BuildRxPacket (unsigned char receivedByte, Packet *rxPacket, unsigned char reset)
{
    switch (PSTATE)
    {
        case PSM_START:
            if (receivedByte == HEAD)
                PSTATE = PSM_LEN;
            break;
        case PSM_LEN:
            if (receivedByte < 1 || receivedByte > MAXPAYLOADLENGTH)
                return 1;           // Error  --  specified length of payload is longer than supported by protocol
            rxPacket->len = receivedByte;
            PSTATE = PSM_MESSAGEID;
            break;
        case PSM_MESSAGEID:
            if (receivedByte == 0)
                return 1;           // Error -- message has an invalid ID
            payloadPos_RX = 0;
            rxPacket->messageID = receivedByte;
            rxPacket->payload[payloadPos_RX++] = receivedByte;
            rxPacket->checksum = Protocol_CalcIterativeChecksum(receivedByte, 0);
            PSTATE = PSM_PAYLOAD;
            break;
        case PSM_PAYLOAD:
            if (receivedByte != TAIL && payloadPos_RX < rxPacket->len)
            {
                rxPacket->payload[payloadPos_RX++] = receivedByte;
                rxPacket->checksum = Protocol_CalcIterativeChecksum(receivedByte, rxPacket->checksum);
            }
            else if (receivedByte == TAIL)
            {
                if (payloadPos_RX != rxPacket->len)
                    return 1;       // Error  --  tail byte encountered before specified payload length
                PSTATE = PSM_CHECKSUM;
            }
            else 
            {
                return 1;           // Error  --  payload length is longer than specified by the 'len' byte
            }
            break;
        case PSM_CHECKSUM:
            if (receivedByte != rxPacket->checksum)
                return 1;           // Error  --  incorrect checksum
            RXPacketComplete = 1;
            PSTATE = PSM_START;
            break;
    }
    return 0;
}

/**
 * @brief Determines operation to perform based on the messageID of the received packet
 * @param ID, received from Protocol_ReadNextPacketID()
 * @param msg, reserved for messages with potentially-long payloads
 * @return 0 if success, 1 if error
 */
int Protocol_Operate(Packet *op_packet)
{
    switch(op_packet->messageID)
    {
        case ID_LEDS_SET:
        {
            setLEDValues(op_packet->payload[1]);         // by default an LEDS_SET message has 1 byte of payload
            break;
        }
        case ID_LEDS_GET:
        {
            txPacket.payload[0] = ID_LEDS_STATE;
            txPacket.payload[1] = getLEDValues();
            Protocol_SendPacket(0x02, ID_LEDS_STATE, &txPacket.payload);
            break;
        }
        case ID_PING:
        {
            txPacket.payload[0] = ID_PONG;
            unsigned int pong = 0;
            unsigned int temp = 0;
            for(int i = 4; i > 0; i--)     // pulls bytes into the pong integer
            {
                temp = (unsigned int)op_packet->payload[i];
                temp = temp << (8*(i - 1));
                pong |= temp;
            }
            pong = CalcPong(pong);    // @todo better naming convention?
            for(int j = 1; j < 5; j++)     // places bytes of new pong value into payload
            {
                temp = (pong >> 8*(j - 1));
                txPacket.payload[j] = (unsigned char)(temp & 0xFF);
            }
            Protocol_SendPacket(0x05, ID_PONG, &txPacket.payload);
            break;
        }
        default:
        {
            return 1;
        }
    }
    return 0;
}

/*******************************************************************************
 * PRIVATE FUNCTIONS IMPLEMENTATIONS                                           *
 ******************************************************************************/

/**
 * @brief 'Flushes' the Packet Buffer. In other words, resets all buffer values to initial
 * @param none
 * @return none
 * @author Nicholas Kuipers
 */
void flushPacketBuffer()
{
    Packet zeroPacket;
    zeroPacket.messageID = ID_INVALID;
    // First, sets all packets in the buffer to an invalid packet ID (i.e. a 'zero' packet)
    for(int i = 0; i < PACKETBUFFERSIZE; i++)
        PBUF.buffer[i] = zeroPacket;
    // Clears the remaining PBUF variables
    PBUF.head = 0;
    PBUF.tail = 0;
    PBUF.isFull = 0;
}

/**
 * @brief Converts a Little Endian integer to a Big Endian, or vice versa
 * @note Verified algorithm in separate file: EndianTest.c
 * @param num, the 32-bit/4-byte value to be converted
 * @return the Endian conversion as another unsigned int 
 * @author Nicholas Kuipers
 */
unsigned int convertEndian(unsigned int *num)
{
    unsigned int input  = *num;
    unsigned int result = 0;       // we add values from num to this int
    uint8_t      temp   = 0;
    /*
    *   Through four repetitions (i.e. one repetition per byte), a specified byte from the input value (copied
    *       from the num parameter) is copied to a temporary, one-byte long variable. Through bitmasking and
    *       bit shifting, this temporary value is copied to the respective byte on an unsigned integer result value.
    *   
    *   Once all four repetitions have concluded and all bytes are copied over, the result variable is returned
    */
    for(unsigned int i = 0; i < 4; i++)
    {
        temp = input >> (8*i);
        temp &= 0xFF;   // singles out least significant byte
        result |= temp << (24 - (8*i));  // writes to opposite byte in the resulting integer
    }
    return result;
}

/**
 * @brief Returns the size of the packet buffer -- built with the same logic as the equivalent function
 *      for circular buffers in Uart.c
 * 
 * @return size of the packet buffer as a uint8_t 
 */
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

/**
 * @brief Iterative function : calculates checksum based on current checksum value and new char value.
 *      - Perform circular shift to checksum
 *      - Add payloadByte value to checksum
 * 
 * @param payloadByte , a char value from the payload of the received RX packet
 * @param curChecksum , current value of the checksum BEFORE this function updates it
 * @return new checksum as an unsigned char
 * @author Nicholas Kuipers
 */
unsigned char Protocol_CalcIterativeChecksum(unsigned char payloadByte, unsigned char curChecksum)
{
    curChecksum = (curChecksum >> 1) + (curChecksum << 7);    // performs circular rotation of bits
    curChecksum += payloadByte;                               // adds new byte to the checksum
    curChecksum &= 0xFF;                                      // bitmask to set any potential above bits to 0 (not really needed here, but
                                                              // may come in handy with larger types later)
    return curChecksum;
}

/**
 * @brief Takes in an integer tracking the four bytes sent from a Ping request and does the following
 *      to create an integer for a Pong response and returns the result
 *      - convert the Endian
 *      - divide the result by 2
 *      - convert the Endian (again)
 * @param ping, an integer tracking the four bytes from a recent Ping request
 * @return pong, an integer containing the proper calculations for a pong reply
 */
unsigned int CalcPong(unsigned int ping)
{
    unsigned int pong = convertEndian(&ping);
    pong = pong / 2;     //@todo bitshift by 1
    return convertEndian(&pong);
}

/*******************************************************************************
 * Protocol2.h Test Bench                                                      *
 ******************************************************************************/

/**
 * @brief Main event loop:
 *      - Checks if an RX packet has been completed from a previous iteration
 *          - if true, checks the messageID of the new packet -- if LEDS_SET/GET it is executed immediately
 *          - else, sends the complete packet to PBUF
 *      - Checks the RX Circular Buffer in Uart.c for an available byte
 *          - if true, pulls the byte via GetChar and attempts to build more of the current RX packet
 *          - checks for an error : if RX packet is invalid, resets state machine and discards the byte
 *      - Else, check the messageID of the next packet in PBUF (if available) to poll an instruction
 *          - Uses a switch/case in a private function to determine course of action depending on the messageID
 * 
 *  @author Nicholas Kuipers
 */
#if DEBUG_PROTOCOL

int main()
{
    BOARD_Init();
    Protocol_Init(115200);
    unsigned char receivedByte = 0x00;
    char initialMessage[128];
    sprintf(initialMessage, "Lab 1 Protocol Test. Compiled on: %s at %s", __DATE__, __TIME__);
    Protocol_SendDebugMessage(initialMessage);
    
    while(1)
    {
        if(RXPacketComplete)
        {
            RXPacketComplete = 0;    // reset the flag
            if(rxPacket.messageID == ID_LEDS_SET || rxPacket.messageID == ID_LEDS_GET)
            {
                Protocol_Operate(&rxPacket);
            }
            else
                Protocol_QueuePacket();
        }
        if(checkRXCircBuffer())    //RX circular buffer in UART not empty
        {
            receivedByte = (unsigned char)getchar();
            if(BuildRxPacket(receivedByte, &rxPacket, 0))
                PSTATE = PSM_START;
        }
        else          // Check PBUF for any packets to process
        {
            if((PBUF.tail - PBUF.head) != 0 || PBUF.isFull != 0)
            {
                if(Protocol_ReadNextPacketID() != ID_INVALID)
                {
                    Protocol_DeQueuePacket();   // operates a packet from the buffer
                }
                else
                    PBUF.head++;     // skips over the invalid packet
            }
        }
    }
}

#endif /* PROTOCOL_TEST */