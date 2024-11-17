#include "privatePattern.h"

#define PRIVATE_PATTER_FLAG_1 0x1
#define PRIVATE_PATTER_FLAG_2 0x2
#define PRIVATE_PATTER_FLAG_3 0x4

uint32_t privPatt_Init(hPrivateObject me, privateObject_config_t* conf)
{
	if (conf->parameter1 > 0)
	{
		me->privateData.flags = 1;
		me->privateData.flags |= PRIVATE_PATTER_FLAG_1;
	}
	if (conf->parameter2 > 0)
	{
		me->privateData.flags |= PRIVATE_PATTER_FLAG_3;
	}
	return 0;
}

uint32_t privPatt_DeInit(hPrivateObject me)
{
	// Uninit all
	return 0;
}
