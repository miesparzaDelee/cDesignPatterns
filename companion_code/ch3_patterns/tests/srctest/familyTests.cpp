#include "CppUTest/TestHarness.h"  

extern "C" {
    #include "shape_rectangle.h"  
    #include "shape_circle.h"  
    #include "shape_triangle.h"  
}


// Test Group for Family Pattern (Inheritance)  
TEST_GROUP(FamilyPattern)  
{  
    void setup()  
    {  
    }  
  
    void teardown()  
    {  
    }  
};  
  
// Test 4: Polymorphism Example (Handling indistinctly)  
TEST(FamilyPattern, PolymorphismExample)  
{  
    // 1. Create instances  
    shape_rectangle_t r = {};
    shape_config_t r_shape_conf = {SHAPE_TYPE_RECTANGLE, 1, true};
    rect_config_t r_conf = {10, 20};  
    shapeRect_init(&r, &r_conf, &r_shape_conf);  
  
    shape_circle_t c ={};  
    shape_config_t c_shape_conf = {SHAPE_TYPE_CIRCLE, 2, true};
    circle_config_t c_conf = {5};  
    shapeCircle_init(&c, &c_conf, &c_shape_conf);  
  
    shape_triangle_t t ={};  
    triangle_config_t t_conf = {10, 20};  
    shape_config_t t_shape_conf = {SHAPE_TYPE_TRIANGLE, 3, true};
    shapeTriangle_init(&t, &t_conf, &t_shape_conf);  
  
    // 2. Treat them as generic shapes  
    shape_t * shapes[3];  
    shapes[0] = (shape_t*)&r;  
    shapes[1] = (shape_t*)&c;  
    shapes[2] = (shape_t*)&t;  
  
    // 3. Iterate and verify type  
    LONGS_EQUAL(SHAPE_TYPE_RECTANGLE, shapes[0]->type);  
    LONGS_EQUAL(SHAPE_TYPE_CIRCLE, shapes[1]->type);  
    LONGS_EQUAL(SHAPE_TYPE_TRIANGLE, shapes[2]->type);  
  
    // Verify colors  
    LONGS_EQUAL(1, shapes[0]->color);  
    LONGS_EQUAL(2, shapes[1]->color);  
    LONGS_EQUAL(3, shapes[2]->color);  
}  
