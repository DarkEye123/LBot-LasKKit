
#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#define RX_PIN A3
#define TX_PIN A2

#include "common.h"

namespace bluetooth_ns
{
    void Setup();
    Data *ReceiveData(bool debug);
}

#endif