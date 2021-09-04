#include "stdlib.h"
#include "Adafruit_NeoPixel.h"

uint8_t current_led = 0;

Adafruit_NeoPixel rgb = Adafruit_NeoPixel(2, 13);
// Adafruit_NeoPixel rgb = Adafruit_NeoPixel(2, 13, NEO_RGB + NEO_KHZ800); //TOTO UROBI GREEN RED BLUE V SKUTOCNOSTI

namespace intelligent_led
{

    void Setup()
    {
        rgb.begin();
        rgb.setBrightness(10);
    }

    void setColor(byte r, byte g, byte b, byte led)
    {
        uint32_t _rgb;
        _rgb = rgb.Color(r, g, b);
        rgb.setPixelColor(led, _rgb);
        rgb.show();
    }

    void SetRandomColorOnNextLed()
    {
        setColor(rand() % 256, rand() % 256, rand() % 256, current_led % 2);
        current_led++;
    }
}