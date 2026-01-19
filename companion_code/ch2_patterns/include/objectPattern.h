#ifndef OBJECT_PATTERN_H
#define OBJECT_PATTERN_H

#include <stdint.h>

// Object structure definition
typedef struct
{
	uint32_t variable; // Represents an operational variable
	uint32_t flags;    // Represents operational states or conditions
}object_t;

// Object configuration structure definition
typedef struct
{
	uint32_t parameter1;
	uint32_t parameter2;
}object_config_t;


// Init implies that module user has to allocate the object
// self implies that function will operate only on the passed element
uint32_t op_Init(object_t* self, object_config_t * conf);

uint32_t op_DeInit(object_t* self);

#endif