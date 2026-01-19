#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <stdint.h>
#include "shape_api.h"

// Object structure definition
typedef struct {
   shape_t base;
   uint32_t width;
   uint32_t height;
   const uint32_t area;
} srectangle_t;

// Object configuration structure definition (CS-06)
typedef struct
{
	uint32_t width;
	uint32_t height;
}srect_config_t;

void srect_init(srectangle_t *self, srect_config_t * conf);

uint32_t srect_get_area(srectangle_t *self);

uint32_t srect_get_perimeter(srectangle_t * self);

void srect_updateWidth(srectangle_t *self, uint32_t newWidth);

#endif // RECTANGLE_H
