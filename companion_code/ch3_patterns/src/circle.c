#include "circle.h"
#include <stddef.h> // For NULL

// Internal constant
#define PI 3.14159f

// This is completely hidden from the user size, the size must be manually set in CIRCLE_SIZE
struct circle {
    uint32_t radius;
    float    area;     // Dependent state: area = PI * r^2
};

hCircle_t circle_init(circle_memory_t *mem, circle_config_t *config)
{
    if (sizeof(struct circle) > sizeof(circle_memory_t))
    {
        return NULL; // Error: Header size constant is too small!
    }
    // CASTING MAGIC:    // We treat the raw memory block provided by the user as our specific struct.
    struct circle *self = (struct circle *)mem;

    // Initialize state
    self->radius = config->radius;
    self->area = (float)(self->radius * self->radius) * PI;

    // Return the pointer cast as the opaque handle type
    return (hCircle_t)self;
}

void circle_updateRadius(hCircle_t self, uint32_t radius) {
    // 1. Update the primary state
    self->radius = radius;
    
    // 2. AUTOMATICALLY update the dependent state.
    self->area = (float)(radius * radius) * PI;
}

uint32_t circle_getRadius(hCircle_t self) {
    return self->radius;
}

float circle_getArea(hCircle_t self) {
    return self->area;
}