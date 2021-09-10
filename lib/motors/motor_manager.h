#ifndef MOTOR_MANAGER_H
#define MOTOR_MANAGER_H

#include "motors.h"

#define MOTORS_FORWARD 3877175040
#define MOTORS_BACKWARD 2907897600
#define MOTORS_LEFT 4144561920
#define MOTORS_RIGHT 2774204160
#define MOTORS_SPEED_UP 3860463360
#define MOTORS_SPEED_DOWN 3910598400

#define MOTORS_SUPPORTED_CMD_LIST_LENGTH 6
#define MOTORS_DEFAULT_SPEED 150
#define MOTORS_MIN_SPEED 25
#define MOTORS_CORRECTION_OFFSET 25
#define MOTORS_MAX_SPEED 255
#define MOTORS_SPEED_STEP 25

#define STOP_CMD 0
#define MOVE_FORWARD_CMD 1
#define MOVE_BACKWARDS_CMD 2
#define TURN_RIGHT_CMD 3
#define TURN_LEFT_CMD 4
#define SPEED_MANUPULATION_CMD 5

namespace movement_manager
{
    class MovementManager
    {

        motors::Motor *A;
        motors::Motor *B;

        unsigned short processing_period;
        unsigned int last_command;

    private:
        unsigned short current_speed;
        unsigned long last_timestamp;
        unsigned long supported_cmds[MOTORS_SUPPORTED_CMD_LIST_LENGTH] = {MOTORS_FORWARD, MOTORS_BACKWARD, MOTORS_LEFT, MOTORS_RIGHT, MOTORS_SPEED_UP, MOTORS_SPEED_DOWN};

    public:
        MovementManager(motors::Motor *A, motors::Motor *B, unsigned short default_speed = MOTORS_DEFAULT_SPEED);
        ~MovementManager();
        void MoveForward(unsigned short speed = MOTORS_DEFAULT_SPEED); // 500 is ok for usb, not batteries
        void MoveBackward(unsigned short speed = MOTORS_DEFAULT_SPEED);
        void TurnRight(unsigned short speed = MOTORS_DEFAULT_SPEED / 2);
        void TurnLeft(unsigned short speed = MOTORS_DEFAULT_SPEED / 2);
        void SpeedUp();
        void SpeedDown();
        // void MoveForward(unsigned short speed = 255); // 255 is ok for batteries
        void StopMovement(void);
        void Process(Data *data, boolean imminent_collision_detected, boolean debug = false, boolean debug_all = false);
        boolean IsProcessing();
        boolean IsSupportedCmd(unsigned long cmd);
    };

    MovementManager *Setup(motors::Motor *left = nullptr, motors::Motor *right = nullptr);
}

#endif