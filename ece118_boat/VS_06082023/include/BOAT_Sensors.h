/*
 * File:   BOAT_Sensors.h
 * Author: Nicholas Kuipers
 *
 * Created on May 13, 2023 at 4:55PM
 *
 * Abstract: Driver code for tape, track wire, and LiDAR sensors
 */

#ifndef BOAT_SENSORS_H
#define BOAT_SENSORS_H

#include <BOARD.h>
#include <BOAT.h>
#include <stdint.h>

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/

#define DEBUG_SENSORS      1

// Calibration values
#define TRACKWIRE_START             200     // starting value of lastTrackWireValue
#define TRACKWIRE_HIGH_THRESHOLD    700
#define TRACKWIRE_LOW_THRESHOLD     400
#define BEACON_2K_START             200
#define BEACON_2K_HIGH_THRESHOLD    800
#define BEACON_2K_LOW_THRESHOLD     500
#define BEACON_1_5K_START           200
#define BEACON_1_5K_HIGH_THRESHOLD  700
#define BEACON_1_5K_LOW_THRESHOLD   400
#define SWITCH_START                200
#define SWITCH_HIGH_THRESHOLD       1000
#define SWITCH_LOW_THRESHOLD        400

/*******************************************************************************
 * PUBLIC TYPEDEFS                                                             *
 ******************************************************************************/

typedef enum{
    LEFT_TOF,
    RIGHT_TOF,
    REAR_TOF
}TOF_Sensor;

/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/**
 * @Function BOAT_InitSensors(void)
 * @param None.
 * @return None.
 * @brief Initializes the tape, track wire, and LiDAR sensors
 * @author Nicholas Kuipers, 20230513
 */
void BOAT_SensorsInit(void);

/**
 * @Function BOAT_ReadAllTapeSensors(void)
 * @param none
 * @return a 4-bit value, depicting values for all 4 tape sensors:
 *      - In order from MSB to LSB:
 *          - Rear-Center, Front-Left, Front-Right, Front-Center
 * @brief Reads all four tape sensor digital signals and returns a 4-bit
 *      value
 * @author Nicholas Kuipers, 20230513
*/
uint8_t BOAT_ReadTapeSensors(void);

/**
 * @Function BOAT_ReadTrackWireSensor(void)
 * @param none
 * @return 0(LOW) or 1(HIGH)
 * @brief Reads the associated pin with the track wire sensor and returns
 *      the PORTx value
 * @author Nicholas Kuipers, 20230513
*/
unsigned int BOAT_ReadTrackWireSensor(void);

/**
 * @Function BOAT_ReadAllBumpers(void)
 * @param none
 * @return 4-bit value depicting current bumper values
 * @brief Reads all bumpers and returns their digital values
 *      as a 4-bit integer
 *      - Bit orientation is as follows (from MSB to LSB):
 *          - Rear-Left, Rear-Right, Front-Left, Front-Right
 * @author Nicholas Kuipers, 20230513
 */
uint8_t BOAT_ReadBumpers(void);

/**
 * @Function BOAT_ReadBeacon_2k(void)
 * @param None
 * @return 0 - 1023 (analog value) (10 bit)
 * @brief Reads the 2k Beacon Detector pin (analog), returns a 10-bit value
 * @author Nicholas Kuipers
 */
unsigned int BOAT_ReadBeacon_2k(void);

/**
 * @Function BOAT_ReadBeacon_1_5k(void)
 * @param None
 * @return 0 - 1023 (analog value) (10 bit)
 * @brief Reads the 1.5k Beacon Detector pin (analog), returns a 10-bit value
 * @author Nicholas Kuipers
 */
unsigned int BOAT_ReadBeacon_1_5k(void);

/**
 * @Function BOAT_ReadTOF(TOF_Sensor sensor)
 * @param sensor, which sensor to read from
 * @return 0 - 1023 (analog value) -- mm sensor can see
 * 
 * @brief Reads the ToF sensor attached to the specific analog pin (via connection
 *      to the ESP32). mm value is limited to up to 1023 (just over a meter), which is
 *      adequate for the dimensions the BOAT will be operating in.
 * 
 * @author Nicholas Kuipers
 */
unsigned int BOAT_ReadTOF(TOF_Sensor sensor);

/**
 *@Function BOAT_ReadSwitch(void)
 * @param None
 * @return 0 - 1023 (analog value) (10 bit)
 * @brief Reads the switch pin (analog), returns a 10-bit value
 * @author Me
 */
unsigned int BOAT_ReadSwitch(void);

#endif    /* BOAT_SENSORS_H */
