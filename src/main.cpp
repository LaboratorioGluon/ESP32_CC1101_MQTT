#include <Arduino.h>

#include "wifi_local.h"
#include "mqtt.h"
#include "radiotx.h"

void setup() {
    Serial.begin(115200);
    delay(1000);
    // Init radio
    radio_init();

    // Init Wifi
    wifi_init();

    // Init MQTT
    mqtt_init();

}

void loop() {
    mqtt_loop();

    // Check MQTT from Home Assistant
    // while( mqttReceive(...) == 0);

    // Parse MQTT message 
    // fan_execMqtt(...);

}
