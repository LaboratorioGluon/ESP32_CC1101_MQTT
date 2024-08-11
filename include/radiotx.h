#ifndef __RADIOTX_H__
#define __RADIOTX_H__

#include <stdint.h>

void radio_init();

void radio_send(uint8_t* data, uint8_t len);

#endif //__RADIOTX_H__