#include "shape_rectangle.h"
#include <stddef.h>

void shapeRect_init(shape_rectangle_t * self, rect_config_t * r_conf, shape_config_t * s_conf)
{
    if (self == NULL || r_conf == NULL || s_conf == NULL) {
        return;
    }
    
    // 1. Initialize the base class
    shape_init(&self->base, s_conf);

    // 2. Initialize the specific part (Rectangle)
    rect_init(&self->rect, r_conf);

}