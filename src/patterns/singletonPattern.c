#include "singletonPattern.h"

singletonData_t uniqueInstance;

singletonData_t* singPatt_Init(singletton_config_t* conf)
{
	uniqueInstance.param = conf->param;
	uniqueInstance.element1 = conf->element1;
	return &uniqueInstance;
}

void singPatt_SetParam(int32_t param)
{
	uniqueInstance.param = param;
}