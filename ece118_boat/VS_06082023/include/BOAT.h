/*
 * File:   BOAT.h
 * Author: Nicholas Kuipers
 *
 * Created on May 13, 2023 at 5:15PM
 * Last Modified May 13, 2023 at 5:15PM
 *
 * Abstract: Parent library for BOAT system. Incorporates Movement, Launcher,
 *      and UART libraries.
 *
 */

#ifndef BOAT_H
#define BOAT_H

#include <BOARD.h>

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/

// Activate only one at a time, or none at all for final implementation
#define TESTBENCH_LAUNCHER     0
#define TESTBENCH_MOVEMENT     0
#define TESTBENCH_SENSORS      0
#define TESTBENCH_POC          1

#define TESTBENCH_ES           0

#define FINAL_RUN              0

/*******************************************************************************
 * PUBLIC TYPEDEFS                                                             *
 ******************************************************************************/

/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/**
 * @Function BOAT_Init(void)
 * @param None.
 * @return None.
 * @brief Performs all necessary initializations for the BOAT, including:
 *      - initializing PWM for motors, analog and digital pins for I/O
 *      - initializing the motors, setting initial directions
 *      - initializing UART for communication with ESP32
 *      - 
 * @author Nicholas Kuipers, 20230513
 */
void BOAT_Init(void);


/**
 * @Function Roach_LightLevel(void)
 * @param None.
 * @return a 10-bit value corresponding to the amount of light received.
 * @brief  Returns the current light level. A higher value means less light is detected.
 * @author Max Dunne, 2012.01.06 */
//unsigned int Roach_LightLevel(void);

/**
 * @Function Roach_BatteryVoltage(void)
 * @param None.
 * @return a 10-bit value corresponding to the current voltage of the roach
 * @brief  returns a 10:1 scaled value of the roach battery level
 * @author Max Dunne, 2013.07.12 */
//unsigned int Roach_BatteryVoltage(void);

/**
 * @Function Roach_ReadFrontLeftBumper(void)
 * @param None.
 * @return BUMPER_TRIPPED or BUMPER_NOT_TRIPPED
 * @brief  Returns the state of the front left bumper
 * @author Max Dunne, 2012.01.06 */
//unsigned char Roach_ReadFrontLeftBumper(void);


/**
 * @Function Roach_ReadFrontRightBumper(void)
 * @param None.
 * @return BUMPER_TRIPPED or BUMPER_NOT_TRIPPED
 * @brief  Returns the state of the front right bumper
 * @author Max Dunne, 2012.01.06 */
//unsigned char Roach_ReadFrontRightBumper(void);

/**
 * @Function Roach_ReadRearLeftBumper(void)
 * @param None.
 * @return BUMPER_TRIPPED or BUMPER_NOT_TRIPPED
 * @brief  Returns the state of the rear left bumper
 * @author Max Dunne, 2012.01.06 */
//unsigned char Roach_ReadRearLeftBumper(void);

/**
 * @Function Roach_ReadRearRightBumper(void)
 * @param None.
 * @return BUMPER_TRIPPED or BUMPER_NOT_TRIPPED
 * @brief  Returns the state of the rear right bumper
 * @author Max Dunne, 2012.01.06 */
//unsigned char Roach_ReadRearRightBumper(void);

/**
 * @Function Roach_ReadBumpers(void)
 * @param None.
 * @return 4-bit value representing all four bumpers in following order: front left,front right, rear left, rear right
 * @brief  Returns the state of all 4 bumpers
 * @author Max Dunne, 2012.01.06 */
//unsigned char Roach_ReadBumpers(void);



/**
 * @Function Roach_LEDSSet( unsigned char pattern)
 * @param pattern - sets LEDs on (1) or off (0) as in the pattern.
 * @return SUCCESS or ERROR
 * @brief  Forces the LEDs in (bank) to on (1) or off (0) to match the pattern.
 * @author Gabriel Hugh Elkaim, 2011.12.25 01:16 Max Dunne 2015.09.18 */
//char Roach_LEDSSet(uint16_t pattern);

/**
 * @Function Roach_LEDSGet(void)
 * @return uint16_t: ERROR or state of BANK
 * @author Max Dunne, 203.10.21 01:16 2015.09.18 */
//uint16_t Roach_LEDSGet(void);

/**
 * @Function Roach_BarGraph(uint8_t Number)
 * @param Number - value to light between 0 and 12 leds
 * @return SUCCESS or ERROR
 * @brief  allows all leds to be used as a bar graph
 * @author  Max Dunne 2015.09.18 */
//char Roach_BarGraph(uint8_t Number);


#endif    /* BOAT_H */
