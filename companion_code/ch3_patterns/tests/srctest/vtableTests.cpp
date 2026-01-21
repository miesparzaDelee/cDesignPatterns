#include "CppUTest/TestHarness.h"
extern "C" {
#include "api_rectangle.h"
#include "api_circle.h"
#include "api_triangle.h"
}

// Test Group for VTable Pattern (Interface)
TEST_GROUP(VTablePattern)
{
    void setup()
    {
    }

    void teardown()
    {
    }
};

// Test 1: Verify VTable Polymorphism
TEST(VTablePattern, Polymorphism)
{
    // 1. Create specific API objects
    api_rectangle_t r = {};
    rect_config_t r_conf = {10, 20};
    shape_config_t r_shape = {SHAPE_TYPE_RECTANGLE, 0xFF0000, true};
    api_rectangle_init(&r, &r_conf, &r_shape);

    api_circle_t c = {};
    circle_config_t c_conf = {5};
    shape_config_t c_shape = {SHAPE_TYPE_CIRCLE, 0x00FF00, true};
    api_circle_init(&c, &c_conf, &c_shape);

    api_triangle_t t = {};
    triangle_config_t t_conf = {10, 20};
    shape_config_t t_shape = {SHAPE_TYPE_TRIANGLE, 0x0000FF, true};
    api_triangle_init(&t, &t_conf, &t_shape);

    // 2. Use generic API pointer (Polymorphism)
    // In this pattern, we cast to api_shape_t*
    api_shape_t * shapes[3];
    shapes[0] = (api_shape_t*)&r;
    shapes[1] = (api_shape_t*)&c;
    shapes[2] = (api_shape_t*)&t;

    // 3. Verify Get Area via VTable
    // Rectangle: 10 * 20 = 200
    DOUBLES_EQUAL(200.0, shape_get_area(shapes[0]), 0.1);
    
    // Circle: pi * 5^2 = 78.53
    DOUBLES_EQUAL(78.5398, shape_get_area(shapes[1]), 0.1);

    // Triangle: 0.5 * 10 * 20 = 100
    DOUBLES_EQUAL(100.0, shape_get_area(shapes[2]), 0.1);

    // 4. Verify Get Perimeter
    // Rectangle: 2 * (10 + 20) = 60
    LONGS_EQUAL(60, shape_get_perimeter(shapes[0]));
    
    // Circle: 2 * pi * 5 = 31.41
    LONGS_EQUAL(31, shape_get_perimeter(shapes[1]));

    // Triangle: Not implemented (returns 0)
    LONGS_EQUAL(0, shape_get_perimeter(shapes[2]));
}
