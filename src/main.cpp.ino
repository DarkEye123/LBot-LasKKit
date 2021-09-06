#include "../lib/integrated_led/integrated_led.h"
#include "../lib/light_sensor/light_sensor.h"
#include "../lib/intelligent_led/intelligent_led.h"
#include "../lib/bell/bell.h"
#include "../lib/button/button.h"
#include "../lib/ir_receiver/ir_receiver.h"

#include "Arduino.h"

void setup()
{
  Serial.begin(9600);

  // integrated_led::Setup();
  intelligent_led::Setup();
  button::Setup();

  bell::Setup();
  bell::Buzz();

  ir_receiver::Setup();
}

void loop()
{
  button::RunOnPress([](void)
                     {
                       Serial.println("just pressing the button");
                       bell::Buzz(100);
                       light_sensor::LogValue();
                     });
  // integrated_led::Blink(true, 500); // for now this fights with intelligent leds on PIN 13 --> I need to check registers
  intelligent_led::SetRandomColorOnNextLed();
  ir_receiver::LogValue();
}