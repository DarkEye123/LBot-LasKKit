#include "stdlib.h"
#include "Adafruit_NeoPixel.h"

Adafruit_NeoPixel rgb = Adafruit_NeoPixel(2, 13);
// Adafruit_NeoPixel rgb = Adafruit_NeoPixel(2, 13, NEO_RGB + NEO_KHZ800); //TOTO UROBI GREEN RED BLUE V SKUTOCNOSTI

namespace intelligent_led
{
    uint8_t current_led = 0;
    unsigned long last_interval = 0;

    void Setup()
    {
        rgb.begin();
        rgb.setBrightness(10);
        last_interval = millis();
    }

    void SetColor(byte r, byte g, byte b, byte led)
    {
        uint32_t _rgb;
        _rgb = rgb.Color(r, g, b);
        rgb.setPixelColor(led, _rgb);
        rgb.show();
    }

    void SetRandomColorOnNextLed(uint32_t every)
    {
        unsigned long current = millis();
        if (current - last_interval > every)
        {
            last_interval = current;
            SetColor(rand() % 256, rand() % 256, rand() % 256, current_led % 2);
            current_led++;
        }
    }
}