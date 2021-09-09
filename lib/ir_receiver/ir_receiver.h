#ifndef IR_RECEIVER_H
#define IR_RECEIVER_H

#define IR_RECEIVER_PIN 2

struct Data
{
    bool received;
    unsigned long data;
};

namespace ir_receiver
{
    void Setup();
    Data *ReceiveData(bool debug = false);
}

#endif