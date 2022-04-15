#include <Arduino.h>
#include <CRC16.h>
#include <PubSubClient.h>

class Telegram
{
private:
    char byteArray[1024];
    uint8_t *byteArrayPtr;

    unsigned int index = 0;
    unsigned int length = 0;
    static const char terminatingChar = '!';
    bool completed = false;
    
    CRC16 crc16;
    uint8_t crc16Buffer[2];
    uint16_t  calcCRC();
    uint16_t  getSentCRC();
    void VerifyCRC();
    bool verified = false;


public:
    Telegram();
    void ReadFromSerial(HardwareSerial &serial);
    bool isCompleted();
    bool isVerified();
    void PublishToMQTT(PubSubClient client, char* topic, char* obisCode);

};