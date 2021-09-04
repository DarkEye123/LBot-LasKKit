#define LIGHT_SENSOR_PIN A6
// #define LIGHT_SENSOR_PIN 20 // same value of PIN

namespace light_sensor
{
    void PrintToSerial(void);
    int ReadLightSensor(void);
}