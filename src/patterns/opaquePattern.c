#include "opaquePattern.h"

#include <stdlib.h>

#define OPAQUE_PATTERN_FLAG_1 0x1
#define OPAQUE_PATTERN_FLAG_2 0x2
#define OPAQUE_PATTERN_FLAG_3 0x4


struct opaqueObject_t
{
	uint32_t variable;
	uint32_t flags;
};


int oop_Init(hOpaqueObject me, opaqueObject_config_t* conf)
{
	//op_Deinit(me);
	if (conf->parameter1 > 0)
	{
		me->variable = 1;
		me->flags |= OPAQUE_PATTERN_FLAG_1;
	}
	if (conf->parameter2 > 0)
	{
		me->flags |= OPAQUE_PATTERN_FLAG_3;
	}
	return 0;
}
//
//int oop_Deinit(hOpaque me)
//{
//	return 0;
//}
//
size_t oop_size(void)
{
	return sizeof(struct opaqueObject_t);
}

hOpaqueObject oop_new()
{
	return malloc(oop_size());
}

void oop_free(hOpaqueObject * me)
{
	free(*me);
	*me = NULL;
}

//
//// methods that operate on an opaque
//void oop_setParameter(hOpaque me, uint32_t parameter)
//{
//	return 0;
//}
//
//uint32_t oop_getFlags(hOpaque me)
//{
//	return 0;
//}
//
//uint32_t oop_getParameters(hOpaque me)
//{
//	return 0;
//}