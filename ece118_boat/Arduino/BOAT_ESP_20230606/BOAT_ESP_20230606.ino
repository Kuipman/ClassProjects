/* Basic Multi Threading Arduino Example
   This example code is in the Public Domain (or CC0 licensed, at your option.)
   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
// Please read file README.md in the folder containing this example./*

/**
* File: BOAT_ESP
* Author: Nicholas Kuipers 
*
* Brief: FreeRTOS-based system for integration with the BOAT mechatronics project. Performs 
*   the following as tasks:
*     - ReadFromSerial: checks the UART RX register for information ready to be processed. If there is data
*         present, reads in the data as a string and parses it for packet information from the UNO. If the packet
*         parsing is successful, calls the OperatePacket() function
*     - ReadSensors:  checks the 100ms timer (started at end of setup()). If expired, checks each I2C connection of the ToF
*       sensors and builds an update packet. Packet is queued for the next repetition of WriteToSerial
*     - WriteToSerial: checks the queue for a string ready to be written to serial. If one is present in the queue, builds a packet based around this
*          string (it will always be an UPDATE_ID)
*
*/

// Libraries
#include <Arduino.h>
#include <esp32-hal-i2c.h>
#include <Wire.h>
#include <VL53L1X.h>
#include <ESP32Servo.h>
#include <Stepper.h>

// FreeRTOS Declarations
#define MAX_LINE_LENGTH (64)

// Pin Declarations
#define XSHUT_PIN_1     D2    // TOF
#define XSHUT_PIN_2     D3    // TOF
#define XSHUT_PIN_3     D4    // TOF
#define FLYWHEEL_ON     D5
#define TURN_STEPPER    D6
#define PWM_PIN         D7   // SS on the board
// Stepper D8 D9 D10 D11
#define TOF_LEFT        A1
#define TOF_RIGHT       A2
#define TOF_REAR        A3


// ToF Declarations
const uint8_t sensorCount = 3;        // for the ToF Sensors
const uint8_t xshutPins[sensorCount] = { XSHUT_PIN_1, XSHUT_PIN_2, XSHUT_PIN_3 };
VL53L1X sensors[sensorCount];
uint16_t lastRangeValues[sensorCount];

// Launcher Declarations
//ESP32PWM pwm;
Servo esc;
int Fly_Speed;
const int stepsPerRevolution = 200;    // Stepper motor
Stepper myStepper(stepsPerRevolution, D8, D9, D10, D11);
//const int minUs = 1000;
//const int maxUs = 2000;

// Task Definitions
void TaskWriteToSerial(void *pvParameters);
void TaskReadFromSerial(void *pvParameters);
//void TaskReadSensors(void *pvParameters);
void TaskRunLauncher(void *pvParameters);

// Define Queue handle
QueueHandle_t QueueHandle;
const int QueueElementSize = 10;
typedef struct{
  char line[MAX_LINE_LENGTH];
  uint8_t line_length;
} message_t;

// The setup function runs once when you press reset or power on the board.
void setup() {
  // Initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
  while(!Serial){delay(10);}
  Wire.begin();            // ToF I2C
  Wire.setClock(400000);   // use 400 kHz I2C

  /****************************************************** TOF Setup ***************************************************/
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

    Serial.println("In Setup()");
    sensors[i].setTimeout(500);
    if (!sensors[i].init())
    {
      Serial.print("Failed to detect and initialize sensor ");
      Serial.println(i);
      //while (1);
    }

    // Each sensor must have its address changed to a unique value other than
    // the default of 0x29 (except for the last one, which could be left at
    // the default). To make it simple, we'll just count up from 0x2A.

    //sensors[i].setAddress(0x2A + i);

    /*
    * We want to be in long-distance ranging mode to get the most out of our sensors.
    *   To allow for the system to best operate, the timing budget and continuous ranging
    *   are set to operate at 200ms (5Hz), sufficiently slow enough to allow for sufficient
    *   photon collection.
    */

    //sensors[i].setDistanceMode(VL53L1X::Long);
    //sensors[i].setMeasurementTimingBudget(200000);
    //sensors[i].startContinuous(200);
  }

  /****************************************************** Launcher Setup ***************************************************/
  esc.attach(PWM_PIN);    // Pin 9 = PWM signal
  esc.writeMicroseconds(1500); // send "stop" signal to ESC. Also necessary to arm the ESC.
  Fly_Speed = 50;
  myStepper.setSpeed(60);

  /****************************************************** Serial Setup ************************************************************/
  // Create the queue which will have <QueueElementSize> number of elements, each of size `message_t` and pass the address to <QueueHandle>.
  Serial.println("Serial Setup Reached");
  QueueHandle = xQueueCreate(QueueElementSize, sizeof(message_t));

  // Check if the queue was successfully created
  if(QueueHandle == NULL){
    Serial.println("Queue could not be created. Halt.");
    while(1) delay(1000); // Halt at this point as is not possible to continue
  }

  // Tasks run independently, organized by priority
  xTaskCreate(
    TaskReadFromSerial
    ,  "Task Read From Serial"
    ,  2048  // Stack size
    ,  NULL  // No parameter is used
    ,  1  // Priority
    ,  NULL // Task handle is not used here
    );

  xTaskCreate(
    TaskWriteToSerial
    ,  "Task Write To Serial" // A name just for humans
    ,  2048        // The stack size can be checked by calling `uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);`
    ,  NULL        // No parameter is used
    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL // Task handle is not used here
    );
  /*
  xTaskCreate(
     TaskReadSensors
     , "Task Read Sensors"
     , 4096
     , NULL
     , 3      // priority
     , NULL
  );
  */

  xTaskCreate(
    TaskRunLauncher
    , "Task Run Launcher"
    , 2048
    , NULL
    , 3       // priority
    , NULL
  );

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
  Serial.printf("\nAnything you write will return as echo.\nMaximum line length is %d characters (+ terminating '0').\nAnything longer will be sent as a separate line.\n\n", MAX_LINE_LENGTH-1);
}

void loop(){
  // Loop's primary function is to check and update the current ToF sensor values
  Serial.println("Loop Task Reached");
  /************ ToF Loop ***********************/
  // ToF addresses: 2A02 , 2B02 , 2C02
  /*
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
  analogWrite(TOF_LEFT,  lastRangeValues[0]);
  analogWrite(TOF_RIGHT, lastRangeValues[1]);
  analogWrite(TOF_REAR,  lastRangeValues[2]);
  */
  /************ End of ToF Loop ***********************/
  delay(1000); // While not being used yield the CPU to other tasks
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void TaskReadFromSerial(void *pvParameters){  // This is a task.
  message_t message;
  Serial.println("Read from Serial reached");
  for (;;){
    // Check if any data are waiting in the Serial buffer
    message.line_length = Serial.available();
    if(message.line_length > 0){
      // Check if the queue exists AND if there is any free space in the queue
      if(QueueHandle != NULL && uxQueueSpacesAvailable(QueueHandle) > 0){
        int max_length = message.line_length < MAX_LINE_LENGTH ? message.line_length : MAX_LINE_LENGTH-1;
        for(int i = 0; i < max_length; ++i){
          message.line[i] = Serial.read();
        }
        message.line_length = max_length;
        message.line[message.line_length] = 0; // Add the terminating nul char

        // The line needs to be passed as pointer to void.
        // The last parameter states how many milliseconds should wait (keep trying to send) if is not possible to send right away.
        // When the wait parameter is 0 it will not wait and if the send is not possible the function will return errQUEUE_FULL
        int ret = xQueueSend(QueueHandle, (void*) &message, 0);
        if(ret == pdTRUE){
          // The message was successfully sent.
        }else if(ret == errQUEUE_FULL){
          // Since we are checking uxQueueSpacesAvailable this should not occur, however if more than one task should
          //   write into the same queue it can fill-up between the test and actual send attempt
          Serial.println("The `TaskReadFromSerial` was unable to send data into the Queue");
        } // Queue send check
      } // Queue sanity check
    }else{
      delay(100); // Allow other tasks to run when there is nothing to read
    } // Serial buffer check
  } // Infinite loop
}

void TaskWriteToSerial(void *pvParameters){  // This is a task.
  message_t message;
  Serial.println("Write to Serial reached");
  for (;;){ // A Task shall never return or exit.
    // One approach would be to poll the function (uxQueueMessagesWaiting(QueueHandle) and call delay if nothing is waiting.
    // The other approach is to use infinite time to wait defined by constant `portMAX_DELAY`:
    if(QueueHandle != NULL){ // Sanity check just to make sure the queue actually exists
      int ret = xQueueReceive(QueueHandle, &message, portMAX_DELAY);
      if(ret == pdPASS){
        // The message was successfully received - send it back to Serial port and "Echo: "
        Serial.printf("Echo line of size %d: \"%s\"\n", message.line_length, message.line);
        //Serial.write(0x55);     // test byte
        // The item is queued by copy, not by reference, so lets free the buffer after use.
      }else if(ret == pdFALSE){
        //Protocol_WriteErrorMessage(&message);
        //Serial.write(message);
        Serial.println("The `TaskWriteToSerial` was unable to receive data from the Queue");
      }
    } // Sanity check
  } // Infinite loop
}

/*
void TaskReadSensors(void *pvParameters){
  bool readFlag = false;
  while(1)    //forever loop
  {
    if(readFlag == false)    // triggers true at end of this loop so the read only occurs once
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
      readFlag = true;
    }
  }
  
  //Serial.println("Read Sensors Test");
  //vTaskDelay(1000/ portTICK_RATE_MS);     // Delay by 1 second
}
*/

void TaskRunLauncher(void *pvParameters){
  Serial.println("Run Launcher Task Reached");
  while(1)
  {
    if(digitalRead(FLYWHEEL_ON) == HIGH)
    { 
      esc.write(Fly_Speed);
      Fly_Speed = Fly_Speed + 50;
      // IMPLEMENT COUNTER
      //myStepper.step(stepsPerRevolution);
      //delay(500);
      //myStepper.step(-stepsPerRevolution);   // 
    }
    else
    {
      esc.write(0);
      Fly_Speed = 50;
      delay(100);     // gives up rest of time allocated to task
    }
    vTaskDelay(200/ portTICK_RATE_MS);     // Delay by 200ms
  }
  
}
