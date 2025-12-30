/**
 * @File BOAT_Serial.ino
 * @project BOAT - ECE 118
 * @author Nicholas Kuipers
 * 
 * @brief Testbench for the serial interface between the arduino uno (ARD)
 *    and the PIC32 (PIC). Interface utilizes a UART connection via the 
 *    hardware pin connections on the arduino (RX and TX) and the RF2/RF3 pins
 *    on the I/O shield of the PIC.
 *    
 *    Packet structure utilizes a modified version of the protocol library built
 *    in ECE 121, and follows the same format.
 *    
 *  The Testbench performs the following:
 *    - Initializes serial at baud rate 115200 (default baud for the PIC)
 *    - Initializes the protocol library, which mainly just sets up the library's
 *        private variables
 *    - In the setup(), ARD waits for a packet to be received from the PIC. Specifically,
 *        this packet needs to have the STANDBY messageID and a 4 byte payload (hard-coded on the PIC).
 *        The ARD calculates the checksum of the incoming message and checks with the checksum byte for
 *        accuracy. Then, ARD takes the payload and divides by 2 -- the result is placed into a new packet to be
 *        transmitted back to the PIC. The new checksum is calculated and sent as well -- the PIC parses the received packet
 *        for correct messageID (STANDBY_AYE), correct payload, and correct checksum. 
 *    
 */

/************************************************************************/
/**********  INCLUDES AND DEFINES     ***********************************/
/************************************************************************/
 // For Arduino, this declaration is needed to tell the compiler the library
 // is C code, NOT C++
 extern "C"
 {
#include <ARD_Protocol2.h>
 }
#include <stdlib.h>    // for memory allocation

#define MAXRXBUFFERSIZE    10

/************************************************************************/
/**********  TYPEDEFS                 ***********************************/
/************************************************************************/

typedef enum{
  INIT,
  STANDING_BY,
  ENGAGED
} ARD_STATE;

typedef struct{
  String buffer[MAXRXBUFFERSIZE];
  int head;
  int tail;
  int isFull;
} RX_BUFFER;

/************************************************************************/
/**********  VARIABLES                ***********************************/
/************************************************************************/

ARD_STATE state = INIT;
String inputString = "";      // a String to hold incoming data
bool packetReady = false;  // whether the string is complete
RX_BUFFER rxBUF;

const int debugLED = 2;

/************************************************************************/
/**********  HELPER FUNCTION PROTOTYPES        **************************/
/************************************************************************/

uint8_t writeToBuffer();
uint8_t readFromBuffer();


/************************************************************************/
/**********  MAIN FUNCTIONS           ***********************************/
/************************************************************************/

void setup() {
  // Initialize Serial and Protocol
  Serial.begin(115200);
  Protocol_Init(115200);
  // @todo Initialize the sensor libraries
  // @todo Initialize the mapping library

  // Initialize the RX Buffer for the UART comms structure
  rxBUF.head   = 0;
  rxBUF.tail   = 0;
  rxBUF.isFull = 0;

  // reserve 200 bytes for the inputString:
  inputString.reserve(200);   // this will be replaced by protocol stuff

  // Set up debug LED, lights up when stated in loop
  pinMode(debugLED, OUTPUT);

  // Give a brief delay
  delay(10);
}

/* @Function void loop()
*  @brief Main function utilizes a simple state machine to determine its actions on every repetition.
*     - INIT: Device will perform no actions until it receives a proper STANDBY packet from the UNO. If
*         it receives a bad packet it will return an ERROR packet and will not move states
*     - STANDING_BY: Device will perform no actions until the power switch on the bot moves from LOW to HIGH. If
*       the switch is HIGH upon device startup switch will be ignored until it is moved back to LOW
*     - ENGAGED: Device operating state. Device will:
*         - Read up-to-date values from the sensors, when appropriate
*         - Every 200ms device will send an ID_UPDATE message containing up-to-date sensor readings and any
*             other relevant information (i.e. mapping, coordinate updates, etc)
*               - This is performed with a 200ms timer
*/
void loop() {
  
  // State Machine
  switch(state)
  {
    case INIT:
    {
      if(packetReady)
      {
        packetReady = false;

      }
      break;
    }
    case STANDING_BY:
    {
      digitalWrite(debugLED, HIGH);
      delay(1000);
      digitalWrite(debugLED, LOW);
      delay(1000);
      break;
    }
    case ENGAGED:
    {

      break;
    }
  }


/************************************************************************/
/**********  HELPER FUNCTIONS         ***********************************/
/************************************************************************/



  /*
  // print the string when a newline arrives:
  if (stringComplete) {
    Serial.println(inputString);
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
  //else
    //Serial.println("Still waiting...");
    */
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.

  SerialEvent occurs whenever new data becomes available on the hardware serial RX.
  This function is called automatically at the end of each loop() iteration. 
*/
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      packetReady = true;
    }
  }
}
