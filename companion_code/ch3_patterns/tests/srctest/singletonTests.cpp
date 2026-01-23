#include "CppUTest/TestHarness.h"
#include <stdlib.h>

extern "C" {
    #include "shape_registry.h"
    #include "api_rectangle.h"
    #include "api_circle.h"
    #include "api_triangle.h"
}

TEST_GROUP(SingletonPattern)
{
    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(SingletonPattern, usage_example)
{
    // 1. Initialize the registry singleton
    const shape_registry_data_t *registry = shapeRegistry_Init();

    // 2. Create different shapes with varying sizes
    api_rectangle_t small_rect = {};
    rect_config_t small_rect_conf = {5, 10};
    shape_config_t small_rect_shape = {SHAPE_TYPE_RECTANGLE, 0xFF0000, true};
    api_rectangle_init(&small_rect, &small_rect_conf, &small_rect_shape);

    api_rectangle_t large_rect = {};
    rect_config_t large_rect_conf = {50, 100};
    shape_config_t large_rect_shape = {SHAPE_TYPE_RECTANGLE, 0x00FF00, true};
    api_rectangle_init(&large_rect, &large_rect_conf, &large_rect_shape);

    api_circle_t circle = {};
    circle_config_t circle_conf = {20};
    shape_config_t circle_shape = {SHAPE_TYPE_CIRCLE, 0x0000FF, true};
    api_circle_init(&circle, &circle_conf, &circle_shape);

    api_triangle_t triangle = {};
    triangle_config_t triangle_conf = {30, 40};
    shape_config_t triangle_shape = {SHAPE_TYPE_TRIANGLE, 0xFFFF00, true};
    api_triangle_init(&triangle, &triangle_conf, &triangle_shape);

    // 3. Register shapes in the singleton
    shapeRegistry_Register((api_shape_t*)&small_rect);
    shapeRegistry_Register((api_shape_t*)&large_rect);
    shapeRegistry_Register((api_shape_t*)&circle);
    shapeRegistry_Register((api_shape_t*)&triangle);

    // 4. Update statistics (triggered when new shapes are registered)
    shapeRegistry_Tasks();

    // 5. Verify biggest area
    // Large rectangle: 50 * 100 = 5000
    // Circle: pi * 20^2 = 1256.6
    // Triangle: 0.5 * 30 * 40 = 600
    // Small rectangle: 5 * 10 = 50
    CHECK_TRUE(registry->biggestArea == (api_shape_t*)&large_rect);
    DOUBLES_EQUAL(5000.0, shape_get_area(registry->biggestArea), 0.1);

    // 6. Verify biggest perimeter
    // Large rectangle: 2 * (50 + 100) = 300
    // Circle: 2 * pi * 20 = 125.6
    // Triangle: Not implemented (returns 0)
    // Small rectangle: 2 * (5 + 10) = 30
    CHECK_TRUE(registry->biggestPerimeter == (api_shape_t*)&large_rect);
    LONGS_EQUAL(300, shape_get_perimeter(registry->biggestPerimeter));

    // 7. Unregister the largest shape
    shapeRegistry_Unregister((api_shape_t*)&large_rect);

    // 8. Update statistics again
    shapeRegistry_Tasks();

    // 9. Verify new biggest area (Circle: 1256.6)
    CHECK_TRUE(registry->biggestArea == (api_shape_t*)&circle);
    DOUBLES_EQUAL(1256.6, shape_get_area(registry->biggestArea), 0.1);
}

TEST(SingletonPattern, init_returns_valid_pointer)
{
    const shape_registry_data_t *registry = shapeRegistry_Init();
    CHECK_TRUE(registry != NULL);
}

TEST(SingletonPattern, init_resets_registry_state)
{
    const shape_registry_data_t *registry = shapeRegistry_Init();
    CHECK_EQUAL(0, registry->count);
    CHECK_TRUE(registry->biggestArea == NULL);
    CHECK_TRUE(registry->biggestPerimeter == NULL);
}

TEST(SingletonPattern, register_increases_count)
{
    api_rectangle_t rect = {};
    rect_config_t rect_conf = {10, 20};
    shape_config_t shape_conf = {SHAPE_TYPE_RECTANGLE, 0xFF0000, true};
    api_rectangle_init(&rect, &rect_conf, &shape_conf);

    const shape_registry_data_t *registry = shapeRegistry_Init();
    shapeRegistry_Register((api_shape_t*)&rect);

    CHECK_EQUAL(1, registry->count);
}

TEST(SingletonPattern, unregister_decreases_count)
{
    api_rectangle_t rect = {};
    rect_config_t rect_conf = {10, 20};
    shape_config_t shape_conf = {SHAPE_TYPE_RECTANGLE, 0xFF0000, true};
    api_rectangle_init(&rect, &rect_conf, &shape_conf);

    const shape_registry_data_t * registry = shapeRegistry_Init();
    shapeRegistry_Register((api_shape_t*)&rect);
    shapeRegistry_Unregister((api_shape_t*)&rect);

    CHECK_EQUAL(0, registry->count);
}

TEST(SingletonPattern, register_returns_false_when_full)
{
    api_rectangle_t * rects = (api_rectangle_t*)malloc(MAX_SHAPES + 1 * sizeof(api_rectangle_t));
    shapeRegistry_Init();

    rect_config_t rect_conf = {10, 20};
    shape_config_t shape_conf = {SHAPE_TYPE_RECTANGLE, 0xFF0000, true};

    for (int i = 0; i < MAX_SHAPES; i++) {
        api_rectangle_t rect = rects[i];
        api_rectangle_init(&rect, &rect_conf, &shape_conf);
        CHECK_TRUE(shapeRegistry_Register((api_shape_t*)&rect));
    }
    free(rects);
    api_rectangle_t extra_rect = rects[10];
    api_rectangle_init(&extra_rect, &rect_conf, &shape_conf);
    CHECK_FALSE(shapeRegistry_Register((api_shape_t*)&extra_rect));
}

TEST(SingletonPattern, unregister_nonexistent_returns_false)
{
    api_rectangle_t rect = {};
    rect_config_t rect_conf = {10, 20};
    shape_config_t shape_conf = {SHAPE_TYPE_RECTANGLE, 0xFF0000, true};
    api_rectangle_init(&rect, &rect_conf, &shape_conf);

    shapeRegistry_Init();
    CHECK_FALSE(shapeRegistry_Unregister((api_shape_t*)&rect));
}

TEST(SingletonPattern, tasks_only_updates_when_new_shape_registered)
{
    api_rectangle_t rect1 = {};
    rect_config_t rect_conf1 = {10, 20};
    shape_config_t shape_conf1 = {SHAPE_TYPE_RECTANGLE, 0xFF0000, true};
    api_rectangle_init(&rect1, &rect_conf1, &shape_conf1);

    api_rectangle_t rect2 = {};
    rect_config_t rect_conf2 = {30, 40};
    shape_config_t shape_conf2 = {SHAPE_TYPE_RECTANGLE, 0x00FF00, true};
    api_rectangle_init(&rect2, &rect_conf2, &shape_conf2);

    const shape_registry_data_t *registry = shapeRegistry_Init();
    shapeRegistry_Register((api_shape_t*)&rect1);
    shapeRegistry_Tasks();

    CHECK_TRUE(registry->biggestArea == (api_shape_t*)&rect1);

    shapeRegistry_Register((api_shape_t*)&rect2);
    shapeRegistry_Tasks();

    CHECK_TRUE(registry->biggestArea == (api_shape_t*)&rect2);
}

TEST(SingletonPattern, empty_registry_has_null_biggest)
{
    const shape_registry_data_t *registry = shapeRegistry_Init();
    shapeRegistry_Tasks();

    CHECK_TRUE(registry->biggestArea == NULL);
    CHECK_TRUE(registry->biggestPerimeter == NULL);
}
