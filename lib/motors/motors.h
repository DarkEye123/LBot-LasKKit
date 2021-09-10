#ifndef MOTORS_H
#define MOTORS_H

#define MAX_SUPPORTED_SPEED 255
namespace motors
{
    class Motor
    {
        unsigned short pwm_pin;
        unsigned short pin;
        unsigned short correction_offset;

    public:
        Motor(unsigned short pwm_pin, unsigned short pin, unsigned short correction_offset);
        Motor(unsigned short pwm_pin, unsigned short pin);
        void Stop();
        void PositiveRotation(unsigned short speed);
        void NegativeRotation(unsigned short speed);
    };
}
#endif