

#include "IRremote.h"

#include "ir_receiver.h"

unsigned long received_code = 0;

namespace ir_receiver
{
    void Setup()
    {
        IrReceiver.begin(IR_RECEIVER_PIN, ENABLE_LED_FEEDBACK);
    }

    void LogValue(Data *data, bool debug)
    {
        if (debug && data->received)
        {
            Serial.print("IrReceiver.decodedIRData.decodedRawData ");
            Serial.println(IrReceiver.decodedIRData.decodedRawData, DEC);
            Serial.print("IrReceiver.decodedIRData.command ");
            Serial.println(IrReceiver.decodedIRData.command, DEC);
            Serial.print("IrReceiver.decodedIRData.protocol ");
            Serial.println(IrReceiver.decodedIRData.protocol, DEC);
            Serial.print("IrReceiver.decodedIRData.flags ");
            Serial.println(IrReceiver.decodedIRData.flags, DEC);

            Serial.print("ir_receiver:: received DATA: ");
            Serial.println(data->data, DEC);
            Serial.flush();
        }
    }

    /*
     * Be sure to call free(variable) after the call
     */
    Data *ReceiveData(bool debug)
    {
        struct Data *data = (Data *)malloc(sizeof(Data));
        data->data = 0;
        data->received = false;

        if (IrReceiver.decode())
        {
            data->received = true;
            if (IrReceiver.decodedIRData.flags != IRDATA_FLAGS_IS_REPEAT)
            {
                received_code = IrReceiver.decodedIRData.decodedRawData;
            }
            data->data = received_code;
            IrReceiver.resume(); // more like a reset of the state really
        }

        LogValue(data, debug);

        return data;
    }
}
