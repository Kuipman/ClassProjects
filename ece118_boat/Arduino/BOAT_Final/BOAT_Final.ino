#include <ESP32Servo.h>
#include <Stepper.h>
#include <Arduino.h>
#include <esp32-hal-i2c.h>
#include <Wire.h>
#include <VL53L1X.h>

// Pin Definitions
#define XSHUT_PIN_1     D2    // TOF
#define XSHUT_PIN_2     D3    // TOF
#define XSHUT_PIN_3     D4    // TOF
#define LAUNCHER_ON     D5
#define ESC_PWM         D7
#define STEPP_1         D8
#define STEPP_2         D9
#define STEPP_3         D10
#define STEPP_4         D11
#define TOF_LEFT        A0
#define TOF_RIGHT       A1
#define TOF_REAR        A2

// Constants
const int stepsPerRevolution = 200;  // Stepper Motor Variable
const uint8_t sensorCount = 3;       // ToF sensors in system
const uint8_t xshutPins[sensorCount] = { XSHUT_PIN_1, XSHUT_PIN_2, XSHUT_PIN_3 };  // ToF Multiplexing

// Global Variables
uint16_t lastRangeValues[sensorCount];
int launcherStartTime;
int launcherEndTime;
bool stateTransition;

// Typedefs
typedef enum{
  RANGING,
  LAUNCHER_MODE
}ESP_State;

ESP_State state;

// Objects
Servo flywheel;
Stepper myStepper(stepsPerRevolution, STEPP_1, STEPP_2, STEPP_3, STEPP_4);   // Stepper Motor
VL53L1X sensors[sensorCount];             // ToF Sensors

void setup()
{
  Serial.begin(115200);
  // Set up I2C for the ToF Sensors
  Wire.begin();
  Wire.setClock(400000); // use 400 kHz I2C

  /************* Variable Setup **********************/
  state = RANGING;
  pinMode(LAUNCHER_ON, INPUT);
  pinMode(TOF_LEFT,  OUTPUT);
  pinMode(TOF_RIGHT, OUTPUT);
  pinMode(TOF_REAR,  OUTPUT);
  launcherStartTime = 0;
  launcherEndTime   = 0;
  stateTransition = false;

  /************* ToF Sensor Setup **********************/
  // Disable/reset all sensors by driving their XSHUT pins low.
  /*
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

    Serial.println("In Setup()");
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
    /*
    sensors[i].setDistanceMode(VL53L1X::Long);
    sensors[i].setMeasurementTimingBudget(200000);
    sensors[i].startContinuous(200);
  }
*/

  /************* Stepper Motor Setup **********************/
  myStepper.setSpeed(90);
  Serial.println("Stepper Ready");

  /************* ESC/Flywheel Setup **********************/
  flywheel.attach(ESC_PWM);
  flywheel.writeMicroseconds(1500); // send "stop" signal to ESC. Also necessary to arm the ESC.
  delay(7000);                      // delay to allow the ESC to recognize the stopped signal.
  Serial.println("ESC Ready");
}

/*
Loop runs on a boolean state machine (two states). Does the following:
    - RANGING:
        - Standard state. ESP32 reads the current values of the ToF sensors and outputs their values (up to 1023mm)
            from respective analog pins. A logic converter is utilized to pass information between the ESP32 and UNO.
        - UNO remains in this state until it receives a HIGH value on its LAUNCHER_ON pin from the UNO. 
    - LAUNCHER_ON:
        - Transitioned to this state when LAUNCHER_ON pin receives a HIGH value. Remains in this state until
            timer expiry (~10 seconds)
*/
void loop()
{
  Serial.println("In Loop");
  switch(state)
  {
    case RANGING:
    {
      /*
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
      analogWrite(TOF_LEFT,  lastRangeValues[0]);
      analogWrite(TOF_RIGHT, lastRangeValues[1]);
      analogWrite(TOF_REAR,  lastRangeValues[2]);
      */
	  
	  // Packet write
	  Serial.write(0xCC);   // HEAD
	  Serial.write(0x7);    // Len
	  Serial.write(0x1);    // Message ID = ToF
	  
	  //Serial.write(lastRangeValues, 6);       // TOF Readings

    // Test
    for(int i = 0; i < 6; i++)
    {
      char value = 100 + i;
      Serial.write(value);
    }
	  
	  //Serial.write(0xB9);     // TAIL
	  

      // DEBUG
      Serial.println("In RANGING");


      // Check if the LAUNCHER_ON pin has a high value, indicating the UNO wants to move to LAUNCHER_MODE
      Serial.print("LAUNCHER_ON = ");
      Serial.println(digitalRead(LAUNCHER_ON));
      if(digitalRead(LAUNCHER_ON) == HIGH)
      {
        state = LAUNCHER_MODE;
        launcherStartTime = millis();    // records start time of transition to launcher mode
        stateTransition = true;
      }
      break;
    }
    case LAUNCHER_MODE:
    {
      Serial.println("Entering LAUNCHER_MODE");
      launcherEndTime = millis();
      if((launcherEndTime - launcherStartTime) > 10000)     // ten seconds have passed
      {
        // Turn off flywheel
        flywheel.write(0);
        state = RANGING;
        break;
      }
      if(stateTransition == true)
      {
        stateTransition = false;

        // Get the flywheel spinning
        Serial.println("Flywheel reset");
        flywheel.write(0);
        delay(2000);
        Serial.println("Flywheel running");
        flywheel.write(10);      // standard speed for 1pt line
        delay(500);
        Serial.println("Stepper Turning");
        myStepper.step(stepsPerRevolution);
      }
      Serial.println("Stepper Turning");
      myStepper.step(stepsPerRevolution);

      break;
    }
  }


/*
  //while (Serial.available()==0){}
  //pinVal = Serial.parseInt();
  Serial.println("Speed = 0");
  flywheel.write(0);
  delay(2000);
  Serial.println("Speed = 20 to 40");
  flywheel.write(10);
  //delay(500);
  //esc.write(10);
  delay(500);
  //esc.write(20);
  //delay(500);
  for(int i = 0; i < 20; i++)    // when i = 5, degrees = ~175
  {
    Serial.println("clockwise");
    myStepper.step(stepsPerRevolution);
  }
  //myStepper.step(50);
  //delay(10000);
  /*
  Serial.println("Speed = 20");
  esc.write(20);
  delay(1000);
  Serial.println("Speed = 30");
  esc.write(30);
  delay(1000);
  Serial.println("Speed = 40");
  esc.write(40);
  delay(1000);
  Serial.println("Speed = 50");
  esc.write(50);
  delay(1000);
  Serial.println("Speed = 60");
  esc.write(60);
  delay(1000);
  Serial.println("Speed = 70");
  esc.write(70);
  delay(1000);
  Serial.println("Speed = 80");
  esc.write(80);
  delay(1000);
  Serial.println("Speed = 90");
  esc.write(90);
  delay(1000);
  Serial.println("Speed = 100");
  esc.write(100);
  delay(2000);
  //Serial.println(analogRead(POTENTIOMETER_PIN));
  //int escVal = 10;
  //esc.write(escVal);
  //Serial.print("ESC Val: ");
  //Serial.println(escVal);
  //if(escVal < 150)
  //  {escVal = escVal + 20;}
  //for(int i = 0; i < 30000; i++) {}
  */

}
