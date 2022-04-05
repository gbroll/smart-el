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
            length = serial.readBytesUntil(terminatingChar, bytes, 512);
            if (length > 0) 
            {
                completed = true;
            }
        }
    }

    VerifyCRC();

}

unsigned int Telegram::calcCRC()
{
    crc16.getCRC();
}

unsigned int Telegram::getCRC()
{

}

void Telegram::VerifyCRC()
{

    if (!completed) return;


}