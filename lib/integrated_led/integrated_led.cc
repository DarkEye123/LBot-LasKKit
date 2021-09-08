#include "Arduino.h"

namespace integrated_led
{
    unsigned long last_interval = 0;
    int led_state = LOW;

    void Setup()
    {
        // initialize LED digital pin as an output.
        pinMode(LED_BUILTIN, OUTPUT);
        last_interval = millis();
    }

    void Blink(bool serial_output_enabled = false, uint16_t wait_for = 500)
    {
        unsigned long current = millis();
        if (current - last_interval > wait_for)
        {
            last_interval = current;
            led_state = led_state == LOW ? HIGH : LOW;
            if (serial_output_enabled)
            {
                Serial.println(led_state == LOW ? "Low" : "High");
            }
            digitalWrite(LED_BUILTIN, led_state);
        }
    }
}