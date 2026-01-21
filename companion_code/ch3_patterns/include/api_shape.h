#ifndef API_SHAPE_H
#define API_SHAPE_H

#include "shape.h"

// Forward declaration
struct api_shape;

// 1. VTable definition
typedef struct {
   void (*draw)(struct api_shape *self);
   float (*get_area)(struct api_shape *self);
   uint32_t (*get_perimeter)(struct api_shape *self);
} shape_vtable_t;

// 2. Base API structure (Inherits shape_t)
typedef struct api_shape {
   shape_t base;                // Inherits type, color, visible
   const shape_vtable_t *vptr;  // Pointer to the VTable
} api_shape_t;

// 3. Initialization
void api_shape_init(api_shape_t *self, shape_config_t *config, const shape_vtable_t *vptr);

// 4. Polymorphic API Wrapper functions
void shape_draw(api_shape_t *self);
float shape_get_area(api_shape_t *self);
uint32_t shape_get_perimeter(api_shape_t *self);

#endif // API_SHAPE_H
