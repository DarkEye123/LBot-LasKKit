#include "Arduino.h"

#include "motors.h"

namespace motors
{
    Motor::Motor(unsigned short pwm_pin, unsigned short pin, unsigned short correction_offset) : pwm_pin(pwm_pin), pin(pin), correction_offset(correction_offset)
    {
        pinMode(pwm_pin, OUTPUT);
        pinMode(pin, OUTPUT);
        this->Stop();
    };

    Motor::Motor(unsigned short pwm_pin, unsigned short pin) : Motor::Motor(pwm_pin, pin, 0){};

    void Motor::Stop()
    {
        digitalWrite(this->pin, LOW);
        analogWrite(this->pwm_pin, LOW);
    }

    void Motor::PositiveRotation(unsigned short speed)
    {
        digitalWrite(this->pin, LOW);
        analogWrite(this->pwm_pin, min(speed + this->correction_offset, MAX_SUPPORTED_SPEED));
    }

    void Motor::NegativeRotation(unsigned short speed)
    {
        digitalWrite(this->pin, HIGH);
        analogWrite(this->pwm_pin, min(speed + this->correction_offset, MAX_SUPPORTED_SPEED));
    }
};