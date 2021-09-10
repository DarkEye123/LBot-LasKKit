#include "HCSR04.h"

#include "ultrasonic_sensor.h"

namespace ultrasonic_sensor_ns
{

    UltraSonicSensor::UltraSonicSensor(unsigned short trigger_pin, unsigned long echo_pin, unsigned short measurement_cycle) : trigger_pin(trigger_pin), echo_pin(echo_pin), measurement_cycle(measurement_cycle), last_measured_distance(INVALID_MEASUREMENT), last_measurement_timestamp(millis())
    {
        this->distanceSensor = new UltraSonicDistanceSensor(trigger_pin, echo_pin);
    };

    UltraSonicSensor::~UltraSonicSensor()
    {
        delete this->distanceSensor;
    }

    bool UltraSonicSensor::CanMeasure()
    {
        return millis() - this->last_measurement_timestamp > this->measurement_cycle;
    }

    float UltraSonicSensor::MeasureDistance(bool debug)
    {
        if (CanMeasure())
        {
            this->last_measured_distance = this->distanceSensor->measureDistanceCm();
            if (debug)
            {
                Serial.print("UltraSonicSensor::MeasureDistance ");
                Serial.println(this->last_measured_distance);

                Serial.print("UltraSonicSensor::IsDetectingImminentCollision ");
                Serial.println(this->IsDetectingImminentCollision());
                Serial.flush();
            }
            this->last_measurement_timestamp = millis();
        }
        return this->last_measured_distance;
    }

    bool UltraSonicSensor::IsDetectingImminentCollision()
    {
        if ((long)this->last_measured_distance != INVALID_MEASUREMENT && (long)this->last_measured_distance != TOO_FAR_TOO_CLOSE)
        {
            return this->last_measured_distance < IMMINENT_DANGER_DISTANCE;
        }
        return false;
    }

    UltraSonicSensor *Setup()
    {
        return new UltraSonicSensor(ULTRASONIC_TRIGGER_PIN, ULTRASONIC_ECHO_PIN, SUGGESTED_MEASUREMENT_CYCLE);
    }
}