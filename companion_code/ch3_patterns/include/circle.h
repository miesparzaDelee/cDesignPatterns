#ifndef CIRCLE_H
#define CIRCLE_H

#include <stdint.h>
#include <stdbool.h>

// We must expose the SIZE so the user can allocate memory.
// Note: If the internal struct grows, this must be updated manually.
#define CIRCLE_SIZE    (2)      // 2 elements 
typedef struct {
    uint32_t _reserved[CIRCLE_SIZE];
} circle_memory_t;

// The Opaque Handle
typedef struct circle * hCircle_t;

// Configuration Struct
typedef struct {
    uint32_t radius;
} circle_config_t;

// Initialization now takes a pointer to the RAW storage
hCircle_t circle_init(circle_memory_t *mem, circle_config_t *config);

void circle_updateRadius(hCircle_t self, uint32_t radius);

uint32_t circle_getRadius(hCircle_t self);

float circle_getArea(hCircle_t self);

#endif // CIRCLE_H