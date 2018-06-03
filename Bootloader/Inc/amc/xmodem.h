#ifndef __XMODEM_H
#define __XMODEM_H

#include "stm32f1xx_hal.h"

int32_t xmodemReceive(uint8_t *dest, int32_t destsz);

#endif