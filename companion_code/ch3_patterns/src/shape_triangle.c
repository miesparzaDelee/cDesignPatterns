#include "shape_triangle.h"
#include <stddef.h>

void shapeTriangle_init(shape_triangle_t* self, triangle_config_t* t_conf, shape_config_t* s_conf)
{
    if (self == NULL || t_conf == NULL || s_conf == NULL)
    {
        return;
    }

    // 1. Initialize the Base
    shape_init(&self->base, s_conf);

    // 2. Initialize the Derived (specific)
    triangle_init(&self->triangle, t_conf);
}
