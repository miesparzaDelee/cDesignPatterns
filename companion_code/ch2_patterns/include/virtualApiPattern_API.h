#ifndef VIRTUAL_API_PATTERN_API_H
#define VIRTUAL_API_PATTERN_API_H

#include <stdint.h>

struct commVirtualApi
{
	int (*write)(const struct commVirtualApi** handle, const uint8_t* data, size_t size);
	int (*read)(const struct commVirtualApi** handle, uint8_t* data, size_t size);
};

#endif