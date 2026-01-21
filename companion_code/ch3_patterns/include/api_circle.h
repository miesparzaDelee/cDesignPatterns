#ifndef API_CIRCLE_H
#define API_CIRCLE_H

#include "api_shape.h"
#include "circle.h"

typedef struct {
    api_shape_t super;      // Inherits api_shape_t
    circle_memory_t mem;    // Memory for opaque circle
    hCircle_t circle;       // Usage handle
} api_circle_t;

void api_circle_init(api_circle_t *self, circle_config_t *circle_conf, shape_config_t *shape_conf);

#endif // API_CIRCLE_H
