#include <Arduino.h>
#include "WiFi.h"
#include <PubSubClient.h>
#include "../secrets.h"

#ifndef LED_BUILTIN
#define LED_BUILTIN 4
#endif

int test = MQTTCONNECT;

int status = WL_IDLE_STATUS;
void flash_led_hold();

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    
    Serial.begin(115200);
    Serial.print("LED_BUILTIN is at PIN: ");
    Serial.print(LED_BUILTIN);

    while (status != WL_CONNECTED) 
    {
        Serial.print(MQTTCONNECT);
        Serial.print("Attempting to connect to SSID: ");
        Serial.println(SECRET_SSID);
        status = WiFi.begin(SECRET_SSID, SECRET_PASS);
        delay(10000);
    }

    Serial.println("Setup done");
    flash_led_hold();

}

void loop() 
{
    delay(5000);
}

void flash_led()
{
    int n = 5;
    for (int i = 0; i < n; i++)
    {   
        digitalWrite(LED_BUILTIN, HIGH);
        delay(100);
        digitalWrite(LED_BUILTIN, LOW);
        delay(100);
    }
}

void flash_led_hold()
{
    flash_led();
    digitalWrite(LED_BUILTIN, HIGH);
}
