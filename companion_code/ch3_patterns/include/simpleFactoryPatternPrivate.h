#ifndef SIMPLE_FACTORY_PATTERN_PRIVATE_H
#define SIMPLE_FACTORY_PATTERN_PRIVATE_H

#include "simpleFactoryPattern.h"

#include "common.h"



struct shape_api {
	void (*draw)(hShape shape);
};

#endif // !SIMPLE_FACTORY_PATTERN_PRIVATE_H
