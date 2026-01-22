#ifndef API_TRIANGLE_H
#define API_TRIANGLE_H

#include "api_shape.h"
#include "triangle.h"

typedef struct {
    api_shape_t super;      // Inherits api_shape_t
    triangle_t triangle;    // Composition
} api_triangle_t;

void api_triangle_init(api_triangle_t *self, triangle_config_t *tri_conf, shape_config_t * shape_conf);

#endif // API_TRIANGLE_H
