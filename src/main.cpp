#include <Arduino.h>
#include "WiFi.h"
#include <PubSubClient.h>
#include "../secrets.h"
#include "led.h"
#include "telegram.h"
#include <map>

#define RX_PIN 16




void WiFiConnectLoop(LED led);
void MQTTConnectLoop(PubSubClient &client, int timeOutSeconds);

LED led = LED(LED_BUILTIN);
WiFiClient wifiClient;
PubSubClient MQTTClient(wifiClient);

byte MQTT_SERVER[4] = SECRET_MQTTSERVER;
int MQTT_PORT = SECRET_MQTTPORT;

void setup()
{ 
    
    

    digitalWrite(LED_BUILTIN, HIGH);
    
    //Serial.begin(115200, SERIAL_8N1, 1, 3);
    Serial.begin(115200);
    uint32_t freq = getCpuFrequencyMhz();
    Serial.print("CPU Freq at ");
    Serial.print(freq);
    setCpuFrequencyMhz(80);
    freq = getCpuFrequencyMhz();
    Serial.print("CPU Freq at ");
    Serial.print(freq);


    Serial.print("LED_BUILTIN is at PIN: ");
    Serial.println(LED_BUILTIN);

    Serial2.begin(115200, SERIAL_8N1, 16, 17, false);
    Serial2.flush();

    WiFiConnectLoop(led);
    led.flashAndHold();

    IPAddress MQTTServer(MQTT_SERVER);
    MQTTClient.setServer(MQTTServer, MQTT_PORT);
    MQTTConnectLoop(MQTTClient, 30);

       
}

void loop() 
{
    
    Telegram telegram;
    Serial.println(telegram.isCompleted());
    delay(1000);
    telegram.ReadFromSerial(Serial2);
    telegram.PublishToMQTT(MQTTClient, "outTopic", "1.2.2.2");
    
}

