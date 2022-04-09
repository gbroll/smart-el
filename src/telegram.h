#include <Arduino.h>
#include <CRC16.h>

class Telegram
{
private:
    char byteArray[512];
    uint8_t *byteArrayPtr;

    unsigned int index = 0;
    unsigned int length = 0;
    static const char terminatingChar = '!';
    bool completed = false;
    
    CRC16 crc16;
    uint8_t crc16Buffer[];
    uint16_t  calcCRC();
    uint16_t  getSentCRC();
    void VerifyCRC();
    bool verified = false;


public:
    void ReadFromSerial(HardwareSerial serial);
    bool isCompleted();
    bool isVerified();

};