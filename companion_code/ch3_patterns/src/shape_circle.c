#include "shape_circle.h"
#include <stddef.h>

void shapeCircle_init(shape_circle_t * self, circle_config_t *c_conf, shape_config_t *s_conf)
{
    if (self == NULL || c_conf == NULL || s_conf == NULL) {
        return;
    }

    // 1. Initialize the base class
    shape_init(&self->base, s_conf);

    // 2. Initialize the specific part (Circle)
    self->circle = circle_init(&self->raw_memory, c_conf);
}