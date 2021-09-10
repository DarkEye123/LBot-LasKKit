#include "Arduino.h"
#include "ir_receiver.h"

#include "motors.h"
#include "motor_manager.h"

namespace movement_manager
{
    MovementManager::MovementManager(motors::Motor *A, motors::Motor *B, unsigned short default_speed) : A(A), B(B), processing_period(200), last_command(0), current_speed(default_speed), last_timestamp(millis()){};

    void MovementManager::MoveForward(unsigned short speed)
    {
        this->A->PositiveRotation(speed);
        this->B->PositiveRotation(speed);
    };

    void MovementManager::MoveBackward(unsigned short speed)
    {
        this->A->NegativeRotation(speed);
        this->B->NegativeRotation(speed);
    };

    void MovementManager::TurnRight(unsigned short speed)
    {
        this->A->PositiveRotation(speed);
        this->B->NegativeRotation(speed);
    };

    void MovementManager::TurnLeft(unsigned short speed)
    {
        this->B->PositiveRotation(speed);
        this->A->NegativeRotation(speed);
    };

    void MovementManager::StopMovement(void)
    {
        this->A->Stop();
        this->B->Stop();
    };

    MovementManager::~MovementManager()
    {
        delete this->A;
        delete this->B;
    };

    MovementManager *Setup(motors::Motor *left, motors::Motor *right)
    {
        motors::Motor *A = left == nullptr ? new motors::Motor(6, 7, MOTORS_CORRECTION_OFFSET) : left; // left motor
        motors::Motor *B = right == nullptr ? new motors::Motor(5, 4) : right;                         // right motor
        return new MovementManager(A, B);
    };

    boolean MovementManager::IsProcessing()
    {
        return millis() - this->last_timestamp <= this->processing_period;
    }

    boolean MovementManager::IsSupportedCmd(unsigned long cmd)
    {
        for (unsigned short x = 0; x < MOTORS_SUPPORTED_CMD_LIST_LENGTH; ++x)
        {
            if (this->supported_cmds[x] == cmd)
            {
                return true;
            }
        }
        return false;
    }

    void MovementManager::SpeedUp()
    {
        this->current_speed = min(this->current_speed + MOTORS_SPEED_STEP, MOTORS_MAX_SPEED);
    }

    void MovementManager::SpeedDown()
    {
        this->current_speed = max(this->current_speed - MOTORS_SPEED_STEP, MOTORS_MIN_SPEED);
    }

    void MovementManager::Process(Data *data, boolean imminent_collision_detected, boolean debug, boolean debug_all)
    {
        if (debug && debug_all)
        {
            Serial.print("MovementManager::Process::data->received ");
            Serial.println(data->received);

            Serial.print("MovementManager::Process::last_command ");
            Serial.println(last_command);
        }
        if (data->received)
        {
            if (debug)
            {
                Serial.print("MovementManager::Process::data->data ");
                Serial.println(data->data);
            }
            if (this->IsSupportedCmd(data->data))
            {
                if (data->data == MOTORS_FORWARD)
                {
                    if (debug)
                    {
                        Serial.println("MovementManager::Process::MoveForward");
                        Serial.flush();
                    }

                    if (!imminent_collision_detected)
                    {
                        MoveForward(this->current_speed);
                    }
                    this->last_command = MOVE_FORWARD_CMD;
                }

                else if (data->data == MOTORS_BACKWARD)
                {
                    if (debug)
                    {
                        Serial.println("MovementManager::Process::MoveBackwards");
                        Serial.flush();
                    }

                    MoveBackward(this->current_speed);
                    this->last_command = MOVE_BACKWARDS_CMD;
                }

                else if (data->data == MOTORS_RIGHT)
                {
                    if (debug)
                    {
                        Serial.println("MovementManager::Process::TurnRight");
                        Serial.flush();
                    }

                    TurnRight(this->current_speed / 2);
                    this->last_command = TURN_RIGHT_CMD;
                }

                else if (data->data == MOTORS_LEFT)
                {
                    if (debug)
                    {
                        Serial.println("MovementManager::Process::TurnLeft");
                        Serial.flush();
                    }

                    TurnLeft(this->current_speed / 2);
                    this->last_command = TURN_LEFT_CMD;
                }

                else if (data->data == MOTORS_SPEED_UP)
                {
                    if (debug)
                    {
                        Serial.println("MovementManager::Process::SPEED_UP");
                        Serial.flush();
                    }

                    if (this->last_command != SPEED_MANUPULATION_CMD)
                    {
                        SpeedUp();
                        this->last_command = SPEED_MANUPULATION_CMD;
                        Process(data, imminent_collision_detected, debug, debug_all);
                    }
                }

                else if (data->data == MOTORS_SPEED_DOWN)
                {
                    if (debug)
                    {
                        Serial.println("MovementManager::Process::SPEED_DOWN");
                        Serial.flush();
                    }

                    if (this->last_command != SPEED_MANUPULATION_CMD)
                    {
                        SpeedDown();
                        this->last_command = SPEED_MANUPULATION_CMD;
                        Process(data, imminent_collision_detected, debug, debug_all);
                    }
                }

                if (imminent_collision_detected && this->last_command == MOVE_FORWARD_CMD)
                {
                    StopMovement();
                }
                this->last_timestamp = millis();
            }
            else
            {
                const bool is_processing = this->IsProcessing();
                if (debug)
                {
                    Serial.print("MovementManager::Process::last_command ");
                    Serial.println(last_command);
                    Serial.print("MovementManager::Process::IsProcessing ");
                    Serial.println(is_processing);
                }
                if (!is_processing || imminent_collision_detected)
                {

                    if (last_command != STOP_CMD)
                    {
                        if (debug)
                            Serial.println("MovementManager::Process::StopMovement");
                        StopMovement();
                    }
                    last_command = STOP_CMD;
                }
            }
        }
        else if (!this->IsProcessing() || this->last_command == MOVE_FORWARD_CMD && imminent_collision_detected)
        {
            if (debug)
                Serial.println("MovementManager::Process::StopMovement");
            StopMovement();
            last_command = STOP_CMD;
        }
    }
};