#ifndef PRIVATE_PATTERN_H
#define PRIVATE_PATTERN_H

#include <stdint.h>

struct privateStruct;

typedef struct privateStruct * hPrivateObject_t;

#include "privatePatternPrivate.h"

typedef struct privateStruct
{
	uint32_t publicStatus;
	_privateObject_t privateData;
};

typedef struct
{
	uint32_t parameter1;
	uint32_t parameter2;
}privateObject_config_t;


uint32_t privPatt_Init(hPrivateObject_t self, privateObject_config_t* conf);

uint32_t privPatt_DeInit(hPrivateObject_t self);

#endif
