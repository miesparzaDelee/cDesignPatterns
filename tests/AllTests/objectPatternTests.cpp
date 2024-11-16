#include <stdio.h>
#include <stdarg.h>
#include "CppUTest/TestHarness.h"

extern "C" {
    #include "objectPattern.h"
    // other references
}


TEST_GROUP(ObjectPattern)
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

TEST(ObjectPattern, Init)
{
    object_t object1;
    object_config_t ob1_conf;
    ob1_conf.parameter1 = 1;
    ob1_conf.parameter2 = 0;

    uint32_t r = op_Init(&object1, &ob1_conf);

    CHECK_EQUAL(0, r);
}