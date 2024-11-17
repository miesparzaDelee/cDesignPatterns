#ifndef SIMPLE_FACTORY_PATTERN_SQUARE_H
#define SIMPLE_FACTORY_PATTERN_SQUARE_H

#include "simpleFactoryPattern.h"

typedef struct {
	struct shape api;
	float width, height;
}shape_rectangle;

void shape_square_init(shape_rectangle* circle);

#endif
