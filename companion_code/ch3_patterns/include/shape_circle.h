#ifndef SHAPE_CIRCLE_H
#define SHAPE_CIRCLE_H

#include <stdint.h>
#include <stdbool.h>

#include "circle.h"
#include "shape.h"

typedef struct{
    shape_t base;
    circle_memory_t raw_memory;
    hCircle_t circle;
}shape_circle_t;

void shapeCircle_init(shape_circle_t * self, circle_config_t *c_conf, shape_config_t *s_conf);
    
#endif // SHAPE_CIRCLE_H