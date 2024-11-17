#include <stdio.h>
#include <stdarg.h>
#include "CppUTest/TestHarness.h"

extern "C" {
    #include "privatePattern.h"
    // other references
}

TEST_GROUP(PrivatePattern)
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

TEST(PrivatePattern, Init)
{
    privateObject_t private1;
    hPrivateObject privHandle = &private1;
    privateObject_config_t private1_conf;
    private1_conf.parameter1 = 1;
    private1_conf.parameter2 = 0;

    uint32_t r = privPatt_Init(privHandle, &private1_conf);

    CHECK_EQUAL(0, r);
}

