#ifndef INFRARED_H
#define INFRARED_H

#define RIGHT_INFRA_SENSOR_PIN 10
#define LEFT_INFRA_SENSOR_PIN 9

namespace infrared_line_sensor
{
    bool ReadRightSensor();
    bool ReadLeftSensor();
    bool IsDetectingNoPath();
}

#endif