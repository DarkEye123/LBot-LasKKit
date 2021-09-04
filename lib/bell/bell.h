#define BELL_PIN 8

namespace bell
{
    void Setup();
    void Buzz(uint16_t ring_for = 1000);
}