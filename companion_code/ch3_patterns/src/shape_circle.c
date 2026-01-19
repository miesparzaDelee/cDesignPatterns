#include "shape_circle.h"

#include "shape_api.h"

#include <stddef.h> // For NULL
#include <stdio.h>

// Internal constant
#define PI 3.14159f

static void draw(void * self);
static float get_area(void * self);
static uint32_t get_perimeter(void * self);

static const shape_api_t circle_vtable = {
   .draw = draw,
   .get_area = get_area,
   .get_perimeter = get_perimeter
};

// This is completely hidden from the user size, the size must be manually set in CIRCLE_SIZE
struct scircle {
    shape_t base;
    uint32_t radius;
    float    area;     // Dependent state: area = PI * r^2
};

hsCircle_t scircle_init(scircle_memory_t *mem, scircle_config_t *config)
{
    if (sizeof(struct scircle) > sizeof(scircle_memory_t))
    {
        return NULL; // Error: Header size constant is too small!
    }
    // CASTING MAGIC:    // We treat the raw memory block provided by the user as our specific struct.
    struct scircle *self = (struct scircle *)mem;

    // vtable
    self->base.api = &circle_vtable;

    // Initialize state
    self->radius = config->radius;
    self->area = (float)(self->radius * self->radius) * PI;

    // Return the pointer cast as the opaque handle type
    return (hsCircle_t)self;
}

void scircle_updateRadius(hsCircle_t self, uint32_t radius) {
    // 1. Update the primary state
    self->radius = radius;
    
    // 2. AUTOMATICALLY update the dependent state.
    self->area = (float)(radius * radius) * PI;
}

uint32_t scircle_getRadius(hsCircle_t self) {
    return self->radius;
}

float scircle_getArea(hsCircle_t self) {
    return self->area;
}

uint32_t scircle_getPerimeter(hsCircle_t self) {
    return self->radius * 2 * (uint32_t)PI;
}

static void draw(void * self)
{
    (void)self;
}

static float get_area(void * self)
{
    printf("Hey");
    return ((hsCircle_t)self)->area;
}

static uint32_t get_perimeter(void * self)
{
    return scircle_getPerimeter(self);
}