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

// Allocation functions
size_t oop_size(void);
hOpaqueObject oop_new();
void oop_free(hOpaqueObject* self);

// init and deinit
int oop_Init(hOpaqueObject self, opaqueObject_config_t* conf);
int oop_Deinit(hOpaqueObject self);


// methods that operate on an opaque
void oop_setParameter(hOpaqueObject self, uint32_t parameter);
uint32_t oop_getFlags(hOpaqueObject self);
uint32_t oop_getParameters(hOpaqueObject self);
#endif