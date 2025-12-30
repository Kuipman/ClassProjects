/**
 * File: EventChecker.h
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

#ifndef BUTTONEVENTCHECKER_H
#define	BUTTONEVENTCHECKER_H

/*******************************************************************************
 * PUBLIC #INCLUDES                                                            *
 ******************************************************************************/

#include "ES_Configure.h"   // defines ES_Event, INIT_EVENT, ENTRY_EVENT, and EXIT_EVENT
#include "BOARD.h"

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/

/*******************************************************************************
 * PUBLIC TYPEDEFS                                                             *
 ******************************************************************************/

/*
typedef enum{
    GRAY,
    DARK,
    LIGHT
}LIGHT_STATE;
*/

/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/**
 * @Function checkBumpers(void)
 * @param none
 * @return TRUE if bumper state change, FALSE otherwise
 * @brief Check for a change in bumper values. 
 *      - Static variable prevBumperValues tracks previous recorded value of bumpers
 *      - Static boolean flag bumperChange set to true if a bumper change is detected
 *      - If bumperChange is true:
 *          - Set the flag to false
 *          - 
 * 
 * @author Nicholas Kuipers 
 */
uint8_t checkBumpers(void);

/**
 * @Function checkTapeSensors(void)
 * @param none
 * @return TRUE if tape state changes, FALSE otherwise
 * 
 * @brief Checks the current values of the four tape sensors of the BOAT. These are
 *      digital inputs, so no hysteresis is necessary.
 *          - Works almost identically to the checkBumper function.
 * @author Nicholas Kuipers 
 */
uint8_t checkTapeSensors(void);

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
uint8_t checkTrackWire(void);

/**
 * @Function check2kBeacon(void)
 * @param none
 * @return TRUE if beacon changes, FALSE otherwise
 * 
 * @brief Checks the current value of the 2k beacon. This is an analog input, making hysteresis necessary.
 *      - Works nearly identically to checkTrackWire event
 * @author Nicholas Kuipers
 */
uint8_t check2kBeacon(void);

/**
 * @Function check1_5kBeacon(void)
 * @param none
 * @return TRUE if beacon changes, FALSE otherwise
 * 
 * @brief Checks the current value of the 1.5k beacon. Analog input, making hysteresis necessary.
 *      - Works nearly identically to checkTrackWire event
 * @author Nicholas Kuipers
 */
uint8_t check1_5kBeacon(void);

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
uint8_t updateTOF(void);

/**
 * @Function checkSwitch(void)
 * @param none
 * @return TRUE if switch toggled, FALSE otherwise
 * 
 * @brief Check the current value of the switch pin (PORTV6). If the switch value changes (use lastSwitchValue variable),
 *      post the event directly to the HSM.
 */
uint8_t checkSwitch(void);


#endif	/* BUTTONEVENTCHECKER_H */

