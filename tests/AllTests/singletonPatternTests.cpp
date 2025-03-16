#include <stdio.h>
#include <stdarg.h>
#include "CppUTest/TestHarness.h"

extern "C" {
#include "singletonPattern.h"
#include "singletonPatternPrivate.h"
    // other references
}

TEST_GROUP(SingletonPattern)
{
    void setup()
    {
        // Run before every test.
    }
    void teardown()
    {
        // Run after every test.
    }
};

hOpaqueObject_t getConfiguredObject()
{
    hOpaqueObject_t ret = oop_new();
    opaqueObject_config_t ret_conf;
    ret_conf.parameter1 = 1;
    ret_conf.parameter2 = 0;
    uint32_t r = oop_Init(ret, &ret_conf);
    return ret;
}

TEST(SingletonPattern, Init)
{
    singletton_config_t conf;
    conf.element = getConfiguredObject();
    conf.param = 2;

    uint32_t r = singPatt_Create(&conf);
 
    hSingleton internalData = singPatt_getData();
    CHECK_EQUAL(0, r);
    BYTES_EQUAL(conf.param, internalData->param1);
}

