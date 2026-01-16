#ifndef OPAQUE_PATTERN_H
#define OPAQUE_PATTERN_H

#include <stdint.h>

struct opaqueStruct;

typedef struct opaqueStruct * hOpaqueObject_t;

typedef struct
{
	uint32_t parameter1;
	uint32_t parameter2;
}opaqueObject_config_t;

// Allocation functions
size_t oop_size(void);
hOpaqueObject_t oop_new();
void oop_free(hOpaqueObject_t* self);

// init and deinit
int oop_Init(hOpaqueObject_t self, opaqueObject_config_t* conf);
int oop_DeInit(hOpaqueObject_t self);


// methods that operate on an opaque
void oop_setParameter(hOpaqueObject_t self, uint32_t parameter);
uint32_t oop_getFlags(hOpaqueObject_t self);
uint32_t oop_getParameters(hOpaqueObject_t self);
#endif