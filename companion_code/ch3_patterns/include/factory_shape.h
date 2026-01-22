// factory_shape.h - solo dependencias públicas
#ifndef FACTORY_SHAPE_H
#define FACTORY_SHAPE_H

#include "api_rectangle.h"
#include "api_circle.h"
#include "api_triangle.h"

typedef struct {
    shape_type_t type;
    union {
        rect_config_t rect;
        circle_config_t circle;
        triangle_config_t triangle;
    } shape;
    shape_config_t shape_conf;
} factory_config_t;

api_shape_t* factory_shape_create(api_shape_t * shape, factory_config_t *config);

#endif