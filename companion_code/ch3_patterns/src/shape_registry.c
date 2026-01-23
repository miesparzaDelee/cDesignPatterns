#include "shape_registry.h"
#include <string.h>

static void update_biggest_area(void);
static void update_biggest_perimeter(void);

typedef struct {
    uint32_t is_new_shape;
    float cached_max_area;
    uint32_t cached_max_perimeter;
    uint8_t cache_valid;
}_shape_registry_data_t; // private state

static shape_registry_data_t g_registry_data = {0};
static _shape_registry_data_t priv_registry_data = {0};

const shape_registry_data_t * shapeRegistry_Init()
{
    memset(&g_registry_data, 0, sizeof(shape_registry_data_t));   
    memset(&priv_registry_data, 0, sizeof(_shape_registry_data_t));
    priv_registry_data.cache_valid = 0;
    return &g_registry_data;
}

void shapeRegistry_Tasks()
{
    // Only update if new shapes have been registered/unregistered
    if (priv_registry_data.is_new_shape) {
        update_biggest_area();
        update_biggest_perimeter();
        priv_registry_data.is_new_shape = 0;
    }
}

bool shapeRegistry_Register(api_shape_t * api_shape)
{
    if (g_registry_data.count >= MAX_SHAPES) {
        return false;
    }

    g_registry_data.api_shapes[g_registry_data.count] = api_shape;
    g_registry_data.count++;
    priv_registry_data.is_new_shape = 1;
    priv_registry_data.cache_valid = 0;
    return true;
}

bool shapeRegistry_Unregister(api_shape_t * api_shape)
{
    if (g_registry_data.count == 0) {
        return false;
    }

    for (uint32_t i = 0; i < g_registry_data.count; i++) {
        if (g_registry_data.api_shapes[i] == api_shape) {
            for (uint32_t j = i; j < g_registry_data.count - 1; j++) {
                g_registry_data.api_shapes[j] = g_registry_data.api_shapes[j + 1];
            }
            g_registry_data.count--;
            priv_registry_data.is_new_shape = 1;
            priv_registry_data.cache_valid = 0;
            return true;
        }
    }

    return false;
}

/* Static helper functions for updating statistics */

static void update_biggest_area(void)
{
    if (g_registry_data.count == 0) {
        g_registry_data.biggestArea = NULL;
        priv_registry_data.cached_max_area = 0.0f;
        return;
    }
    
    float max_area = 0.0f;
    api_shape_t *shape_with_max_area = NULL;
    
    for (uint32_t i = 0; i < g_registry_data.count; i++) {
        float area = shape_get_area(g_registry_data.api_shapes[i]);
        if (area > max_area) {
            max_area = area;
            shape_with_max_area = g_registry_data.api_shapes[i];
        }
    }
    
    g_registry_data.biggestArea = shape_with_max_area;
    priv_registry_data.cached_max_area = max_area;
}

static void update_biggest_perimeter(void)
{
    if (g_registry_data.count == 0) {
        g_registry_data.biggestPerimeter = NULL;
        priv_registry_data.cached_max_perimeter = 0;
        return;
    }
    
    uint32_t max_perimeter = 0;
    api_shape_t *shape_with_max_perimeter = NULL;
    
    for (uint32_t i = 0; i < g_registry_data.count; i++) {
        uint32_t perimeter = shape_get_perimeter(g_registry_data.api_shapes[i]);
        if (perimeter > max_perimeter) {
            max_perimeter = perimeter;
            shape_with_max_perimeter = g_registry_data.api_shapes[i];
        }
    }
    
    g_registry_data.biggestPerimeter = shape_with_max_perimeter;
    priv_registry_data.cached_max_perimeter = max_perimeter;
}
