#ifndef SINGLETON_PATTERN_H
#define SINGLETON_PATTERN_H

#include <stdint.h>
#include "opaquePattern.h"


typedef struct
{
	uint32_t status;
	uint32_t param;
	hOpaqueObject_t element1;
}singletonData_t;

typedef struct
{
	uint8_t param;
	hOpaqueObject_t element1;
}singletton_config_t;

singletonData_t * singPatt_Init(singletton_config_t* conf);

void singPatt_SetParam(int32_t param);

#endif