#include <stdio.h>
#include <stdarg.h>
#include "CppUTest/TestHarness.h"

extern "C" {
    #include "opaquePattern.h"
    // other references
}

TEST_GROUP(OpaquePattern)
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

TEST(OpaquePattern, Init_StackAllocation)
{
    hOpaqueObject_t opaque1 = (hOpaqueObject_t)alloca(oop_size());
    opaqueObject_config_t opaque1_conf;
    opaque1_conf.parameter1 = 1;
    opaque1_conf.parameter2 = 0;

    uint32_t r = oop_Init(opaque1, &opaque1_conf);

    CHECK_EQUAL(0, r);
}


TEST(OpaquePattern, Init_DynamicAllocation)
{
    hOpaqueObject_t opaque1 = oop_new();
    opaqueObject_config_t opaque1_conf;
    opaque1_conf.parameter1 = 1;
    opaque1_conf.parameter2 = 0;

    uint32_t r = oop_Init(opaque1, &opaque1_conf);

    CHECK_EQUAL(0, r);

    oop_free(&opaque1);    
    POINTERS_EQUAL(NULL, opaque1);
}

