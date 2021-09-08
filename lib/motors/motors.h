#ifndef MOTORS_H
#define MOTORS_H

#include "ir_receiver.h"

namespace motors
{
    class Motor
    {
        unsigned short pwm_pin;
        unsigned short pin;

    public:
        Motor(unsigned short pwm_pin, unsigned short pin);
        void stop();
        void positiveRotation(unsigned short speed);
        void negativeRotation(unsigned short speed);
    };

    class MovementManager
    {

        Motor *A;
        Motor *B;

    public:
        MovementManager(Motor *A, Motor *B);
        ~MovementManager();
        void moveForward(unsigned short speed = 500); // 500 is ok for usb, not batteries
        void Process(Data *data);
    };

    MovementManager *Setup(Motor *left = nullptr, Motor *right = nullptr);
}

#endif