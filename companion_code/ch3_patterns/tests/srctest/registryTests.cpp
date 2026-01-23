#include "CppUTest/TestHarness.h"

extern "C" {
    #include "shape_registry.h"
    #include "rectangle.h"
    #include "shape.h"
}

TEST_GROUP(ShapeRegistry_SingletonPattern)
{
    shape_registry_memory_t registry_mem;
    shape_registry_config_t config;
    hShapeRegistry_t registry;
    
    void setup()
    {
        config.max_capacity = 8;
        registry = shapeRegistry_GetInstance(&registry_mem, &config);
    }
    
    void teardown()
    {
    }
};

TEST(ShapeRegistry_SingletonPattern, singleton_returns_non_null)
{
    CHECK_TRUE(registry != NULL);
}

TEST(ShapeRegistry_SingletonPattern, initial_count_is_zero)
{
    CHECK_EQUAL(0, shapeRegistry_GetCount(registry));
}

TEST(ShapeRegistry_SingletonPattern, register_shape_increases_count)
{
    rectangle_t rect = { };
    rect_config_t rect_config = { .width = 10, .height = 5 };
    shape_config_t shape_cfg = { .type = SHAPE_TYPE_RECTANGLE, .color = 0xFF0000, .visible = true };
    
    shape_init((shape_t*)&rect.base, &shape_cfg);
    rect_init(&rect, &rect_config);
    
    shapeRegistry_Register(registry, (shape_t*)&rect);
    CHECK_EQUAL(1, shapeRegistry_GetCount(registry));
    
    shape_t* retrieved = shapeRegistry_GetAtIndex(registry, 0);
    CHECK_EQUAL((shape_t*)&rect, retrieved);
}

TEST(ShapeRegistry_SingletonPattern, can_unregister_shape)
{
    rectangle_t rect = { };
    rect_config_t rect_config = { .width = 10, .height = 5 };
    shape_config_t shape_cfg = { .type = SHAPE_TYPE_RECTANGLE, .color = 0xFF0000, .visible = true };
    
    shape_init((shape_t*)&rect.base, &shape_cfg);
    rect_init(&rect, &rect_config);
    
    shapeRegistry_Register(registry, (shape_t*)&rect);
    CHECK_EQUAL(1, shapeRegistry_GetCount(registry));
    
    shapeRegistry_Unregister(registry, (shape_t*)&rect);
    CHECK_EQUAL(0, shapeRegistry_GetCount(registry));
}

TEST(ShapeRegistry_SingletonPattern, multiple_registrations)
{
    rectangle_t rect1 = { };
    rectangle_t rect2 = { };
    rect_config_t rect_config = { .width = 10, .height = 5 };
    shape_config_t shape_cfg = { .type = SHAPE_TYPE_RECTANGLE, .color = 0xFF0000, .visible = true };
    
    shape_init((shape_t*)&rect1.base, &shape_cfg);
    rect_init(&rect1, &rect_config);
    shape_init((shape_t*)&rect2.base, &shape_cfg);
    rect_init(&rect2, &rect_config);
    
    shapeRegistry_Register(registry, (shape_t*)&rect1);
    shapeRegistry_Register(registry, (shape_t*)&rect2);
    
    CHECK_EQUAL(2, shapeRegistry_GetCount(registry));
}

TEST(ShapeRegistry_SingletonPattern, returns_same_instance)
{
    shape_registry_memory_t registry2_mem;
    hShapeRegistry_t registry2 = shapeRegistry_GetInstance(&registry2_mem, NULL);
    
    CHECK_EQUAL(registry, registry2);
}