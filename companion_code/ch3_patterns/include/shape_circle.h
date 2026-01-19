#ifndef CIRCLE_H
#define CIRCLE_H

#include <stdint.h>
#include <stdbool.h>

// We must expose the SIZE so the user can allocate memory.
// Note: If the internal struct grows, this must be updated manually.
#define CIRCLE_SIZE    (2)      // 2 elements 
typedef struct {
    uint32_t _reserved[CIRCLE_SIZE];
} scircle_memory_t;

// The Opaque Handle
typedef struct scircle * hsCircle_t;

// Configuration Struct
typedef struct {
    uint32_t radius;
} scircle_config_t;

// Initialization now takes a pointer to the RAW storage
hsCircle_t scircle_init(scircle_memory_t *mem, scircle_config_t *config);

void scircle_updateRadius(hsCircle_t self, uint32_t radius);

uint32_t scircle_getRadius(hsCircle_t self);

float scircle_getArea(hsCircle_t self);

uint32_t scircle_getPerimeter(hsCircle_t self);

#endif // CIRCLE_H