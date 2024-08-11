# Intro

Software para conectar el ESP32c3 + c1101 con Home Assistant y MQTT.

## Compiling

Keep in mind you have to create a file in "include/" called 'secret.h' with the SSID and PWD for the wifi.

## HA - Fan config

{ 
  "name": "Ceil Fan",
  "command_topic": "gluondev/habitacionfan/onoff", 
  "percentage_command_topic": "gluondev/habitacionfan/speed",
  "payload_on": "true", 
  "payload_off": "false", 
  "speed_range_min": 1,"speed_range_max": 5,
}
