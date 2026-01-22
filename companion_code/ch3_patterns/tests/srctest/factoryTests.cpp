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

    // 2. Create factory configs
    factory_config_t conf_rect;
    conf_rect.type = SHAPE_TYPE_RECTANGLE;
    conf_rect.shape.rect.width = 10;
    conf_rect.shape.rect.height = 20;
    conf_rect.shape_conf.type = SHAPE_TYPE_RECTANGLE;
    conf_rect.shape_conf.color = 0xFF0000;
    conf_rect.shape_conf.visible = true;

    factory_config_t conf_circ;
    conf_circ.type = SHAPE_TYPE_CIRCLE;
    conf_circ.shape.circle.radius = 5;
    conf_circ.shape_conf.type = SHAPE_TYPE_CIRCLE;
    conf_circ.shape_conf.color = 0x00FF00;
    conf_circ.shape_conf.visible = true;

    factory_config_t conf_tri;
    conf_tri.type = SHAPE_TYPE_TRIANGLE;
    conf_tri.shape.triangle.base = 10;
    conf_tri.shape.triangle.height = 20;
    conf_tri.shape_conf.type = SHAPE_TYPE_TRIANGLE;
    conf_tri.shape_conf.color = 0x0000FF;
    conf_tri.shape_conf.visible = true;

    // 3. Create shapes using factory
    api_shape_t* shapes[3];
    shapes[0] = factory_shape_create((api_shape_t*)&rect, &conf_rect);
    shapes[1] = factory_shape_create((api_shape_t*)&circle, &conf_circ);
    shapes[2] = factory_shape_create((api_shape_t*)&triangle, &conf_tri);

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


