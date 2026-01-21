#include "api_rectangle.h"
#include <stdio.h> // For printf in draw

// --- Interface Implementations ---

static void draw(api_shape_t *self)
{
    // Downcast to access specific data
    api_rectangle_t * this = (api_rectangle_t *)self;
    printf("Drawing Rectangle: Width=%d, Height=%d, Color=%X\n", 
           this->rect.width, this->rect.height, this->super.base.color);
}

static float get_area(api_shape_t *self)
{
    api_rectangle_t * this = (api_rectangle_t *)self;
    return (float)rect_get_area(&this->rect);
}

static uint32_t get_perimeter(api_shape_t *self)
{
    api_rectangle_t * this = (api_rectangle_t *)self;
    return 2 * (this->rect.width + this->rect.height);
}

// --- VTable Definition ---
// Defined specific to this class
static const shape_vtable_t rectangle_vtable = {
    .draw = draw,
    .get_area = get_area,
    .get_perimeter = get_perimeter
};

// --- Initialization ---

void api_rectangle_init(api_rectangle_t *self, rect_config_t *rect_conf, shape_config_t *shape_conf)
{
    // 1. Initialize the API Base (sets vptr)
    api_shape_init(&self->super, shape_conf, &rectangle_vtable);

    // 2. Initialize the internal object
    rect_init(&self->rect, rect_conf);
}
