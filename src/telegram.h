#include <Arduino.h>

class Telegram
{
private:
    char bytes[512];
    unsigned int index = 0;
    unsigned int length = 0;
    unsigned int CRC16;
    static const char terminatingChar = '!';
    bool completed = false;
    
    unsigned int calcCRC();
    unsigned int getCRC();
    void VerifyCRC();


public:
    void ReadFromSerial(HardwareSerial serial);
    bool isCompleted();
    bool isVerified();

};