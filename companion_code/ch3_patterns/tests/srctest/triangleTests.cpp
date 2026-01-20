#include "CppUTest/TestHarness.h"

extern "C" {
    #include "triangle.h"
}

TEST_GROUP(Triangle_PrivatePattern){ 
    void setup(){
        // add init 
    }

    void teardown(){
        // add deinit
    } 
};

TEST(Triangle_PrivatePattern, demonstrates_PrivateFieldAccess)
{
    // 1. Declare instances
    triangle_t small_tri = { };
    triangle_t big_tri = { };
    triangle_config_t conf;
    
    // 2. Initialize with different states
    conf.base = 10;
    conf.height = 5;
    triangle_init(&small_tri, &conf);

    conf.base = 100;
    conf.height = 50;
    triangle_init(&big_tri, &conf);

    // 3. Test public area is readable
    DOUBLES_EQUAL(25.0f, small_tri.area, 0.1f);
    DOUBLES_EQUAL(2500.0f, big_tri.area, 0.1f);
    
    // 4. Use private function to verify internal state
    _triangle_private_t* small_private = triangle_getPrivateInfo(&small_tri);
    LONGS_EQUAL(10, small_private->base);
    LONGS_EQUAL(5, small_private->height);
}
