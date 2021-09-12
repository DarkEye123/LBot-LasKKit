#ifndef IR_RECEIVER_H
#define IR_RECEIVER_H

#define IR_RECEIVER_PIN 2

#include "common.h"

namespace ir_receiver
{
    void Setup();
    Data *ReceiveData(bool debug = false);
}

#endif