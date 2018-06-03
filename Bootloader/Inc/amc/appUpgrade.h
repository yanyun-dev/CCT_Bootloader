#ifndef __APP_UPGRADE_H
#define __APP_UPGRADE_H

#include "stm32f1xx_hal.h"
#include "constant_config.h"

	void flash_program(uint32_t * pData, uint32_t size);

#endif