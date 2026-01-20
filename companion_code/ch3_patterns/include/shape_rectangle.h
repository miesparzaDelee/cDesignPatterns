#ifndef SHAPE_RECTANGLE_H
#define SHAPE_RECTANGLE_H

#include <stdint.h>

#include "rectangle.h"
#include "shape.h"

// Object structure definition
typedef struct {
   shape_t base;
   rectangle_t rect;
} shape_rectangle_t;

void shapeRect_init(shape_rectangle_t * self, rect_config_t * conf);

#endif // RECTANGLE_H
