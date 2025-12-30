/* 
 * File:   MessageIDs.h
 * @author Nicholas Kuipers
 * @purpose Message ID list of packets used in BOAT project
 * @note Inspired from previous work in ECE 121
 */

#ifndef MESSAGEIDS_H
#define MESSAGEIDS_H

typedef enum {
    ID_ERROR = 0,           // Invalid packet, used as an error return 
    ID_DEBUG = 128,         // Treated as an array of chars that are displayed as a string on console
    ID_STANDBY,             // One byte payload, sent as command to distant microcontroller
    ID_STANDBY_AYE,         // One byte payload, received as response to STANDBY message
    ID_ENGAGE,              // One byte payload, sent as command (triggered by move to START state)
    ID_ENGAGE_AYE,           // One byte payload, response indicating microcontroller is reading its sensors
            
           
    // Below is to be removed once Protocol is debugged
    ID_LEDS_SET,
    ID_LEDS_GET,
    ID_PING,
    ID_PONG
}MessageIDS_t;

#endif	/* MESSAGEIDS_H */