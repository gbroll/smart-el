#include <Arduino.h>
#include "WiFi.h"
#include <PubSubClient.h>
#include "../secrets.h"
#include "led.h"
#include "telegram.h"

#define RX_PIN 16


class Timeinfo
{
public:
    unsigned long loopLastRun = 0;
    unsigned long loopIntervalMilliSeconds = 5000;
};

void WiFiConnectLoop(int timeOutSeconds);
void MQTTConnectLoop(PubSubClient &client, int timeOutSeconds);

LED led = LED(LED_BUILTIN);
WiFiClient wifiClient;
PubSubClient MQTTClient(wifiClient);
Timeinfo timings;

byte MQTT_SERVER[4] = SECRET_MQTTSERVER;
int MQTT_PORT = SECRET_MQTTPORT;

void setup()
{ 
    
    digitalWrite(LED_BUILTIN, LOW);
    
    Serial.begin(115200, SERIAL_8N1, 1, 3);
    Serial.print("LED_BUILTIN is at PIN: ");
    Serial.println(LED_BUILTIN);

    Serial2.begin(115200, SERIAL_8N1, 16, 17, false);

    WiFiConnectLoop(30);
    led.flash();

    IPAddress MQTTServer(MQTT_SERVER);
    MQTTClient.setServer(MQTTServer, MQTT_PORT);
    MQTTConnectLoop(MQTTClient, 30);

       
}

void loop() 
{
    
    Telegram telegram;
    telegram.ReadFromSerial(Serial2);

    /* 
    unsigned long now = millis();
    if ((now-timings.loopLastRun) > timings.loopIntervalMilliSeconds)
    {
        timings.loopLastRun = now;
        WiFiConnectLoop(30);
        MQTTConnectLoop(MQTTClient, 30);
        MQTTClient.loop();


        Serial.println("hej hej från serial");
        if (Serial2.available() > 0)
        {
            led.flash();
            String input = Serial2.readString();
            MQTTClient.publish("outTopic", input.c_str());
        }

 
    } */

}

