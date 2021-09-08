// #include "../lib/integrated_led/integrated_led.h"
#include "../lib/light_sensor/light_sensor.h"
#include "../lib/intelligent_led/intelligent_led.h"
#include "../lib/bell/bell.h"
#include "../lib/button/button.h"
#include "../lib/ir_receiver/ir_receiver.h"
#include "../lib/motors/motors.h"

#include "Arduino.h"

motors::MovementManager *movement_manager = nullptr;

void setup()
{
  Serial.begin(9600);

  // integrated_led::Setup();
  intelligent_led::Setup();
  button::Setup();

  bell::Setup();
  bell::Buzz();

  ir_receiver::Setup();

  movement_manager = motors::Setup();
}

void loop()
{
  // integrated_led::Blink(true, 500); // for now this fights with intelligent leds on PIN 13 --> I need to check registers

  button::RunOnPress([](void)
                     { light_sensor::LogValue(); });
  Data *data = ir_receiver::ReceiveData();

  movement_manager->Process(data);

  free(data);

  data = NULL;

  intelligent_led::SetRandomColorOnNextLed();
}