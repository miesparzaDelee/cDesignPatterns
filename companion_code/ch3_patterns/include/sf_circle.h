#ifndef CIRCLE_FACTORY_SQUARE_H
#define CIRCLE_FACTORY_SQUARE_H

#include "shape_factory.h"
#include "circle.h"

typedef struct {
	struct shape api;
	circle_memory_t shape;
}shape_circle;

void shape_circle_init(shape_circle* circle);

#endif
