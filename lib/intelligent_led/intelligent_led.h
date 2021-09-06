namespace intelligent_led
{
    void Setup();
    void SetColor(byte r, byte g, byte b, byte led);
    void SetRandomColorOnNextLed(uint32_t every = 500);
}