#include "Arduino.h"

namespace integrated_led
{
    void setup()
    {
        // initialize LED digital pin as an output.
        pinMode(LED_BUILTIN, OUTPUT);
    }

    void blink(bool serial_output_enabled = false, uint16_t waitFor = 500)
    {
        // turn the LED on (HIGH is the voltage level)
        if (serial_output_enabled)
        {

            Serial.println("High");
        }
        digitalWrite(LED_BUILTIN, HIGH);

        // wait for a second
        delay(waitFor);

        // turn the LED off by making the voltage LOW
        if (serial_output_enabled)
        {

            Serial.println("Low");
        }
        digitalWrite(LED_BUILTIN, LOW);
        delay(waitFor);
    }
}