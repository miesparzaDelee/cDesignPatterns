#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <stdint.h>

typedef struct {
    uint32_t width;
    uint32_t height;
} rectangle_t;

void rect_init(rectangle_t *self, uint32_t width, uint32_t height);
uint32_t rect_get_area(rectangle_t *self);

#endif // RECTANGLE_H
