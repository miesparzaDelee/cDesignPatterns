#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <stdint.h>

// Object structure definition
typedef struct {
    uint32_t width;
    uint32_t height;
} rectangle_t;

// Object configuration structure definition (CS-06)
typedef struct
{
	uint32_t width;
	uint32_t height;
}rect_config_t;

void rect_init(rectangle_t *self, rect_config_t * conf);

uint32_t rect_get_area(rectangle_t *self);

void rect_deinit(rectangle_t *self, rect_config_t * conf);

#endif // RECTANGLE_H
