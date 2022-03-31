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
void connect_wifi();
void connect_mqtt();

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

    Serial.println("Connected to WiFi, local IP is: ");
    Serial.println(WiFi.localIP());
    flash_led_hold();

    WiFiClient wifiClient;
    PubSubClient MQTTClient(wifiClient);

    IPAddress MQTTServer(SECRET_MQTTSERVER);
    MQTTClient.setServer(MQTTServer, SECRET_MQTTPORT);
    while (!MQTTClient.connected())
    {
        Serial.print("Attempting MQTT connection...");
        // Create a random client ID
        String clientId = "ESP32client-";
        clientId += String(random(0xffff), HEX);
        // Attempt to connect
        if (MQTTClient.connect(clientId.c_str()))
        {
            Serial.println("connected");
            flash_led_hold();
            // Once connected, publish an announcement...
            MQTTClient.publish("outTopic", "ESP32 connected");
            // ... and resubscribe
            MQTTClient.subscribe("inTopic");
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(MQTTClient.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
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
