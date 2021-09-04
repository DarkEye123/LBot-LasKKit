#include "Arduino.h"

#include "button.h"

#define BREAKING_VALUE 512

namespace button
{

    void Setup()
    {
        pinMode(BUTTON_PIN, INPUT);
    }

    void LogValue()
    {
        Serial.print("button value: ");
        Serial.println(analogRead(BUTTON_PIN));
    }

    bool IsPressed()
    {
        return analogRead(BUTTON_PIN) < BREAKING_VALUE;
    }
}