
#include <Arduino.h>
//#include <esp32-hal-i2c.h>

#define LED 13
//#define IOPin_Test D1

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.print("Initializing...");
  pinMode(LED, OUTPUT);
  //pinMode(IOPin_Test, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED, HIGH);
  //digitalWrite(IOPin_Test, HIGH);
  Serial.println("LED is on");
  delay(1000);
  digitalWrite(LED, LOW);
  //digitalWrite(IOPin_Test, LOW);
  Serial.println("LED is off");
  delay(1000);
}
