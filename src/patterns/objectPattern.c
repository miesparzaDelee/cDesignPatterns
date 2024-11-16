#include "objectPattern.h"

#include <string.h>

#define FLAG_1 0x1
#define FLAG_2 0x2
#define FLAG_3 0x4

uint32_t op_Init(object_t* me, object_config_t* conf)
{
	op_Deinit(me);
	memset(me, 0, sizeof(object_t));
	if (conf->parameter1 > 0)
	{
		me->variable = 1;
		me->flags |= FLAG_1;
	}
	if (conf->parameter2 > 0)
	{
		me->flags |= FLAG_3;
	}
	return 0;
}

uint32_t op_Deinit(object_t* me)
{
	memset(me, 0, sizeof(object_t));
	return 0;
}