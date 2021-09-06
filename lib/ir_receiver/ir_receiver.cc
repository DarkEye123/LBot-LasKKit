

#include "IRremote.h"

#include "ir_receiver.h"

IRrecv irrecv(IR_RECEIVER_PIN);
unsigned long received_code = 0;

namespace ir_receiver
{
    void Setup()
    {
        irrecv.enableIRIn();
        irrecv.blink13(true);
    }

    /*
     * Be sure to call free(variable) after the call
     */
    Data *ReceiveData()
    {
        decode_results received_data;

        struct Data *data = (Data *)malloc(sizeof(Data));
        data->data = 0;
        data->received = false;

        if (irrecv.decode(&received_data))
        {
            data->received = true;
            if (received_data.value != REPEAT)
            {
                received_code = received_data.value;
            }
            data->data = received_code;
            irrecv.resume(); // more like a reset of the state really
        }

        return data;
    }

    void LogValue()
    {
        Data *data = ReceiveData();
        if (data->received)
        {
            Serial.print("received IR_DATA: ");
            Serial.println(data->data, DEC);
        }
        free(data);
        data = NULL;
    }
}
