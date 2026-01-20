#include "CppUTest/TestHarness.h"

extern "C" {
    #include "rectangle.h"
}

TEST_GROUP(Rectangle_ObjectPattern){ 
    void setup(){
        // add init 
    }

    void teardown(){
        // add deinit
    } 
};

TEST(Rectangle_ObjectPattern, demonstrates_MultipleIndependentInstances)
{
    // 1. Declare instances
    rectangle_t small_rect = { }; // only for c++
    rectangle_t big_rect = { };
    rect_config_t conf;
    
    // 2. Initialize with different states
    conf.height = 5;
    conf.width  = 10;
    rect_init(&small_rect, &conf);

    conf.height = 100;
    conf.width  = 200;
    rect_init(&big_rect, &conf);

    // Test expected behavior
    LONGS_EQUAL(5*10, small_rect.area);
    LONGS_EQUAL(100*200, big_rect.area);
}
