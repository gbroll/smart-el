#include <Arduino.h>
#include <telegram.h>
#include <CRC16.h>


using namespace std;

Telegram::Telegram()
{
    crc16.setPolynome(0x8005);
    crc16.setReverseOut(true);
    crc16.setReverseIn(true);
 
}

void Telegram::ReadFromSerial(HardwareSerial &serial)
{
    
    while (serial.available()){serial.read();}; //clear buffer

    while (!completed)
    {
        Serial.println("Waiting for serial input");
        if (serial.available() > 0)
        {
            length = serial.readBytesUntil(terminatingChar, byteArray, 1024);
            if (length > 0) 
            {
                serial.readBytes(crc16Buffer, 2);
                completed = true;
            }
        } 
        
    }
    VerifyCRC();
}

uint16_t Telegram::calcCRC()
{
    crc16.add(byteArrayPtr, length);
    return crc16.getCRC();
}

uint16_t Telegram::getSentCRC()
{
    return (uint16_t)(crc16Buffer[1] << 8) + crc16Buffer[0];
}

void Telegram::VerifyCRC()
{

    if (!completed) return;
    uint16_t calculatedCRC = calcCRC();
    uint16_t sentCRC = getSentCRC();

    verified = (calculatedCRC == sentCRC);


}

bool Telegram::isCompleted()
{
    return completed;
}

bool Telegram::isVerified()

{
    return verified;
}

void Telegram::PublishToMQTT(PubSubClient client, char* topic, char* obisCode)
{

    if (!completed || !verified) {return;}
    
    client.publish("outTopic", "Publishing data from telegram");    

}
