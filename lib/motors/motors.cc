#include "Arduino.h"

#include "motors.h"
#include "ir_receiver.h"

namespace motors
{
    Motor::Motor(unsigned short pwm_pin, unsigned short pin) : pwm_pin(pwm_pin), pin(pin)
    {
        pinMode(pwm_pin, OUTPUT);
        pinMode(pin, OUTPUT);
        this->stop();
    };

    void Motor::stop()
    {
        digitalWrite(this->pin, LOW);
        analogWrite(this->pwm_pin, LOW);
    }

    void Motor::positiveRotation(unsigned short speed)
    {
        digitalWrite(this->pin, LOW);
        analogWrite(this->pwm_pin, speed);
    }

    void Motor::negativeRotation(unsigned short speed)
    {
        digitalWrite(this->pin, HIGH);
        analogWrite(this->pwm_pin, speed);
    }

    MovementManager::MovementManager(Motor *A, Motor *B) : A(A), B(B){};

    void MovementManager::moveForward(unsigned short speed)
    {
        this->A->positiveRotation(speed);
        this->B->positiveRotation(speed);
    };

    MovementManager::~MovementManager()
    {
        delete this->A;
        delete this->B;
    };

    MovementManager *Setup(Motor *left, Motor *right)
    {
        Motor *A = left == nullptr ? new Motor(6, 7) : left;   // left motor
        Motor *B = right == nullptr ? new Motor(5, 4) : right; // right motor
        return new MovementManager(A, B);
    };

    void MovementManager::Process(Data *data)
    {
        if (data->received)
        {
            Serial.print("processing ");
            Serial.println(data->data, DEC);
        }
    }
};