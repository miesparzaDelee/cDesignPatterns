#include "singletonPattern.h"
#include "singletonPatternPrivate.h"

static struct _singletonModule uniqueInstance;

uint32_t singPatt_Create(singletton_config_t* conf)
{
	uniqueInstance.hElement1 = conf->element;
	uniqueInstance.param1 = conf->param;
	uniqueInstance.hElement2 = &uniqueInstance.element2;
	privateObject_config_t privConf;
	privConf.parameter1 = 2;
	privConf.parameter2 = 0;
	uniqueInstance.status = privPatt_Init(uniqueInstance.hElement2, &privConf);
	return 0;
}

uint32_t singPatt_GetStatus()
{
	return uniqueInstance.status;
}

uint32_t singPatt_ChangeStatus(uint32_t newStatus)
{
	uniqueInstance.status = newStatus;
	return 0;
}


hSingleton singPatt_getData()
{
	return &uniqueInstance;
}