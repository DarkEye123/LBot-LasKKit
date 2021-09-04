#include "Arduino.h"
#include "LightSensor.hpp"

namespace light_sensor
{
    int readLightSensor(void)
    {
        return analogRead(LIGHT_SENSOR_PIN);
    }

    void printToSerial(void)
    {
        // Serial.println("analog value: " + readLightSensor());
        Serial.println("analog value: ");
        Serial.println(readLightSensor());
    }
}