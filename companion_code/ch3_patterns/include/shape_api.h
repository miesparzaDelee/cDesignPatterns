#ifndef SHAPE_API_H
#define SHAPE_API_H

#include <stdint.h>

// The vtable - defines the contract all shapes must follow
typedef struct shape_api {
   void (*draw)(void* self);
   float (*get_area)(void* self);
   uint32_t (*get_perimeter)(void* self);
} shape_api_t;

// Base shape structure - all shapes must have this as first member
typedef struct shape {
   const shape_api_t* api;  // Points to the vtable
} shape_t;

// Opaque handle for users
typedef shape_t* hShape;

// Polymorphic functions (these dispatch through vtable)
void shape_draw(hShape self);
float shape_get_area(hShape self);
uint32_t shape_get_perimeter(hShape self);

#endif // SHAPE_API_H
