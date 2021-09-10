#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include "HCSR04.h"

#define ULTRASONIC_TRIGGER_PIN 11
#define ULTRASONIC_ECHO_PIN 12

// how long to wait before another trigger can occur in ms
// check https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf
#define SUGGESTED_MEASUREMENT_CYCLE 60

// in cm
#define IMMINENT_DANGER_DISTANCE 15

#define INVALID_MEASUREMENT -2
#define TOO_FAR_TOO_CLOSE -1

namespace ultrasonic_sensor_ns
{
    class UltraSonicSensor
    {

    private:
        unsigned short trigger_pin, echo_pin, measurement_cycle;
        float last_measured_distance;
        unsigned short last_measurement_timestamp;
        UltraSonicDistanceSensor *distanceSensor;

    public:
        UltraSonicSensor(unsigned short trigger_pin, unsigned long echo_pin, unsigned short measurement_cycle = SUGGESTED_MEASUREMENT_CYCLE);
        ~UltraSonicSensor();
        bool CanMeasure();
        float MeasureDistance(bool debug = false);
        bool IsDetectingImminentCollision();
    };

    UltraSonicSensor *Setup();
}

#endif