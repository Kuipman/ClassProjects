#include <Servo.h>

Servo esc;

#define POTENTIOMETER_PIN A0

int pinVal;

void setup()
{
  Serial.begin(115200);
  pinVal = 0;
  esc.attach(9);    // Pin 9 = PWM signal
  esc.writeMicroseconds(1500); // send "stop" signal to ESC. Also necessary to arm the ESC.
  delay(7000); // delay to allow the ESC to recognize the stopped signal.
  //delay(4000);
  //esc.write(180);
}

void loop()
{
  //delay(1000);
  //esc.write(110);
  //Serial.print("Test");
  pinVal = analogRead(POTENTIOMETER_PIN);
  pinVal = map(pinVal, 0, 1023, 0, 180);
  Serial.println(pinVal);
  esc.write(pinVal);
  //Serial.println(analogRead(POTENTIOMETER_PIN));

}
