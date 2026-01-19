#include "CppUTest/TestHarness.h"

extern "C" {
    #include "rectangle.h"
}

TEST_GROUP(rectangle_NoInit_Group){ 
    void setup(){
        // add init 
    }

    void teardown(){
        // add deinit
    } 
};

TEST(rectangle_NoInit_Group, module_multipleInstancesExample)
{
    // 1. Declare instances
    rectangle_t small_rect;
    rectangle_t big_rect;
    rect_config_t conf;
    
    // 2. Initialize with different states
    conf.height = 5;
    conf.width  = 10;
    rect_init(&small_rect, &conf);

    conf.height = 100;
    conf.width  = 200;
    rect_init(&big_rect, &conf);

    // 3. Operate on them independently
    uint32_t area1 = rect_get_area(&small_rect);
    uint32_t area2 = rect_get_area(&big_rect);

    // Test expected behavior
    LONGS_EQUAL(5*10, area1);
    LONGS_EQUAL(100*200, area2);
}
