#include "Arduino.h"

namespace integrated_led
{
    void Setup()
    {
        // initialize LED digital pin as an output.
        pinMode(LED_BUILTIN, OUTPUT);
    }

    void Blink(bool serial_output_enabled = false, uint16_t wait_for = 500)
    {
        // turn the LED on (HIGH is the voltage level)
        if (serial_output_enabled)
        {

            Serial.println("High");
        }
        digitalWrite(LED_BUILTIN, HIGH);

        // wait for a second
        delay(wait_for);

        // turn the LED off by making the voltage LOW
        if (serial_output_enabled)
        {

            Serial.println("Low");
        }
        digitalWrite(LED_BUILTIN, LOW);
        delay(wait_for);
    }
}