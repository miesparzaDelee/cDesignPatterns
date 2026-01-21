#include "api_circle.h"
#include <stdio.h>

// --- Interface Implementations ---

static void draw(api_shape_t *self)
{
    api_circle_t * this = (api_circle_t *)self;
    printf("Drawing Circle: Radius=%d, Color=%X\n", 
           circle_getRadius(this->circle), this->super.base.color);
}

static float get_area(api_shape_t *self)
{
    api_circle_t * this = (api_circle_t *)self;
    return circle_getArea(this->circle);
}

static uint32_t get_perimeter(api_shape_t *self)
{
    // Perimeter (Circumference) = 2 * pi * r
    // Approximation for demo
    api_circle_t * this = (api_circle_t *)self;
    return (uint32_t)(2 * 3.14159f * (float)circle_getRadius(this->circle));
}

// --- VTable Definition ---
static const shape_vtable_t circle_vtable = {
    .draw = draw,
    .get_area = get_area,
    .get_perimeter = get_perimeter
};

// --- Initialization ---

void api_circle_init(api_circle_t *self, circle_config_t *circle_conf, shape_config_t *shape_conf)
{
    // 1. Init API Base
    api_shape_init(&self->super, shape_conf, &circle_vtable);

    // 2. Init internal object
    // Pass address of memory block
    self->circle = circle_init(&self->mem, circle_conf);
}
