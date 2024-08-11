#ifndef __FAN_CONTROL__
#define __FAN_CONTROL__

#include <stdint.h>

/**
 * @brief Set Fan speed.
 * @param speed 0- stop, 1-5 set on and set speed.
 */
void setFan(uint8_t speed);

#endif //__FAN_CONTROL__