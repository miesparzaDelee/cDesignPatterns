#ifndef SIMPLE_FACTORY_PATTERN_CIRCLE_H
#define SIMPLE_FACTORY_PATTERN_CIRCLE_H

#include "simpleFactoryPattern.h"

typedef struct {
	struct shape api;
	float radius;
}shape_circle;

void shape_circle_init(shape_circle* circle);

#endif
