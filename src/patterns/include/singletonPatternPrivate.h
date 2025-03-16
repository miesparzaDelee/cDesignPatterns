#ifndef SINGLETON_PATTERN_PRIVATE_H
#define SINGLETON_PATTERN_PRIVATE_H

#include <stdint.h>
#include "privatePattern.h"

struct _singletonModule 
{
uint32_t status;
hOpaqueObject_t hElement1;
struct privateObject_t element2;
hOpaqueObject_t hElement2;
uint8_t param1;
};

typedef struct _singletonModule* hSingleton;

hSingleton singPatt_getData();
#endif