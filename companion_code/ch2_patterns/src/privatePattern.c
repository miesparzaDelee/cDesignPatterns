#include "privatePattern.h"

#define PRIVATE_PATTERN_FLAG_1 0x1
#define PRIVATE_PATTERN_FLAG_2 0x2
#define PRIVATE_PATTERN_FLAG_3 0x4

uint32_t privPatt_Init(hPrivateObject_t self, privateObject_config_t* conf)
{
	if (conf->parameter1 > 0)
	{
		self->privateData.flags = 1;
		self->privateData.flags |= PRIVATE_PATTERN_FLAG_1;
	}
	if (conf->parameter2 > 0)
	{
		self->privateData.flags |= PRIVATE_PATTERN_FLAG_3;
	}
	return 0;
}

uint32_t privPatt_InitLarge(hPrivateObject_t self, privateObject_config_t* conf)
{
	_privateObject_t* _self = (_privateObject_t*)&self->privateData;
	if (conf->parameter1 > 0)
	{
		_self->flags = 1;
		_self->flags |= PRIVATE_PATTERN_FLAG_1;
	}
	if (conf->parameter2 > 0)
	{
		_self->flags |= PRIVATE_PATTERN_FLAG_3;
	}
	return 0;
}

uint32_t privPatt_DeInit(hPrivateObject_t self)
{
	// Uninit all
	return 0;
}
