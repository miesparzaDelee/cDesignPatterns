#ifndef OBJECT_PATTERN_H
#define OBJECT_PATTERN_H

// Useful for multiple instances modules

#include <stdint.h>

typedef struct
{
	uint32_t variable;
	uint32_t flags;
}object_t;

typedef struct
{
	uint32_t parameter1;
	uint32_t parameter2;
}object_config_t;


// Init implies that module user has to allocate the object
// me/self implies that function will operate only on the passed element
uint32_t op_Init(object_t* me, object_config_t * conf);

uint32_t op_Deinit(object_t* me);

#endif