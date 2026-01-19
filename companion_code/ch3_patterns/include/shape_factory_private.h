#ifndef SHAPE_FACTORY_PRIVATE_H
#define SHAPE_FACTORY_PRIVATE_H

#include "shape_factory.h"

#include "common.h"

struct shape_api {
	void (*draw)(hShape shape);
};

#endif // !SIMPLE_FACTORY_PATTERN_PRIVATE_H
