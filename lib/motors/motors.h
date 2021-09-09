#ifndef MOTORS_H
#define MOTORS_H

#include "ir_receiver.h"

#define MOTORS_FORWARD 3877175040
#define MOTORS_BACKWARD 2907897600
#define MOTORS_LEFT 4144561920
#define MOTORS_RIGHT 2774204160
#define MOTORS_SUPPORTED_CMD_LIST_LENGTH 4

#define STOP_CMD 0
#define MOVE_FORWARD_CMD 1
#define MOVE_BACKWARDS_CMD 2
#define TURN_RIGHT_CMD 3
#define TURN_LEFT_CMD 4

namespace motors
{
    class Motor
    {
        unsigned short pwm_pin;
        unsigned short pin;

    public:
        Motor(unsigned short pwm_pin, unsigned short pin);
        void Stop();
        void PositiveRotation(unsigned short speed);
        void NegativeRotation(unsigned short speed);
    };

    class MovementManager
    {

        Motor *A;
        Motor *B;

        unsigned short processing_period;
        unsigned int last_command;

    private:
        unsigned long last_timestamp;
        unsigned long supported_cmds[MOTORS_SUPPORTED_CMD_LIST_LENGTH] = {MOTORS_FORWARD, MOTORS_BACKWARD, MOTORS_LEFT, MOTORS_RIGHT};

    public:
        MovementManager(Motor *A, Motor *B);
        ~MovementManager();
        void MoveForward(unsigned short speed = 200); // 500 is ok for usb, not batteries
        void MoveBackward(unsigned short speed = 200);
        void TurnRight(unsigned short speed = 200);
        void TurnLeft(unsigned short speed = 200);
        // void MoveForward(unsigned short speed = 255); // 255 is ok for batteries
        void StopMovement(void);
        void Process(Data *data, boolean debug = false, boolean debug_all = false);
        boolean IsProcessing();
        boolean IsSupportedCmd(unsigned long cmd);
    };

    MovementManager *Setup(Motor *left = nullptr, Motor *right = nullptr);
}

#endif