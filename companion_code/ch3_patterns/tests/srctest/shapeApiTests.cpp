#include "CppUTest/TestHarness.h"

extern "C" {
   #include "shape_api.h"
   #include "shape_circle.h"
   #include "shape_rectangle.h"
}


TEST_GROUP(ShapeAPI_UseCases){ 
   void setup(){
       // No global setup needed
   }

   void teardown(){
       // No cleanup needed for static allocation
   } 
};

TEST(ShapeAPI_UseCases, render_multiple_shapes_on_screen)
{
   /*
    * USE CASE: Graphics rendering system
    * 
    * Scenario: You have a collection of different shapes that need to be
    * rendered on a display. The rendering loop doesn't care what type of
    * shape it is - it just needs to draw each one and calculate total area
    * for memory/optimization purposes.
    * 
    * This demonstrates the POWER of polymorphism - same code works for
    * any shape type!
    */
   
   // ===== 1. CREATE DIFFERENT SHAPES =====
   
   // Circle: radius = 5
   scircle_memory_t circle_mem;
   scircle_config_t circle_cfg;
   circle_cfg.radius = 5;
   hsCircle_t circle = scircle_init(&circle_mem, &circle_cfg);
   
   // Rectangle: 10 x 20
   srectangle_t rect = {};
   srect_config_t rect_cfg;
   rect_cfg.width = 10;
   rect_cfg.height = 20;
   srect_init(&rect, &rect_cfg);
   
   // ===== 2. STORE IN POLYMORPHIC ARRAY =====
   // This is the key: different types, same interface!
   hShape shapes[2];
   shapes[0] = (hShape)circle;
   shapes[1] = (hShape)&rect;
   
   // ===== 3. PROCESS ALL SHAPES UNIFORMLY =====
   // Notice: NO if/else or switch to check type!
   // The vtable handles dispatching automatically
   
   float total_area = 0.0f;
   uint32_t total_perimeter = 0;
   
   for (int i = 0; i < 2; i++) {
       // Draw the shape (polymorphic call)
       shape_draw(shapes[i]);
       
       // Calculate area (polymorphic call)
       float area = shape_get_area(shapes[i]);
       
       // Calculate perimeter (polymorphic call)
       uint32_t perimeter = shape_get_perimeter(shapes[i]);
       
       // Accumulate totals
       total_area += area;
       total_perimeter += perimeter;
   }
   
   // ===== 4. VERIFY RESULTS =====
   
   // Circle area = π * r² = 3.14159 * 5 * 5 ≈ 78.54
   float expected_circle_area = 78.54f;
   
   // Rectangle area = width * height = 10 * 20 = 200
   float expected_rect_area = 200.0f;
   
   // Total area
   float expected_total_area = expected_circle_area + expected_rect_area;
   
   // Circle perimeter = 2 * π * r = 2 * 3.14159 * 5 ≈ 31
   uint32_t expected_circle_perimeter = 31;
   
   // Rectangle perimeter = 2 * (width + height) = 2 * (10 + 20) = 60
   uint32_t expected_rect_perimeter = 60;
   
   // Total perimeter
   uint32_t expected_total_perimeter = expected_circle_perimeter + expected_rect_perimeter;
   
   // Verify individual shapes work correctly via polymorphic interface
   DOUBLES_EQUAL(expected_circle_area, shape_get_area(shapes[0]), 0.01);
   DOUBLES_EQUAL(expected_rect_area, shape_get_area(shapes[1]), 0.01);
   
   // Verify totals
   DOUBLES_EQUAL(expected_total_area, total_area, 0.01);
   LONGS_EQUAL(expected_total_perimeter, total_perimeter);
   
   // Verify we processed both shapes
   CHECK(total_area > 0.0f);
   CHECK(total_perimeter > 0);
}

// TEST_GROUP(ShapeAPI){ 
//    // Memory for shapes
//    circle_memory_t circle_mem;
//    rectangle_t rect = {};
   
//    // Shape handles
//    hCircle_t circle;
//    hShape circle_shape;
//    hShape rect_shape;
   
//    void setup(){
//        // Initialize circle with radius 10
//        circle_config_t circle_cfg;
//        circle_cfg.radius = 10;
//        circle = circle_init(&circle_mem, &circle_cfg);
//        circle_shape = (hShape)circle;
       
//        // Initialize rectangle with width 20, height 30
//        rect_config_t rect_cfg;
//        rect_cfg.width = 20; rect_cfg.height = 30;
//        rect_init(&rect, &rect_cfg);
//        rect_shape = (hShape)&rect;
//    }

//    void teardown(){
//        // Cleanup if needed (for static allocation, usually nothing)
//    } 
// };

// TEST(ShapeAPI, test_circle_area)
// {
//    // Test circle area calculation
//    // Area = π * r^2 = 3.14159 * 10 * 10 ≈ 314.159
//    float area = shape_get_area(circle_shape);
   
//    DOUBLES_EQUAL(314.159, area, 0.01);  // Allow small tolerance
// }

// TEST(ShapeAPI, test_rectangle_area)
// {
//    // Test rectangle area calculation
//    // Area = width * height = 20 * 30 = 600
//    float area = shape_get_area(rect_shape);
   
//    DOUBLES_EQUAL(600.0, area, 0.01);
// }

// TEST(ShapeAPI, test_polymorphic_area)
// {
//    // Test that both shapes work through same interface
//    float circle_area = shape_get_area(circle_shape);
//    float rect_area = shape_get_area(rect_shape);
   
//    // Verify they're different (polymorphism works)
//    CHECK(circle_area != rect_area);
   
//    // Verify circle area is correct
//    DOUBLES_EQUAL(314.159, circle_area, 0.01);
   
//    // Verify rectangle area is correct
//    DOUBLES_EQUAL(600.0, rect_area, 0.01);
// }

// TEST(ShapeAPI, test_null_shape)
// {
//    // Test NULL safety
//    float area = shape_get_area(NULL);
   
//    // Should return 0.0 or handle gracefully
//    DOUBLES_EQUAL(0.0, area, 0.01);
// }

// TEST(ShapeAPI, test_multiple_shapes_in_array)
// {
//    // Test array of polymorphic shapes
//    hShape shapes[2];
//    shapes[0] = circle_shape;
//    shapes[1] = rect_shape;
   
//    // Calculate total area
//    float total_area = 0.0f;
//    for (int i = 0; i < 2; i++) {
//        total_area += shape_get_area(shapes[i]);
//    }
   
//    // Total = 314.159 + 600 = 914.159
//    DOUBLES_EQUAL(914.159, total_area, 0.01);
// }
