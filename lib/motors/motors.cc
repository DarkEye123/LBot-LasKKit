#include "Arduino.h"
#include "ir_receiver.h"

#include "motors.h"

namespace motors
{
    Motor::Motor(unsigned short pwm_pin, unsigned short pin) : pwm_pin(pwm_pin), pin(pin)
    {
        pinMode(pwm_pin, OUTPUT);
        pinMode(pin, OUTPUT);
        this->Stop();
    };

    void Motor::Stop()
    {
        digitalWrite(this->pin, LOW);
        analogWrite(this->pwm_pin, LOW);
    }

    void Motor::PositiveRotation(unsigned short speed)
    {
        digitalWrite(this->pin, LOW);
        analogWrite(this->pwm_pin, speed);
    }

    void Motor::NegativeRotation(unsigned short speed)
    {
        digitalWrite(this->pin, HIGH);
        analogWrite(this->pwm_pin, speed);
    }

    MovementManager::MovementManager(Motor *A, Motor *B) : A(A), B(B), processing_period(200), last_command(0), last_timestamp(millis()){};

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
    };

    void MovementManager::TurnLeft(unsigned short speed)
    {
        this->B->PositiveRotation(speed);
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

    MovementManager *Setup(Motor *left, Motor *right)
    {
        Motor *A = left == nullptr ? new Motor(6, 7) : left;   // left motor
        Motor *B = right == nullptr ? new Motor(5, 4) : right; // right motor
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

    void MovementManager::Process(Data *data, boolean debug, boolean debug_all)
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

                    MoveForward();
                    this->last_command = MOVE_FORWARD_CMD;
                }
                else if (data->data == MOTORS_BACKWARD)
                {
                    if (debug)
                    {
                        Serial.println("MovementManager::Process::MoveBackwards");
                        Serial.flush();
                    }

                    MoveBackward();
                    this->last_command = MOVE_BACKWARDS_CMD;
                }
                else if (data->data == MOTORS_RIGHT)
                {
                    if (debug)
                    {
                        Serial.println("MovementManager::Process::TurnRight");
                        Serial.flush();
                    }

                    TurnRight();
                    this->last_command = TURN_RIGHT_CMD;
                }
                else if (data->data == MOTORS_LEFT)
                {
                    if (debug)
                    {
                        Serial.println("MovementManager::Process::TurnLeft");
                        Serial.flush();
                    }

                    TurnLeft();
                    this->last_command = TURN_LEFT_CMD;
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
                if (!is_processing)
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
        else if (!this->IsProcessing())
        {
            if (debug)
                Serial.println("MovementManager::Process::StopMovement");
            StopMovement();
            last_command = STOP_CMD;
        }
    }
};