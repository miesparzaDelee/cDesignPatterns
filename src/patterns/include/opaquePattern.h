#ifndef OPAQUE_PATTERN_H
#define OPAQUE_PATTERN_H

#include <stdint.h>

struct opaqueObject_t;
typedef struct opaqueObject_t* hOpaqueObject;

typedef struct
{
	uint32_t parameter1;
	uint32_t parameter2;
}opaqueObject_config_t;

// init and deinit
int oop_Init(hOpaqueObject me, opaqueObject_config_t* conf);
int oop_Deinit(hOpaqueObject me);

// Allocation functions
size_t oop_size(void);
hOpaqueObject oop_new();
void oop_free(hOpaqueObject * me);

// methods that operate on an opaque
void oop_setParameter(hOpaqueObject me, uint32_t parameter);
uint32_t oop_getFlags(hOpaqueObject me);
uint32_t oop_getParameters(hOpaqueObject me);
#endif