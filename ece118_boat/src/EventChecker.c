/**
 * File: EventChecker.c
 * Project: ECE 118 - Final Project (BOAT)
 * Authors: Nicholas Kuipers
 * 
 * @brief Library of event checkers ran through by ES_Framework during a
 *      standard loop. For the BOAT, event checkers are:
 *      - Check bumper interactions. If any bumper value changes, starts a debounce timer (Timer 2)
 *          that, upon expiry (10ms), reads the bumper values again and delivers a proper BUMPER EVENT
 *      - Check tape sensor interactions. If any tape sensor value changes, returns a TAPE EVENT
 *      - Check 1.5k and 2k beacon sensor interactions. If any beacon value changes, return BEACON_2K or BEACON_1_5K
 *      - Check ToF sensor pins. Returns a TOF EVENT that simply updates the ToF values tracked globally
 */

/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/
#include <stdio.h>

#include "EventChecker.h"
#include "ES_Configure.h"
#include "ES_Events.h"
#include "serial.h"
#include "AD.h"
#include "BOAT.h"
#include "BOAT_Movement.h"
#include "BOAT_Launcher.h"
#include "BOAT_Sensors.h"
#include "BOAT_PinDefs.h"

#include "BumperService.h"
#include "TapeAndTrackService.h"
#include "BeaconService.h"
#include "BOAT_HSM.h"
#include "Protocol2.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/

/*******************************************************************************
 * EVENTCHECKER_TEST SPECIFIC CODE                                                             *
 ******************************************************************************/

//#define EVENTCHECKER_TEST
#ifdef EVENTCHECKER_TEST
#include <stdio.h>
#define SaveEvent(x) do {eventName=__func__; storedEvent=x;} while (0)

static const char *eventName;
static ES_Event storedEvent;
static ES_Event lastBumper;
#endif

/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this EventChecker. They should be functions
   relevant to the behavior of this particular event checker */

/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                    *
 ******************************************************************************/

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function checkBumpers(void)
 * @param none
 * @return TRUE if bumper state changes, FALSE otherwise
 * 
 * @brief Checks the current values of the four bumpers of the BOAT. These are
 *      digital inputs each supplemented with a pull-down resistor, so no hysteresis
 *      is necessary.
 *      - If the bumper state changes, event records the current value
 * @return 
 */

uint8_t checkBumpers(void)
{
    static unsigned char lastBumperValue = 0;    // static variable only receives init 0 during first function call -- saves future values
    unsigned char curBumperValue = BOAT_ReadBumpers();
    unsigned char BumperChange = lastBumperValue ^ curBumperValue;
    ES_Event ThisEvent;
    if(BumperChange)            // if any bumper is pressed, returns an event
    {
        lastBumperValue = curBumperValue;
        ThisEvent.EventType = BUMPER_EVENT;
        ThisEvent.EventParam = curBumperValue;
        printf("\r\nBUMPER EVENT: %i", curBumperValue);
        PostBumperService(ThisEvent);
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/**
 * @Function checkTapeSensors(void)
 * @param none
 * @return TRUE if tape state changes, FALSE otherwise
 * 
 * @brief Checks the current values of the four tape sensors of the BOAT. These are
 *      digital inputs, so no hysteresis is necessary.
 *          - Works almost identically to the checkBumper function, but rather than
 *              post the event to another service the information is passed directly
 *              as a TAPE_EVENT to the HSM
 * @author Nicholas Kuipers 
 */
uint8_t checkTapeSensors(void)
{
    ES_Event ThisEvent;
    static unsigned char lastTapeValue = 0;
    unsigned char currentTapeValue = BOAT_ReadTapeSensors();
    unsigned char TapeChange = lastTapeValue ^ currentTapeValue;   // XOR - any change is reflected in TapeChange
    if(TapeChange)
    {
        lastTapeValue = currentTapeValue;
        ThisEvent.EventType = TAPE_EVENT;
        ThisEvent.EventParam = currentTapeValue;
        PostTapeAndTrackService(ThisEvent);
        //PostHSM(ThisEvent);
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/**
 * @Function checkTrackWire(void)
 * @param none
 * @return TRUE if track wire changes, FALSE otherwise
 * 
 * @brief Checks the current value of the track wire. This is an analog input, making
 *      hysteresis necessary.
 *      - Initial value is set as TRACKWIRE_START, define value at top of EventChecker.h
 *      - When analog pin value reaches above high threshold and value is LOW, set value to HIGH and return a TRACKWIRE_EVENT
 *      - When analog pin value reaches below low threshold and value is HIGH, set value to LOW and return a TRACKWIRE_EVENT
 *      - In either case, event parameter will be HIGH or LOW to indicate the new value of the track wire
 * @author Nicholas Kuipers
 */
uint8_t checkTrackWire(void)
{
    ES_Event ThisEvent;
    static unsigned char lastDigitalTrackValue = 0;              // can be 0 or 1 (LOW or HIGH)
    unsigned int currentTrackValue = BOAT_ReadTrackWireSensor();   // analog value, 10-bit
    
    /* 
     * First, check if the lastTrackValue_DIG is 0 and the currentTrackValue is
     *      above the high threshold. This indicates a move from low to high
     */
    if(lastDigitalTrackValue == 0 && currentTrackValue > TRACKWIRE_HIGH_THRESHOLD)
    {
        lastDigitalTrackValue = 1;
        ThisEvent.EventType = TRACKWIRE_EVENT;
        ThisEvent.EventParam = lastDigitalTrackValue;
        PostTapeAndTrackService(ThisEvent);
        return TRUE;
    }
    
    if(lastDigitalTrackValue == 1 && currentTrackValue < TRACKWIRE_LOW_THRESHOLD)
    {
        lastDigitalTrackValue = 0;
        ThisEvent.EventType = TRACKWIRE_EVENT;
        ThisEvent.EventParam = lastDigitalTrackValue;
        PostTapeAndTrackService(ThisEvent);
        return TRUE;
    }
    return FALSE;
}

/**
 * @Function check2kBeacon(void)
 * @param none
 * @return TRUE if beacon changes, FALSE otherwise
 * 
 * @brief Checks the current value of the 2k beacon. This is an analog input, making hysteresis necessary.
 *      - Works nearly identically to checkTrackWire event
 * @author Nicholas Kuipers
 */
uint8_t check2kBeacon(void)
{
    ES_Event ThisEvent;
    static unsigned char digitalValue_2k = 0;               // can be 0 or 1 (LOW or HIGH)
    //static unsigned int averageBeaconValue = 1;
    unsigned int currentBeaconValue = BOAT_ReadBeacon_2k();   // analog value, 10-bit
    
    //averageBeaconValue = (currentBeaconValue + averageBeaconValue) / 2;
    //printf("\r\nCurrent Beacon Value = %i", currentBeaconValue);
    
    /* 
     * First, check if the lastTrackValue_DIG is 0 and the currentTrackValue is
     *      above the high threshold. This indicates a move from low to high
     */
    if(digitalValue_2k == 0 && currentBeaconValue > BEACON_2K_HIGH_THRESHOLD)
    {
        digitalValue_2k = 1;
        ThisEvent.EventType = BEACON_EVENT_2K;
        ThisEvent.EventParam = 0x1;
        PostBeaconService(ThisEvent);
        return TRUE;
    }
    
    else if(digitalValue_2k == 1 && currentBeaconValue < BEACON_2K_LOW_THRESHOLD)
    {
        digitalValue_2k = 0;
        ThisEvent.EventType = BEACON_EVENT_2K;
        ThisEvent.EventParam = 0;
        PostBeaconService(ThisEvent);
        return TRUE;
    }
    return FALSE;
}

/**
 * @Function check1_5kBeacon(void)
 * @param none
 * @return TRUE if beacon changes, FALSE otherwise
 * 
 * @brief Checks the current value of the 1.5k beacon. Analog input, making hysteresis necessary.
 *      - Works nearly identically to checkTrackWire event
 * @author Nicholas Kuipers
 */
uint8_t check1_5kBeacon(void)
{
    ES_Event ThisEvent;
    static unsigned char last1_5kBeaconValue = 0;               // can be 0 or 1 (LOW or HIGH)
    unsigned int currentBeaconValue = BOAT_ReadBeacon_1_5k();   // analog value, 10-bit
    
    /* 
     * First, check if the lastTrackValue_DIG is 0 and the currentTrackValue is
     *      above the high threshold. This indicates a move from low to high
     */
    if(last1_5kBeaconValue == 0 && currentBeaconValue > BEACON_1_5K_HIGH_THRESHOLD)
    {
        last1_5kBeaconValue = 1;
        ThisEvent.EventType = BEACON_EVENT_1_5K;
        ThisEvent.EventParam = last1_5kBeaconValue;
        PostBeaconService(ThisEvent);
        return TRUE;
    }
    
    if(last1_5kBeaconValue == 1 && currentBeaconValue < BEACON_1_5K_LOW_THRESHOLD)
    {
        last1_5kBeaconValue = 0;
        ThisEvent.EventType = BEACON_EVENT_1_5K;
        ThisEvent.EventParam = last1_5kBeaconValue;
        PostBeaconService(ThisEvent);
        return TRUE;
    }
    return FALSE;
}

/**
 * @Function updateTOF(void)
 * @param none
 * @return will always return FALSE for ES Framework
 * 
 * @brief Checks the current values of the analog pins connected to the three ToF analog pins from
 *      the ESP32, and updates the values tracked by the HSM. 
 *      - Does not return an event or interact with the ES framework outside of getting called on every repetition of the framework
 * @return 
 */
uint8_t updateTOF(void)
{
    HSM_UpdateTOF(BOAT_ReadTOF(LEFT_TOF), BOAT_ReadTOF(RIGHT_TOF), BOAT_ReadTOF(REAR_TOF));
    return FALSE;    // this will always be returned, as we don't want an event to generate from this function
} 

/**
 * @Function checkSwitch(void)
 * @param none
 * @return TRUE if switch toggled, FALSE otherwise
 * 
 * @brief Check the current value of the switch pin (PORTV6). If the switch value changes (use lastSwitchValue variable),
 *      post the event directly to the HSM.
 */
uint8_t checkSwitch(void)
{
    ES_Event ThisEvent;
    static unsigned char lastDigitalSwitchValue = 0; // can be 0 or 1 (LOW or HIGH)
    
    unsigned int currentSwitchValue = BOAT_ReadSwitch(); // analog value, 10-bit

    /* 
     * First, check if the lastTrackValue_DIG is 0 and the currentTrackValue is
     *      above the high threshold. This indicates a move from low to high
     */
    if (lastDigitalSwitchValue == 0 && currentSwitchValue > SWITCH_HIGH_THRESHOLD) {
        lastDigitalSwitchValue = 1;
        ThisEvent.EventType = SWITCH_EVENT;
        ThisEvent.EventParam = lastDigitalSwitchValue;
        PostHSM(ThisEvent);
        return TRUE;
    }

    if (lastDigitalSwitchValue == 1 && currentSwitchValue < SWITCH_LOW_THRESHOLD) {
        lastDigitalSwitchValue = 0;
        ResetHSM();
        //ThisEvent.EventType = SWITCH_EVENT;
        //ThisEvent.EventParam = lastDigitalSwitchValue;
        //PostHSM(ThisEvent);
        return FALSE;
    }
    return FALSE;
}

/**
 * @Function checkSerial(void)
 * @param none
 * @return will always return FALSE -- is used to parse a potential incoming packet
 *      or discard useless information
 * 
 * @brief Parses incoming bytes over UART1 for usable ToF packets. Updates the ToF information
 * @author Nicholas Kuipers
 */
/*
uint8_t checkSerial(void)
{
    ES_Event ThisEvent;
    static uint16_t Left_ToF, Right_ToF, Rear_ToF = 0;
    Packet rxPacket;
    
    while(IsReceiveEmpty() == FALSE)    // if the UART circular buffer has values, build a packet from them and discard the rest
    {
        if(BuildRxPacket(GetChar(), &rxPacket, 0))
            printf("\r\nAn error was encountered in BuildRxPacket");
    }
    // At this point a packet should be available. Now, we need to parse it.
    if(rxPacket.len != 7)
        printf("ERROR: Wrong packet length sent");
    else   // Packet is good, parse packet for ToF sensor values
    {
        Left_ToF = (uint16_t)rxPacket.payload[1] << 8  + (uint16_t)rxPacket.payload[2];
        Right_ToF = (uint16_t)rxPacket.payload[3] << 8 + (uint16_t)rxPacket.payload[4];
        Rear_ToF = (uint16_t)rxPacket.payload[5] << 8  + (uint16_t)rxPacket.payload[6];   
        HSM_UpdateTOF(BOAT_ReadTOF(Left_ToF), BOAT_ReadTOF(Right_ToF), BOAT_ReadTOF(Rear_ToF));
    }
}
 * */



/* 
 * The Test Harness for the event checkers is conditionally compiled using
 * the EVENTCHECKER_TEST macro (defined either in the file or at the project level).
 * No other main() can exist within the project.
 * 
 * It requires a valid ES_Configure.h file in the project with the correct events in 
 * the enum, and the correct list of event checkers in the EVENT_CHECK_LIST.
 * 
 * The test harness will run each of your event detectors identically to the way the
 * ES_Framework will call them, and if an event is detected it will print out the function
 * name, event, and event parameter. Use this to test your event checking code and
 * ensure that it is fully functional.
 * 
 * If you are locking up the output, most likely you are generating too many events.
 * Remember that events are detectable changes, not a state in itself.
 * 
 * Once you have fully tested your event checking code, you can leave it in its own
 * project and point to it from your other projects. If the EVENTCHECKER_TEST marco is
 * defined in the project, no changes are necessary for your event checkers to work
 * with your other projects.
 */
#ifdef EVENTCHECKER_TEST
#include <stdio.h>
static uint8_t(*EventList[])(void) = {EVENT_CHECK_LIST};

void PrintEvent(void);

void main(void) {
    BOARD_Init();
    /* user initialization code goes here */

    // Do not alter anything below this line
    int i;

    printf("\r\nEvent checking test harness for %s", __FILE__);

    while (1) {
        if (IsTransmitEmpty()) {
            for (i = 0; i< sizeof (EventList) >> 2; i++) {
                if (EventList[i]() == TRUE) {
                    PrintEvent();
                    break;
                }

            }
        }
    }
}

void PrintEvent(void) {
    printf("\r\nFunc: %s\tEvent: %s\tParam: 0x%X", eventName,
            EventNames[storedEvent.EventType], storedEvent.EventParam);
}
#endif