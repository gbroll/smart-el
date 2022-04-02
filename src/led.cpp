#include "led.h"

LED::LED(int pinNumber)
{
    this->pinNumber = pinNumber;
    pinMode(LED_BUILTIN, OUTPUT);
}

void LED::flash()
{
    int n = 5;
    for (int i = 0; i < n; i++)
    {   
        digitalWrite(pinNumber, HIGH);
        delay(100);
        digitalWrite(pinNumber, LOW);
        delay(100);
    }
}

void LED::flashAndHold()
{
    this->flash();
    digitalWrite(pinNumber, HIGH);
}
