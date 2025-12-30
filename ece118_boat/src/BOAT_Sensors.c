/*
 * File:   BOAT_Sensors.c
 * Author: Nicholas Kuipers
 *
 * Created on May 13, 2023 at 4:55PM
 *
 * Abstract: Driver code for tape, track wire, and LiDAR sensors
 */

#include <BOARD.h>
#include <BOAT.h>
#include <BOAT_Movement.h>
#include <BOAT_Launcher.h>
#include <BOAT_Sensors.h>
#include <BOAT_PinDefs.h>
#include <xc.h>

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <pwm.h>
#include <serial.h>
#include <AD.h>
#include <IO_Ports.h>

/*******************************************************************************
 * PRIVATE #DEFINES                                                             *
 ******************************************************************************/

/*******************************************************************************
 * PRIVATE VARIABLES                                                           *
 ******************************************************************************/

/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/*******************************************************************************
 * PUBLIC FUNCTION IMPLEMENTATIONS                                             *
 ******************************************************************************/

/**
 * @Function BOAT_InitSensors(void)
 * @param None.
 * @return None.
 * @brief Initializes the tape, track wire, and bumper sensors
 * @author Nicholas Kuipers, 20230513
 */
void BOAT_SensorsInit(void)
{
    AD_AddPins(AD_PORTV8 | AD_PORTW3 | AD_PORTW4);    // 2k beacon, 1.5 beacon, track wire
    AD_AddPins(AD_PORTV3 | AD_PORTV4 | AD_PORTV5);    // ToF Sensors
    AD_AddPins(AD_PORTV6);                             // Switch, used in EventChecker.c
    IO_PortsSetPortInputs(PORTX, PIN4 | PIN5 | PIN8 | PIN10);   // Tape Sensors
    IO_PortsSetPortInputs(PORTY, PIN5 | PIN8);                  // front bumpers
    IO_PortsSetPortInputs(PORTZ, PIN5 | PIN11);                 // back bumpers  
    
    printf("BOAT_SensorsInit() succeeded");
}

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
uint8_t BOAT_ReadTapeSensors(void)
{
    uint8_t resultValue = 0b0000;
    
    // Tape sensors are ACTIVE LOW
    if(~IO_PortsReadPort(PORTX) & PIN3)
        resultValue |= 0b0001; 
    if(~IO_PortsReadPort(PORTX) & PIN5)
        resultValue |= 0b0010;
    if(~IO_PortsReadPort(PORTX) & PIN4)
        resultValue |= 0b0100;
    if(~IO_PortsReadPort(PORTX) & PIN6)
        resultValue |= 0b1000;
    
    return resultValue;
}

/**
 * @Function BOAT_ReadTrackWireSensor(void)
 * @param none
 * @return 10-bit analog value from peak detector of Track Wire sensor
 * @brief Reads the associated pin with the track wire sensor and returns
 *      the PORTx value
 * @author Nicholas Kuipers, 20230513
*/
unsigned int BOAT_ReadTrackWireSensor(void)
{
    return AD_ReadADPin(AD_PORTW4);
}

/**
 * @Function BOAT_ReadAllBumpers(void)
 * @param none
 * @return 4-bit value depicting current bumper values
 * @brief Reads all bumpers and returns their "digital" values
 *      as a 4-bit integer
 *      - Bit orientation is as follows (from MSB to LSB):
 *          - Rear-Left, Rear-Right, Front-Left, Front-Right
 * @note Bumpers are very noisy and cause problems with digital ports.
 *      So, to compensate these are analog pins with a high threshold for
 *      returning a HIGH value
 * @author Nicholas Kuipers, 20230513
 */

uint8_t BOAT_ReadBumpers(void)
{
    uint8_t resultValue = 0b0000;
    
    if(IO_PortsReadPort(PORTY) & PIN5)
        resultValue |= 0b0001;
    if(IO_PortsReadPort(PORTY) & PIN8)
        resultValue |= 0b0010;
    if(IO_PortsReadPort(PORTZ) & PIN5)
        resultValue |= 0b0100;
    if(IO_PortsReadPort(PORTZ) & PIN11)
        resultValue |= 0b1000;
        
        return resultValue;
}

/**
 * @Function BOAT_ReadBeacon_2k(void)
 * @param None
 * @return 0 - 1023 (analog value) (10 bit)
 * @brief Reads the 2k Beacon Detector pin (analog), returns a 10-bit value
 * @author Nicholas Kuipers
 */
unsigned int BOAT_ReadBeacon_2k(void)
{
    return AD_ReadADPin(AD_PORTV8);
}

/**
 * @Function BOAT_ReadBeacon_1_5k(void)
 * @param None
 * @return 0 - 1023 (analog value) (10 bit)
 * @brief Reads the 1.5k Beacon Detector pin (analog), returns a 10-bit value
 * @author Nicholas Kuipers
 */
unsigned int BOAT_ReadBeacon_1_5k(void)
{
    return AD_ReadADPin(AD_PORTW3);
}

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
unsigned int BOAT_ReadTOF(TOF_Sensor sensor)
{
    switch(sensor)
    {
        case LEFT_TOF:
        {
            return AD_ReadADPin(AD_PORTV3);
            break;
        }
        case RIGHT_TOF:
        {
            return AD_ReadADPin(AD_PORTV4);
            break;
        }
        case REAR_TOF:
        {
            return AD_ReadADPin(AD_PORTV5);
            break;
        }
    }
}

/**
 *@Function BOAT_ReadSwitch(void)
 * @param None
 * @return 0 - 1023 (analog value) (10 bit)
 * @brief Reads the switch pin (analog), returns a 10-bit value
 * @author Me
 */
unsigned int BOAT_ReadSwitch(void)
{
    return AD_ReadADPin(AD_PORTV6);
}


#if TESTBENCH_SENSORS

int main()
{
    BOARD_Init();
    BOAT_Init();
    
    printf("\r\nSensor Test Bench Active");
    /*
     *  Loop checks each sensor using the standard functions and returns
     *  4-bit or single bit values respectively
     */
    while(1)
    {
        uint8_t currentBumperValues = BOAT_ReadBumpers();
        uint8_t currentTapeValues = BOAT_ReadTapeSensors();
        uint8_t currentTrackWireValue = BOAT_ReadTrackWireSensor();
        printf("\r\nCurrent Bumper Values: %i", currentBumperValues);
        printf("\r\nCurrent Tape Values: %i", currentTapeValues);
        printf("\r\nCurrent Track Wire Value: %i\r\n", currentTrackWireValue);
        for(int i = 0; i < 200000; i++){}   // delay for a brief moment
    }
}
#endif