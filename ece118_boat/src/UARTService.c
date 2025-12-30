/**
 * File: UARTService.c
 * Project: ECE 118 - Final Project
 * Author: Nicholas Kuipers
 * 
 * @brief Header for Beacon Service function, designed to integrate in the
 *      broader ES_Framework built for ECE 118.
 *      - Both the 2k and 1.5k beacons are tied to this service, so this first
 *          differentiates which event (BEACON_EVENT_2K or BEACON_EVENT_1_5K) called it
 *      - Passes the respective parameter as a separate event with parameter to the HSM 
 */
/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "BOARD.h"
#include "BOAT.h"
#include "AD.h"
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "UARTService.h"
#include "BOAT_HSM.h"
#include <stdio.h>

#include <serial.h>
#include "Protocol2.h"
#include "timers.h"
#include "BOAT_Sensors.h"
/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/

/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/

/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                    *
 ******************************************************************************/

static uint8_t MyPriority;            // priority of 0 - 8
Packet rxPacket_UART;
static uint8_t packetReturn;
static uint16_t Left_ToF, Right_ToF, Rear_ToF;

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @brief Initializes the Beacon Service function, called automatically by the
 *      ES_Framework at the beginning of code execution.
 * @note This will post an ES_INIT event to the event queue for the Bumper Service,
 *      requiring an adequate handler within the run function
 * @param Priority - internal variable to track which event queue is used
 * @return TRUE if successful, FALSE otherwise
 */
uint8_t InitUARTService(uint8_t Priority)
{
    ES_Event ThisEvent;

    MyPriority = Priority;

    // in here you write your initialization code
    // this includes all hardware and software initialization
    // that needs to occur.
    
    rxPacket_UART.messageID = 0;
    rxPacket_UART.checksum = 0;
    rxPacket_UART.len = 0;
    packetReturn = 0;
    
    Left_ToF = 0;
    Right_ToF = 0;
    Rear_ToF = 0;

    // post the initial transition event
    ThisEvent.EventType = ES_INIT;
    //ES_Timer_InitTimer(0, 50);           // initializes timer 0, elapses after 5ms
    
    if (ES_PostToService(MyPriority, ThisEvent) == TRUE) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * @brief Wrapper function allowing for post of an event to the respective
 *      queue for the Service Function.
 * @param ThisEvent - the event (a struct with "type" and "param" variables) to
 *      be posted to queue
 * @return TRUE if successful, FALSE otherwise
 */
uint8_t PostUARTService(ES_Event ThisEvent)
{
    return ES_PostToService(MyPriority, ThisEvent);
}

/**
 * @Version 1
 * @brief Function is called any time a new event
 *      is passed to the respective event queue.
 *      Version 1 simply takes in the respective event and passes it onto the HSM
 * 
 * @param ThisEvent - the event (type and param) to be responded to
 * @return event - return event (type and param), that in general should be ES_NO_EVENT
 */
ES_Event RunUARTService(ES_Event ThisEvent)
{
    ES_Event ReturnEvent;
    ReturnEvent.EventType = ES_NO_EVENT; // assume no errors

    /********************************************
     in here you write your service code
     *******************************************/
    
    ES_Event StateEvent;
    
    switch(ThisEvent.EventType)
    {
        case ES_INIT:
        {
            break;
        }
        /*
         * Simply takes the 2k event and passes it to the HSM
         */
        case ES_TIMEOUT:    // called every ~30ms
        {
            if(IsReceiveEmpty() == FALSE)
            {
                TIMERS_InitTimer(3, 10);    // 10 ms timer
                while(TIMERS_IsTimerActive(3))
                {
                    packetReturn = BuildRxPacket(getchar(), &rxPacket_UART, 0);
                    if(packetReturn == 1)   // ERROR in packet
                        BuildRxPacket(0, &rxPacket_UART, 1);
                    else if(packetReturn == 2)   // packet complete
                    {
                        Left_ToF = (uint16_t)rxPacket_UART.payload[1] << 8  + (uint16_t)rxPacket_UART.payload[2];
                        Right_ToF = (uint16_t)rxPacket_UART.payload[3] << 8 + (uint16_t)rxPacket_UART.payload[4];
                        Rear_ToF = (uint16_t)rxPacket_UART.payload[5] << 8  + (uint16_t)rxPacket_UART.payload[6];   
                        HSM_UpdateTOF(BOAT_ReadTOF(Left_ToF), BOAT_ReadTOF(Right_ToF), BOAT_ReadTOF(Rear_ToF));
                    } 
                }
            }
            else
            {
                BuildRxPacket(0, &rxPacket_UART, 1);
            }
            //PostHSM(ThisEvent);
            break;
        }
        default:
            break;
    }
    return ReturnEvent;
}

/*******************************************************************************
 * PRIVATE FUNCTIONs                                                           *
 ******************************************************************************/
