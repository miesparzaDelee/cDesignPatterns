#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <stdint.h>

struct triangle;

typedef struct triangle * hTriangle_t;

#include "trianglePrivate.h"

typedef struct triangle
{
    const float area;
    
    _triangle_private_t _private;
} triangle_t;

typedef struct
{
    uint32_t base;
    uint32_t height;
} triangle_config_t;

void triangle_init(hTriangle_t self, triangle_config_t *config);

void triangle_updateDimensions(hTriangle_t self, uint32_t base, uint32_t height);

#endif // TRIANGLE_H
