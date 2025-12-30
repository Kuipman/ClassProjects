/*
This example shows how to set up and read multiple VL53L1X sensors connected to
the same I2C bus. Each sensor needs to have its XSHUT pin connected to a
different Arduino pin, and you should change sensorCount and the xshutPins array
below to match your setup.

For more information, see ST's application note AN4846 ("Using multiple VL53L0X
in a single design"). The principles described there apply to the VL53L1X as
well.
*/

// Edited for use with BOAT program
// @author Nicholas Kuipers 20230525

#include <Arduino.h>
//#include <esp32-hal-i2c.h>
#include <Wire.h>
#include <VL53L1X.h>

/**********************************/
/*     Public Variables / Defines */
/**********************************/

#define XSHUT_PIN_1     4
#define XSHUT_PIN_2     5
#define XSHUT_PIN_3     6

// The number of sensors in your system.
const uint8_t sensorCount = 3;

// The Arduino pin connected to the XSHUT pin of each sensor.
const uint8_t xshutPins[sensorCount] = { XSHUT_PIN_1, XSHUT_PIN_2, XSHUT_PIN_3 };
VL53L1X sensors[sensorCount];
uint16_t lastRangeValues[sensorCount];

void setup()
{
  while (!Serial) {}
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000); // use 400 kHz I2C

  //Serial.println("First init passed!");

  // Disable/reset all sensors by driving their XSHUT pins low.
  for (uint8_t i = 0; i < sensorCount; i++)
  {
    pinMode(xshutPins[i], OUTPUT);
    digitalWrite(xshutPins[i], LOW);
  }

  // Enable, initialize, and start each sensor, one by one.
  for (uint8_t i = 0; i < sensorCount; i++)
  {
    // Stop driving this sensor's XSHUT low. This should allow the carrier
    // board to pull it high. (We do NOT want to drive XSHUT high since it is
    // not level shifted.) Then wait a bit for the sensor to start up.
    pinMode(xshutPins[i], INPUT);
    delay(10);

    sensors[i].setTimeout(500);
    if (!sensors[i].init())
    {
      Serial.print("Failed to detect and initialize sensor ");
      Serial.println(i);
      while (1);
    }

    // Each sensor must have its address changed to a unique value other than
    // the default of 0x29 (except for the last one, which could be left at
    // the default). To make it simple, we'll just count up from 0x2A.
    sensors[i].setAddress(0x2A + i);

    /*
    * We want to be in long-distance ranging mode to get the most out of our sensors.
    *   To allow for the system to best operate, the timing budget and continuous ranging
    *   are set to operate at 200ms (5Hz), sufficiently slow enough to allow for sufficient
    *   photon collection.
    */
    sensors[i].setDistanceMode(VL53L1X::Long);
    sensors[i].setMeasurementTimingBudget(200000);
    sensors[i].startContinuous(200);
  }
}

void loop()
{
  // ToF addresses: 2A02 , 2B02 , 2C02
  for (uint8_t i = 0; i < sensorCount; i++)
  {
    int TOF_Address = sensors[i].readReg16Bit(0x0001);
    Serial.print("ToF Sensor Address ");   
    Serial.print(TOF_Address); // I2C Slave Address
    Serial.print(": ");
    lastRangeValues[i] = sensors[i].read();
    Serial.print(lastRangeValues[i]);
    if (sensors[i].timeoutOccurred()) { Serial.print(" TIMEOUT"); }
    Serial.print('\t');
  }
  Serial.println();
}
