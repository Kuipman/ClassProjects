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
    ID_HANDSHAKE,             // One byte payload, sent as command to distant microcontroller
    ID_HANDSHAKE_RES,         // One byte payload, received as response to HANDSHAKE message
    ID_UPDATE,              // Regular packet sent from ESP32
            
           
    // Below is to be removed once Protocol is debugged
    ID_LEDS_SET,
    ID_LEDS_GET,
    ID_PING,
    ID_PONG
}MessageIDS_t;

#endif	/* MESSAGEIDS_H */