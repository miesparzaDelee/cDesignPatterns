#include "objectPattern.h"

#include <string.h>

#define OBJECT_PATTERN_FLAG_1 0x1
#define OBJECT_PATTERN_FLAG_2 0x2
#define OBJECT_PATTERN_FLAG_3 0x4

uint32_t op_Init(object_t* self, object_config_t* conf)
{
	op_Deinit(self);
	if (conf->parameter1 > 0)
	{
		self->variable = 1;
		self->flags |= OBJECT_PATTERN_FLAG_1;
	}
	if (conf->parameter2 > 0)
	{
		self->flags |= OBJECT_PATTERN_FLAG_3;
	}
	return 0;
}

uint32_t op_Deinit(object_t* self)
{
	memset(self, 0, sizeof(object_t));
	return 0;
}