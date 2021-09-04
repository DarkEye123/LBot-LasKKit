#include "Arduino.h"
#include "light_sensor.h"

namespace light_sensor
{
    int ReadLightSensor(void)
    {
        return analogRead(LIGHT_SENSOR_PIN);
    }

    void PrintToSerial(void)
    {
        // Serial.println("analog value: " + ReadLightSensor());
        Serial.println("analog value: ");
        Serial.println(ReadLightSensor());
    }
}