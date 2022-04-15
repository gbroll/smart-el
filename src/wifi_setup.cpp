#include "WiFi.h"
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

#include "../secrets.h"
#include "led.h"

char* ssid = SECRET_SSID;
char* pwd = SECRET_PASS;

void WiFiConnectLoop(LED led)
{

    int status = WiFi.status();
    if (status == WL_CONNECTED) return;

    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); //disable brownout detector when starting wifi 

    while (status != WL_CONNECTED)
    {
        delay(5000);
        led.flash();
        WiFi.mode(WIFI_STA);
        Serial.print("Attempting to connect to SSID: ");
        Serial.println(ssid);
        status = WiFi.begin(ssid, pwd);
    }

    Serial.println("Connected to WiFi, local IP is: ");
    Serial.println(WiFi.localIP());
    delay(2000);
    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 1); //enable brownout detector when connected
}
