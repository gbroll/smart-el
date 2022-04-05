#include "WiFi.h"
#include "../secrets.h"

char* ssid = SECRET_SSID;
char* pwd = SECRET_PASS;

void WiFiConnectLoop(int timeOutSeconds = 30)
{
    int status = WiFi.status();
    if (status == WL_CONNECTED) return;

    while (status != WL_CONNECTED)
    {
        Serial.print("Attempting to connect to SSID: ");
        Serial.println(ssid);
        status = WiFi.begin(ssid, pwd);
        delay(5000);
    }

    Serial.println("Connected to WiFi, local IP is: ");
    Serial.println(WiFi.localIP());
}
