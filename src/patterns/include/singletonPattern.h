#ifndef SINGLETON_PATTERN_H
#define SINGLETON_PATTERN_H

#include <stdint.h>
#include "opaquePattern.h"

typedef struct
{
	uint8_t param;
	hOpaqueObject_t element;
}singletton_config_t;


uint32_t singPatt_Create(singletton_config_t* conf);

uint32_t singPatt_GetStatus();

uint32_t singPatt_ChangeStatus(uint32_t newStatus);

#endif