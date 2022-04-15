#include <Arduino.h>
#include <unity.h>
#include "CRC16.h"

void setUp()
{

}

void tearDown()
{

}

void testCRC16()
{
    CRC16 crc16;
    crc16.setPolynome(0x8005);
    crc16.setReverseOut(true);
    crc16.setReverseIn(true);
 

    //uint8_t test_data[24] = "123456789";
    //uint16_t expected = 0xBB3D;
    
    uint8_t test_data[1024] = 
        "/ELL5\\253833635_A\r\n\r\n"
        "0-0:1.0.0(210217184019W)\r\n"
        "1-0:1.8.0(00006678.394*kWh)\r\n"
        "1-0:2.8.0(00000000.000*kWh)\r\n"
        "1-0:3.8.0(00000021.988*kvarh)\r\n"
        "1-0:4.8.0(00001020.971*kvarh)\r\n"
        "1-0:1.7.0(0001.727*kW)\r\n"
        "1-0:2.7.0(0000.000*kW)\r\n"
        "1-0:3.7.0(0000.000*kvar)\r\n"
        "1-0:4.7.0(0000.309*kvar)\r\n"
        "1-0:21.7.0(0001.023*kW)\r\n"
        "1-0:41.7.0(0000.350*kW)\r\n"
        "1-0:61.7.0(0000.353*kW)\r\n"
        "1-0:22.7.0(0000.000*kW)\r\n"
        "1-0:42.7.0(0000.000*kW)\r\n"
        "1-0:62.7.0(0000.000*kW)\r\n"
        "1-0:23.7.0(0000.000*kvar)\r\n"
        "1-0:43.7.0(0000.000*kvar)\r\n"
        "1-0:63.7.0(0000.000*kvar)\r\n"
        "1-0:24.7.0(0000.009*kvar)\r\n"
        "1-0:44.7.0(0000.161*kvar)\r\n"
        "1-0:64.7.0(0000.138*kvar)\r\n"
        "1-0:32.7.0(240.3*V)\r\n"
        "1-0:52.7.0(240.1*V)\r\n"
        "1-0:72.7.0(241.3*V)\r\n"
        "1-0:31.7.0(004.2*A)\r\n"
        "1-0:51.7.0(001.6*A)\r\n"
        "1-0:71.7.0(001.7*A)\r\n!";
        
    Serial.println(test_data[705]);
    uint16_t expected = 0x7945;  
    crc16.add((uint8_t*)test_data, 706);
    
    Serial.println(expected, HEX);
    Serial.println(crc16.getCRC(), HEX);
    
    TEST_ASSERT_EQUAL(expected, crc16.getCRC());

}

void setup()
{
    delay(2000);
    UNITY_BEGIN();
    
    RUN_TEST(testCRC16);

    UNITY_END();
}

void loop()
{

}