/*
 * File:   BOAT_PinDefs.h
 * Author: Nicholas Kuipers
 *
 * Created on May 17, 2023 at 5:43PM
 *
 * Abstract: Input/Output pin definitions for use with BOAT parent library
 */

#ifndef BOAT_PINDEFS_H
#define BOAT__PINDEFS_H

#include <BOARD.h>
#include <xc.h>

#include <RC_Servo.h>
#include <pwm.h>

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/

/* ADMINISTRATIVE PINS */
// Low Voltage LED -- triggers via interrupt in AD.c when voltage drops below threshold
#define ALERT_LED_TRIS            TRISEbits.TRISE2        // PORT Z07
#define ALERT_LED                 LATEbits.LATE2    

// Connected to ON Switch, necessary to move state machine from (or to) STANDBY state
#define ON_SWITCH_TRIS            TRISBbits.TRISB5        // PORT V6
#define ON_SWITCH                 LATBbits.LATB5    

// ESP receives a reset event whenever the PIC is reset or set back to STANDBY (ESP32 Reset is ACTIVE LOW)
#define ESP_RESET_TRIS            TRISDbits.TRISD8        // PORT Z8
#define ESP_RESET                 LATDbits.LATD8        // ACTIVE LOW

// Notifies the ESP32 to begin its launcher protocol
#define FLYWHEEL_ON_TRIS          TRISBbits.TRISB13      // PORT Z9
#define FLYWHEEL_ON               LATBbits.LATB13      

/* MOTOR PINS */
// PWM Pin definitions
#define WHEEL_FRONT_LEFT_PWM    PWM_PORTY10
#define WHEEL_FRONT_RIGHT_PWM   PWM_PORTY12
#define WHEEL_REAR_LEFT_PWM     PWM_PORTX11
#define WHEEL_REAR_RIGHT_PWM    PWM_PORTZ06 

// Motor Direction Pin Initializations
#define WHEEL_FRONT_LEFT_DIR_TRIS        TRISDbits.TRISD6     // PORT X12     // INVERT WITH INV
#define WHEEL_FRONT_LEFT_DIR_INV_TRIS    TRISDbits.TRISD11    // PORT Y03     // INVERT WITH MAIN
#define WHEEL_FRONT_RIGHT_DIR_TRIS       TRISEbits.TRISE5     // PORT Y11     // INVERT WITH INV
#define WHEEL_FRONT_RIGHT_DIR_INV_TRIS   TRISEbits.TRISE6     // PORT Y09     // INVERT WITH MAIN
#define WHEEL_REAR_LEFT_DIR_TRIS         TRISDbits.TRISD10    // PORT Y06
#define WHEEL_REAR_LEFT_DIR_INV_TRIS     TRISEbits.TRISE7     // PORT Y07
#define WHEEL_REAR_RIGHT_DIR_TRIS        TRISEbits.TRISE4     // PORT Z03
#define WHEEL_REAR_RIGHT_DIR_INV_TRIS    TRISFbits.TRISF1     // PORT Z04

// Motor Direction Pin Definitions
#define WHEEL_FRONT_LEFT_DIR             LATDbits.LATD6    // PORT X12
#define WHEEL_FRONT_LEFT_DIR_INV         LATDbits.LATD11   // PORT Y03
#define WHEEL_FRONT_RIGHT_DIR            LATEbits.LATE5    // PORT Y11
#define WHEEL_FRONT_RIGHT_DIR_INV        LATEbits.LATE6    // PORT Y09
#define WHEEL_REAR_LEFT_DIR              LATDbits.LATD10   // PORT Y06
#define WHEEL_REAR_LEFT_DIR_INV          LATEbits.LATE7    // PORT Y07
#define WHEEL_REAR_RIGHT_DIR             LATEbits.LATE4    // PORT Z03
#define WHEEL_REAR_RIGHT_DIR_INV         LATFbits.LATF1    // PORT Z04

/* SENSOR PINS */
// Motor Encoder Pin Initializations
#define ENCODER_FRONT_LEFT_TRIS          TRISBbits.TRISB13          // PORT W5
#define ENCODER_FRONT_RIGHT_TRIS         TRISBbits.TRISB12          // PORT W6
#define ENCODER_REAR_LEFT_TRIS           TRISBbits.TRISB15          // PORT W7
#define ENCODER_REAR_RIGHT_TRIS          TRISBbits.TRISB14          // PORT W8

// Motor Encoder Pin Definitions
#define ENCODER_FRONT_LEFT               PORTBbits.RB13    // PORT W5
#define ENCODER_FRONT_RIGHT              PORTBbits.RB12    // PORT W6
#define ENCODER_REAR_LEFT                PORTBbits.RB15    // PORT W7
#define ENCODER_REAR_RIGHT               PORTBbits.RB14    // PORT W8

// Beacon Detector Pin Initializations/Definitions
#define BEACON_DETECTOR_2K_TRIS          TRISBbits.RB9     // PORT V8
#define BEACON_DETECTOR_2K               PORTBbits.RB9    
#define BEACON_DETECTOR_1_5K_TRIS        TRISBbits.RB11    // PORT W3
#define BEACON_DETECTOR_1_5K             PORTBbits.RB11

// Track Wire Sensor Pin Initialization/Definition
#define TRACK_WIRE_TRIS                  TRISBbits.TRISB10 // PORT W4
#define TRACK_WIRE                       PORTBbits.RB10 

// Tape Sensor Pin Initializations  (Input pins for sensors are powered directly from 3.3V (?))
#define TAPE_FRONT_CENTER_TRIS           TRISFbits.TRISF5           // PORT X3
#define TAPE_FRONT_LEFT_TRIS             TRISBbits.TRISB0           // PORT X4
#define TAPE_FRONT_RIGHT_TRIS            TRISGbits.TRISG6           // PORT X5
#define TAPE_REAR_CENTER_TRIS            TRISFbits.TRISF4           // PORT X6

// Tape Sensor Pin Definitions - Port to read data from
#define TAPE_FRONT_CENTER                PORTFbits.RF5     // PORT X3
#define TAPE_FRONT_LEFT                  PORTBbits.RB0     // PORT X4
#define TAPE_FRONT_RIGHT                 PORTGbits.RG6     // PORT X5
#define TAPE_REAR_CENTER                 PORTFbits.RF4     // PORT X6

// Bumper Pin Initializations
#define BUMPER_FRONT_LEFT_TRIS           TRISDbits.TRISD5    // PORT Y5
#define BUMPER_FRONT_RIGHT_TRIS          TRISDbits.TRISD9    // PORT Y8
#define BUMPER_REAR_LEFT_TRIS            TRISEbits.TRISE3    // PORT Z5
#define BUMPER_REAR_RIGHT_TRIS           TRISEbits.TRISE0    // PORT Z11

// Bumper Pin Definitions
#define BUMPER_FRONT_LEFT                PORTDbits.RD5     // PORT Y5
#define BUMPER_FRONT_RIGHT               PORTDbits.RD9     // PORT Y8
#define BUMPER_REAR_LEFT                 PORTEbits.RE3     // PORT Z5
#define BUMPER_REAR_RIGHT                PORTEbits.RE0     // PORT Z11

// Time of Flight Sensor Definitions/Initializations
#define TOF_LEFT                      TRISBbits.RB2        // PORT V3
#define TOF_RIGHT                     TRISBbits.RB3        // PORT V4
#define TOF_REAR                      TRISBbits.RB4        // PORT V5

// Stepper Motor Definitions/Initializations
// used in Stepper.h/.c
#define TRIS_COIL_A_ENABLE            TRISFbits.TRISF1     	//PORTZ_04
#define TRIS_COIL_A_DIRECTION         TRISEbits.TRISE4  	//PORTZ_03
#define TRIS_COIL_A_DIRECTION_INV     TRISEbits.TRISE3	    //PORTZ_05
#define TRIS_COIL_B_ENABLE            TRISDbits.TRISD8     	//PORTZ_08
#define TRIS_COIL_B_DIRECTION         TRISEbits.TRISE2  	//PORTZ_07
#define TRIS_COIL_B_DIRECTION_INV     TRISEbits.TRISE1      //PORTZ_09

#define COIL_A_ENABLE                 LATFbits.LATF1
#define COIL_A_DIRECTION              LATEbits.LATE4
#define COIL_A_DIRECTION_INV          LATEbits.LATE3
#define COIL_B_ENABLE                 LATDbits.LATD8
#define COIL_B_DIRECTION              LATEbits.LATE2
#define COIL_B_DIRECTION_INV          LATEbits.LATE1

// Ditching the comms protocol, opting for analog pin connections instead - NK, 05312023
/* Communication Pins */

/*
// UART2 Pins
#define UART2_RX_TRIS         TRISFbits.TRISF4         // PORT X6
#define UART2_TX_TRIS         TRISFbits.TRISF5         // PORT X3
#define UART2_RTS_TRIS        TRISBbits.TRISB14        // PORT W8
#define UART2_CTS_TRIS        TRISBbits.TRISB8         // PORT V7      


// SPI Pins (Communication with ESP32) (LIBRARY NEEDED)
#define SPI_CLK          TRISGbits.TRISG6        // SPI2 Clock Select
#define SPI_MISO         TRISGbits.TRISG7        // SPI2 UNO input
#define SPI_MOSI         TRISGbits.TRISG8        // SPI2 UNO output
#define SPI_CS           NULL
*/


#endif    /* BOAT_H */
