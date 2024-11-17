#ifndef SIMPLE_FACTORY_PATTERN_PRIVATE_H
#define SIMPLE_FACTORY_PATTERN_PRIVATE_H

#include "simpleFactoryPattern.h"

#include <stdlib.h>
#include <string.h>


#define CONTAINER_OF(ptr, type, member) \
    ((type *)((char *)(ptr) - offsetof(type, member)))

struct shape_api {
	void (*draw)(hShape shape);
};

#endif // !SIMPLE_FACTORY_PATTERN_PRIVATE_H
