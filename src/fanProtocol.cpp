#include "fanControl.h"
#include "radiotx.h"

uint8_t fanControlData[6][18] =
{
    {1,1,0,1,1,2,0,1, 2,0,0,3,2,0,0,0,1,0}, // Off
    {1,1,1,0,2,0,2,0, 2,0,0,3,2,0,0,0,1,0}, // Speed 1
    {1,1,0,2,1,0,2,0, 2,0,0,3,2,0,0,0,1,0},
    {1,1,0,1,2,0,2,0, 2,0,0,3,2,0,0,0,1,0},
    {1,0,2,1,1,0,2,0, 2,0,0,3,2,0,0,0,1,0},
    {1,0,2,0,2,0,2,0, 2,0,0,3,2,0,0,0,1,0}, // Speed 5
};

void setFan(uint8_t speed)
{
    if(speed > 5)
    {
        return;
    }

    // Send to radio...
    radio_send(fanControlData[speed], 18);
}