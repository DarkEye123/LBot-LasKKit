#define BUTTON_PIN A7

namespace button
{
    bool IsPressed();
    void Setup();
    void LogValue();
    void RunOnPress(void (*)(void));
}