#include "WiFi.h"
#include "../secrets.h"

void WiFiConnectLoop(int timeOutSeconds = 30)
{
    int status = WiFi.status();
    if (status == WL_CONNECTED) return;

    while (status != WL_CONNECTED)
    {
        Serial.print("Attempting to connect to SSID: ");
        Serial.println(SECRET_SSID);
        status = WiFi.begin(SECRET_SSID, SECRET_PASS);
        delay(5000);
    }

    Serial.println("Connected to WiFi, local IP is: ");
    Serial.println(WiFi.localIP());
}
