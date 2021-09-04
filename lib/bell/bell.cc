#include "Arduino.h"

#include "bell.h"

namespace bell
{
    void Setup()
    {
        pinMode(BELL_PIN, OUTPUT);
    }
    void Buzz(uint16_t ring_for)
    {
        tone(BELL_PIN, 1000, ring_for);
    }
}