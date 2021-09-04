#include "Arduino.h"
#include "IntegratedLed.hpp"
#include "LightSensor.hpp"
#include "IntelligentLed.hpp"

void setup()
{
  Serial.begin(9600);
  integrated_led::setup();
  intelligent_led::setup();
}

void loop()
{
  integrated_led::blink();
  intelligent_led::setRandomColorOnNextLed();
  light_sensor::printToSerial();
}