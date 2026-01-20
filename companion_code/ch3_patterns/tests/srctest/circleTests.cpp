#include "CppUTest/TestHarness.h"

extern "C" {
    #include "circle.h"
}

TEST_GROUP(Circle_OpaquePattern){ 
    void setup(){
        // add init 
    }

    void teardown(){
        // add deinit
    } 
};

TEST(Circle_OpaquePattern, demonstrates_OpaqueHandleUsage)
{
    // 1. Declare instances
    circle_memory_t small_circ = { }; // only for c++
    circle_memory_t big_circ = { };
    circle_config_t conf;
    
    // 2. Initialize with different states
    conf.radius = 5;

    hCircle_t hSmall = circle_init(&small_circ, &conf);
    
    conf.radius = 100;
    hCircle_t hBig = circle_init(&big_circ, &conf);

    // Test expected behavior
    CHECK(circle_getArea(hSmall) < circle_getArea(hBig));
}