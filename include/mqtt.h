#ifndef __MQTT_H__
#define __MQTT_H__

#include <Arduino.h>
#include <stdint.h>

void mqtt_init();

void mqtt_connect();

void mqtt_sub(String topic);
void mqtt_pub(String topic, uint8_t * data);

void mqtt_loop();


#endif //__MQTT_H__