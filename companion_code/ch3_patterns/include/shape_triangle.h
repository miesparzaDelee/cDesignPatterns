#ifndef SHAPE_TRIANGLE_H
#define SHAPE_TRIANGLE_H

#include <stdint.h>

#include "triangle.h"
#include "shape.h"

// Derived shape: triangle + common shape base
typedef struct
{
   shape_t base;        // MUST be first (inheritance)
   triangle_t triangle; // Composition: reuse existing triangle object
} shape_triangle_t;

// Initialization: base + specific triangle initialization
void shapeTriangle_init(shape_triangle_t* self, triangle_config_t* config);

#endif // SHAPE_TRIANGLE_H