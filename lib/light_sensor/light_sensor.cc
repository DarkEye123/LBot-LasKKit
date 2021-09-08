#include "Arduino.h"
#include "light_sensor.h"

namespace light_sensor
{
    int ReadLightSensor(void)
    {
        return analogRead(LIGHT_SENSOR_PIN);
    }

    void LogValue(void)
    {
        Serial.print("light sensor value: ");
        Serial.println(ReadLightSensor());
    }
}