// #include "../lib/integrated_led/integrated_led.h"
#include "../lib/intelligent_led/intelligent_led.h"
#include "../lib/light_sensor/light_sensor.h"
#include "../lib/bell/bell.h"
#include "../lib/button/button.h"
#include "../lib/ir_receiver/ir_receiver.h"
#include "../lib/motors/motor_manager.h"
#include "../lib/ultrasonic_sensor/ultrasonic_sensor.h"

#include "Arduino.h"

movement_manager::MovementManager *mmanager = nullptr;
ultrasonic_sensor_ns::UltraSonicSensor *ultrasonic_sensor = nullptr;

void setup()
{
  Serial.begin(115200);
  // Serial.begin(9600);

  // integrated_led::Setup();
  intelligent_led::Setup();
  button::Setup();

  bell::Setup();

  mmanager = movement_manager::Setup();
  ultrasonic_sensor = ultrasonic_sensor_ns::Setup();
  ir_receiver::Setup(); // makes initial Buzz to hide (dunno why) TODO
}

void loop()
{
  // integrated_led::Blink(true, 500); // for now this fights with intelligent leds on PIN 13 --> I need to check registers

  ultrasonic_sensor->MeasureDistance(true);
  button::RunOnPress([](void)
                     { light_sensor::LogValue(); });
  Data *data = ir_receiver::ReceiveData(false);

  mmanager->Process(data, ultrasonic_sensor->IsDetectingImminentCollision(), false);
  if (ultrasonic_sensor->IsDetectingImminentCollision())
  {
    bell::Buzz(100);
  }

  free(data);
  data = NULL;

  intelligent_led::SetRandomColorOnNextLed();
}