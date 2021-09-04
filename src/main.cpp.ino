#include "Arduino.h"
#include "LightSensor.hpp"
#include "IntelligentLed.hpp"

void setup()
{
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  // turn the LED on (HIGH is the voltage level)
  Serial.println("High");
  digitalWrite(LED_BUILTIN, HIGH);

  // wait for a second
  delay(500);

  // turn the LED off by making the voltage LOW
  Serial.println("Low");
  digitalWrite(LED_BUILTIN, LOW);

  // wait for a second
  delay(500);
  intelligent_led::setRandomColorOnNextLed();
  light_sensor::printToSerial();
}