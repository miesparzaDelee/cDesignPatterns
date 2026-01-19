#ifndef SIMPLE_FACTORY_PATTERN_SQUARE_H
#define SIMPLE_FACTORY_PATTERN_SQUARE_H

#include "shape_factory.h"
#include "rectangle.h"

typedef struct {
	struct shape api;
	rectangle_t shape;
}shape_rectangle;

void shape_square_init(shape_rectangle* circle);

#endif
