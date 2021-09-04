#include "../lib/integrated_led/integrated_led.h"
#include "../lib/light_sensor/light_sensor.h"
#include "../lib/intelligent_led/intelligent_led.h"
#include "../lib/bell/bell.h"
#include "../lib/button/button.h"

#include "Arduino.h"

void setup()
{
  Serial.begin(9600);

  integrated_led::Setup();

  intelligent_led::Setup();

  button::Setup();

  bell::Setup();
  bell::Buzz();
}

void loop()
{
  button::LogValue();
  button::RunOnPress([](void)
                     {
                       Serial.println("just pressing the button");
                       bell::Buzz(100);
                     });
  light_sensor::LogValue();
  integrated_led::Blink();
  intelligent_led::SetRandomColorOnNextLed();
}