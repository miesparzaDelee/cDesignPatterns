#ifndef API_RECTANGLE_H
#define API_RECTANGLE_H

#include "api_shape.h"
#include "rectangle.h"

typedef struct {
    api_shape_t super;  // Inherits api_shape_t (and thus shape_t)
    rectangle_t rect;   // Composition of the core logic
} api_rectangle_t;

// Initialization
// We need config for shape (base), config for rect, and we set the vtable internally
void api_rectangle_init(api_rectangle_t *self, rect_config_t *rect_conf, shape_config_t *shape_conf);

#endif // API_RECTANGLE_H
