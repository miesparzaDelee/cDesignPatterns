#ifndef PRIVATE_PATTERN_H
#define PRIVATE_PATTERN_H

// Useful for multiple instances modules

#include <stdint.h>


struct privateObject_t;
typedef struct privateObject_t* hPrivateObject;

#include "privatePatternPrivate.h"

struct privateObject_t
{
	uint32_t publicStatus;
	_privateObject_t privateData;
};

typedef struct
{
	uint32_t parameter1;
	uint32_t parameter2;
}privateObject_config_t;


uint32_t privPatt_Init(hPrivateObject me, privateObject_config_t* conf);

uint32_t privPatt_DeInit(hPrivateObject me);

#endif
