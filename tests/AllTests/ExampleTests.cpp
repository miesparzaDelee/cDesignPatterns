#include <stdio.h>
#include <stdarg.h>
#include "CppUTest/TestHarness.h"

extern "C" {
    // #include "<test_module>"
    // other references
}


TEST_GROUP(TestsGroupName)
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

TEST(TestsGroupName, )
{    
    CHECK_TRUE(true);
}
