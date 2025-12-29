/**
 * File: EventChecker.h
 * Project: ECE 118 - Lab 0 Part 5
 * Authors: Josh Gamlen, Nick Kuipers
 * 
 * @brief Library of event checkers ran through by ES_Framework during a
 *      standard loop. For part 5, event checkers are:
 *      - Check of any bumper interaction -- which bumper does not matter
 *      - Check for any discrete change in light level
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

#define LIGHTTHRESHOLD 500
#define DARKTHRESHOLD  700

/*******************************************************************************
 * PUBLIC TYPEDEFS                                                             *
 ******************************************************************************/

typedef enum{
    GRAY,
    DARK,
    LIGHT
}LIGHT_STATE;

/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/**
 * @Function TemplateCheckBattery(void)
 * @param none
 * @return TRUE or FALSE
 * @brief This function is a prototype event checker that checks the battery voltage
 *        against a fixed threshold (#defined in the .c file). Note that you need to
 *        keep track of previous history, and that the actual battery voltage is checked
 *        only once at the beginning of the function. The function will post an event
 *        of either BATTERY_CONNECTED or BATTERY_DISCONNECTED if the power switch is turned
 *        on or off with the USB cord plugged into the Uno32. Returns TRUE if there was an 
 *        event, FALSE otherwise.
 * @note Use this code as a template for your other event checkers, and modify as necessary.
 * @author Gabriel H Elkaim, 2013.09.27 09:18
 * @modified Gabriel H Elkaim/Max Dunne, 2016.09.12 20:08 */
uint8_t TemplateCheckBattery(void);


/**
 * @Function checkBumpers(void)
 * @brief Check the current bumper values
 *      - Cross-reference these values with the previous bumper values (set a "change" flag if they're different)
 *      - Conversion - 4-bit value depicting the bits that changed (XOR)
 *      - If the flag is set to true
 *          - set flag false
 *          - post event
 *              - if/else that generate individual events depending on bits that are different (0110)
 *          - sets lastBumperValues = currentbumperValues
 *          - return TRUE
 *      - return FALSE
 * VERSION BELOW REMOVED FLAG AS CHANGE BEING HIGH WORKS FOR DETECTING CHANGE!!!
 * 
 * @param void
 * @return TRUE if bumper state change, FALSE otherwise
 */
uint8_t checkBumpers(void);

/**
 * @Function checkLight(void)
 * @brief Check the current light value, read by the light sensor on robot
 *      - Declare an enum (DARK, LIGHT) to record the previous light state (global variable).
 *          - Initialize as DARK
 *      - In the function:
 *          - Declare an enum (DARK, LIGHT) to record the CURRENT light state
 *          - Declare a 16-bit integer, set value to the current light level
 *          - Declare a boolean return value, set to FALSE
 *          - Check if the current light level is below the light threshold or above the dark
 *              threshold
 *              - If either case is true, set currentLightState to respective value
 *              - Check if the currentLightState IS NOT equal to previousLightState
 *                  - if these are not equal, set returnValue to TRUE. Update previousLightState
 *                  - if these are equal, do nothing
 *          - return the returnValue
 * 
 * @param void
 * @return TRUE if light state change, FALSE otherwise
 */
uint8_t checkLight(void);


#endif	/* BUTTONEVENTCHECKER_H */

