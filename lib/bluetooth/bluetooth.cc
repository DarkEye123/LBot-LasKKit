#include "Arduino.h"
#include "SoftwareSerial.h"

#include "bluetooth.h"

SoftwareSerial BT(RX_PIN, TX_PIN); // original RX, TX was not working for my HC-06 module, so I rewired it

namespace bluetooth_ns
{
    unsigned long ms;

    void Setup()
    {
        BT.begin(9600);
        Serial.println("Bluetooth::initializing...");
        pinMode(13, OUTPUT);
        pinMode(RX_PIN, INPUT);
        pinMode(TX_PIN, OUTPUT);
        ms = millis();
        Serial.println("Bluetooth::done...");
    };

    Data *ReceiveData(bool debug)
    {
        bool can_print = millis() - ms > 2000;
        if (BT.available())
        {
            int x = BT.read();
            if (debug)
            {
                Serial.print("Bluetooth::received ");
                Serial.println(x, DEC);
            }
        }
        if (can_print)
        {
            BT.write("\nPING BT");
            ms = millis();
        }
    }
}
