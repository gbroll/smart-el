#include <Arduino.h>
#include "WiFi.h"
#include <PubSubClient.h>
#include "../secrets.h"

char* mqtt_user = MQTT_USER;
char* mqtt_pass = MQTT_PASS;

void MQTTConnectLoop(PubSubClient &client, int timeOutSeconds)
{
    if (client.connected()) return;

    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");
        // Create a random client ID
        String clientId = "ESP32client-";
        clientId += String(random(0xffff), HEX);
        // Attempt to connect
        if (client.connect(clientId.c_str(), mqtt_user, mqtt_pass))
        {
            Serial.println("connected");
            // Once connected, publish an announcement...
            client.publish("outTopic", "ESP32 connected");
            client.subscribe("inTopic");
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}
