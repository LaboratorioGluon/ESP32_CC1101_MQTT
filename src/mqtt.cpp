#include "mqtt.h"
#include <stdint.h>

#include <WiFiClient.h>
#include <PubSubClient.h>

#include "fanControl.h"

/* Configuracion MQTT */
constexpr char* MQTT_BROKER_ADDR = "192.168.1.157";
constexpr uint16_t MQTT_PORT = 1883;
constexpr char* MQTT_CLIENT_NAME = "FAN_MQTT";

/* Configuracion HA */
constexpr const char* DISCOVERY_FAN_TOPIC = "homeassistant/fan/habitacion/config";
constexpr const char* DISCOVERY_FAN = "{\"name\":\"CeilFan\",\"command_topic\":\"gluondev/habitacionfan/onoff\",\"percentage_command_topic\":\"gluondev/habitacionfan/speed\",\"payload_on\":\"true\",\"payload_off\":\"false\",\"speed_range_min\":1,\"speed_range_max\":5}";

typedef struct{
    String topic;
    void (*f)(String);
} topicToFunc;

void parseFan(String payload)
{
    uint32_t value;
    if (String("true").equals(payload))
    {
        value = 1;
    }
    else if (String("false").equals(payload))
    {
        value = 0;
    }
    else
    {
        value = atoi(payload.c_str());
    }
    
    Serial.print("Setting Fan to: ");
    Serial.println(value);
    
    setFan(value);

}

topicToFunc funcs[] = 
{
    {.topic = "gluondev/habitacionfan/onoff", .f=parseFan },
    {.topic = "gluondev/habitacionfan/speed", .f=parseFan }
};

WiFiClient espClient;
PubSubClient mqttClient(espClient);

void OnMqttMessageReceived(char * topic, byte* payload, unsigned int len);

void mqtt_init()
{
    mqttClient.setBufferSize(512);
    mqttClient.setServer(MQTT_BROKER_ADDR, MQTT_PORT);
    mqttClient.setCallback(OnMqttMessageReceived);
}

void mqtt_connect()
{
    while(!mqttClient.connected()){
        Serial.println("Conectando MQTT...");
        if( !mqttClient.connect(MQTT_CLIENT_NAME) )
        {
            Serial.println("Fallo conexion MQTT");
        }
        else
        {
            for( uint8_t i = 0; i < sizeof(funcs)/sizeof(topicToFunc); i++)
            {
                Serial.print("Sub to:"); Serial.println(funcs[i].topic);
                mqtt_sub(funcs[i].topic);
            }

        }  
    }
    Serial.println("MQTT Connected!");

    mqtt_pub(DISCOVERY_FAN_TOPIC, (unsigned char*)DISCOVERY_FAN);
}

void mqtt_loop()
{
    if(!mqttClient.connected())
    {
        mqtt_connect();
    }

    mqttClient.loop();
}

void mqtt_sub(String topic)
{
    mqttClient.subscribe(topic.c_str());
}

void mqtt_pub(String topic, uint8_t * data)
{
    mqttClient.publish(topic.c_str(), (const char*) data);
}


String content;
void OnMqttMessageReceived(char * topic, byte* payload, unsigned int len)
{
    Serial.print("MQTT Received on '");
    Serial.print(topic);
    Serial.println("'");

    content = "";
    for( uint32_t i = 0; i < len; i++ )
    {
        content.concat((char)payload[i]);
    }
    Serial.println(content);

    for( uint8_t i = 0; i < sizeof(funcs)/sizeof(topicToFunc); i++)
    {
        if(funcs[i].topic.equals(topic))
        {
            funcs[i].f( String((char*)payload, len) );
        }
    }
}