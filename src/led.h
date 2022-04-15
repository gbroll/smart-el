#include <Arduino.h>
#ifndef LED_H
#define LED_H

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

#endif