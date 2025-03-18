#include <stdio.h>
#include <stdarg.h>
#include "CppUTest/TestHarness.h"

extern "C" {
#include "singletonPattern.h"
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
    conf.element1 = getConfiguredObject();
    conf.param = 2;

    singletonData_t* data = singPatt_Init(&conf);
 
    //LONGS_EQUAL(conf.param, data->param);
}

