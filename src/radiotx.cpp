#include "radiotx.h"

#include <RadioLib.h>

constexpr uint32_t SYNC_PULSE = 600;
constexpr uint32_t SYNC_WAIT  = 7700;
constexpr uint32_t SHORT_PULSE = 350;
constexpr uint32_t SHORT_WAIT  = 350;
constexpr uint32_t LONG_PULSE  = 1000;
constexpr uint32_t LONG_WAIT   = 1000;
constexpr uint32_t END_WAIT    = 7700;

constexpr float RADIO_FREQ = 433.92f;

constexpr uint8_t RADIO_SCK  = 0;
constexpr uint8_t RADIO_MISO = 1;
constexpr uint8_t RADIO_MOSI = 21;
constexpr uint8_t CS   = 3;
constexpr uint8_t GDO0 = 4;
constexpr uint8_t GDO2 = 2;

/**
 * CS Pin: 3
 * GDO0  : 4
 * RST   : No Conectado
 * GDO2  : 2
 */
CC1101 radio = new Module(CS, GDO0, RADIOLIB_NC, GDO2);

void radio_init()
{
    SPI.begin(RADIO_SCK, RADIO_MISO, RADIO_MOSI);
    int state = radio.begin(RADIO_FREQ);
    if ( state == RADIOLIB_ERR_NONE )
    {
        Serial.println("Radio iniciada");
    }
    else
    {
        Serial.print("Radio fallida:");
        Serial.print(state);
        while(1);
    }

    radio.setOOK(true);
    radio.setBitRate(10.0f);
}

inline void pulse(uint32_t time)
{
    digitalWrite(GDO0, HIGH);
    delayMicroseconds(time);
    digitalWrite(GDO0, LOW);
}

void radio_send(uint8_t* data, uint8_t len)
{
    pinMode(GDO0, OUTPUT);
    radio.transmitDirect();
    digitalWrite(GDO2, LOW);
    delay(10);

    // Primer pulso
    pulse(SYNC_PULSE);
    delayMicroseconds(SYNC_WAIT);

    for( uint8_t repes = 0; repes < 5; repes++)
    {
        for(uint8_t i = 0; i < len; i++)
        {
            pulse(SHORT_PULSE);   
            for( uint8_t j = 0; j < data[i]; j++)
            {
                delayMicroseconds(SHORT_WAIT);
                pulse(LONG_PULSE);
            }
            delayMicroseconds(LONG_WAIT);
        }
        delayMicroseconds(END_WAIT - LONG_WAIT);
    }

    radio.finishTransmit();
}
