#include <Arduino.h>
#include <telegram.h>
#include <CRC16.h>

void Telegram::ReadFromSerial(HardwareSerial serial)
{

    while (!completed)
    {
        if (serial.available())
        {
            //c = serial.read();
            length = serial.readBytesUntil(terminatingChar, byteArray, 512);
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


}