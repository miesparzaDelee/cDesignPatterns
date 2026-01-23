#include "CppUTest/TestHarness.h"

extern "C" {
    #include "factory_shape.h"
}

TEST_GROUP(FactoryPattern)
{
    void setup()
    {
    }

    void teardown()
    {
    }
};



// Test 1: Verify Factory Pattern Polymorphism
TEST(FactoryPattern, Polymorphism)
{
    // 1. Create specific API objects
    api_rectangle_t rect = {};
    api_circle_t circle = {};
    api_triangle_t triangle = {};

    api_shape_t* shapes[3];
    
    // 3. Create shapes using factory
    factory_config_t conf;
    conf.shape.rect.width = 10;
    conf.shape.rect.height = 20;
    conf.shape_conf.type = SHAPE_TYPE_RECTANGLE;
    conf.shape_conf.color = 0xFF0000;
    conf.shape_conf.visible = true;
    shapes[0] = factory_shape_create((api_shape_t*)&rect, &conf);
    
    
    conf.shape.circle.radius = 5;
    conf.shape_conf.type = SHAPE_TYPE_CIRCLE;
    conf.shape_conf.color = 0x00FF00;
    conf.shape_conf.visible = true;
    shapes[1] = factory_shape_create((api_shape_t*)&circle, &conf);

    conf.shape.triangle.base = 10;
    conf.shape.triangle.height = 20;
    conf.shape_conf.type = SHAPE_TYPE_TRIANGLE;
    conf.shape_conf.color = 0x0000FF;
    conf.shape_conf.visible = true;
    shapes[2] = factory_shape_create((api_shape_t*)&triangle, &conf);


    // 4. Use generic API pointers (Polymorphism)
    CHECK(shapes[0] != NULL);
    CHECK(shapes[1] != NULL);
    CHECK(shapes[2] != NULL);

    // 5. Verify Get Area via VTable
    // Rectangle: 10 * 20 = 200
    DOUBLES_EQUAL(200.0, shape_get_area(shapes[0]), 0.1);

    // Circle: pi * 5^2 = 78.53
    DOUBLES_EQUAL(78.5398, shape_get_area(shapes[1]), 0.1);

    // Triangle: 0.5 * 10 * 20 = 100
    DOUBLES_EQUAL(100.0, shape_get_area(shapes[2]), 0.1);
}


