#include "rectangle.h"

void rect_init(rectangle_t *self, uint32_t width, uint32_t height) {
    self->width = width;
    self->height = height;
}

uint32_t rect_get_area(rectangle_t *self) {
    return self->width * self->height;
}
