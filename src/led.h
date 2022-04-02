#include <Arduino.h>

class LED
{

private:
    int pinNumber;

public:

    LED(int pinNumber);
    void flash();
    void flashAndHold();
    bool isOn();
    bool isOff();

};