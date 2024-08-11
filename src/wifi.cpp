#include "wifi_local.h"

#include <WiFi.h>
#include <WiFiClient.h>

#include "secret.h"

void wifi_init()
{
    Serial.println("Iniciando Wifi");
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PWD);

    while( WiFi.status() != WL_CONNECTED )
    {
        delay(200);
        Serial.print(".");
    }
    Serial.println("");

    Serial.print("Wifi conectado, IP: ");
    Serial.println(WiFi.localIP());
}