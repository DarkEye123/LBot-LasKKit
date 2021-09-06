#define IR_RECEIVER_PIN 2

struct Data
{
    bool received;
    unsigned long data;
};

namespace ir_receiver
{
    void Setup();
    void LogValue();
    Data *ReceiveData();
}