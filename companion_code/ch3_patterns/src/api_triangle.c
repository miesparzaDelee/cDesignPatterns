#include "api_triangle.h"
#include <stdio.h>

// --- Interface Implementations ---

static void draw(api_shape_t *self)
{
    printf("Drawing Triangle: Color=%X\n", self->base.color);
}

static float get_area(api_shape_t *self)
{
    api_triangle_t * this = (api_triangle_t *)self;
    // Direct access to public const field
    return this->triangle.area;
}

static uint32_t get_perimeter(api_shape_t *self)
{
    // Dummy implementation as triangle module doesn't expose perimeter logic nicely yet
    (void)self;
    return 0;
}

// --- VTable Definition ---
static const shape_vtable_t triangle_vtable = {
    .draw = draw,
    .get_area = get_area,
    .get_perimeter = get_perimeter
};

// --- Initialization ---

void api_triangle_init(api_triangle_t *self, triangle_config_t *tri_conf, shape_config_t *shape_conf)
{
    // 1. Init API Base
    api_shape_init(&self->super, shape_conf, &triangle_vtable);

    // 2. Init internal object
    triangle_init(&self->triangle, tri_conf);
}
