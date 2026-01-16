#include "opaquePattern.h"

#include <stdlib.h>

#define OPAQUE_PATTERN_FLAG_1 0x1
#define OPAQUE_PATTERN_FLAG_2 0x2
#define OPAQUE_PATTERN_FLAG_3 0x4


struct opaqueStruct
{
	uint32_t variable;
	uint32_t flags;
};


int oop_Init(hOpaqueObject_t self, opaqueObject_config_t* conf)
{
	//op_Deinit(me);
	if (conf->parameter1 > 0)
	{
		self->variable = 1;
		self->flags |= OPAQUE_PATTERN_FLAG_1;
	}
	if (conf->parameter2 > 0)
	{
		self->flags |= OPAQUE_PATTERN_FLAG_3;
	}
	return 0;
}

int oop_DeInit(hOpaqueObject_t self)
{
	return 0;
}

size_t oop_size(void)
{
	return sizeof(struct opaqueStruct);
}

hOpaqueObject_t oop_new()
{
	return malloc(oop_size());
}

void oop_free(hOpaqueObject_t * self)
{
	free(*self);
	*self = NULL;
}


// methods that operate on an opaque
void oop_setParameter(hOpaqueObject_t self, uint32_t parameter)
{
	return 0;
}

uint32_t oop_getFlags(hOpaqueObject_t self)
{
	return 0;
}

uint32_t oop_getParameters(hOpaqueObject_t self)
{
	return 0;
}