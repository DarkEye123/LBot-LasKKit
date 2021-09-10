#include "Arduino.h"

#include "infrared_line_sensor.h"

namespace infrared_line_sensor
{
    bool ReadRightSensor()
    {
        return digitalRead(RIGHT_INFRA_SENSOR_PIN);
    }
    bool ReadLeftSensor()
    {
        return digitalRead(LEFT_INFRA_SENSOR_PIN);
    };

    bool IsDetectingNoPath()
    {
        return !ReadRightSensor() || !ReadLeftSensor();
    };
}