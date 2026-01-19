
#include "rectangle.h"

void rect_init(rectangle_t *self, rect_config_t * conf) {
    self->width = conf->width;
    self->height = conf->height;
}

uint32_t rect_get_area(rectangle_t *self) {
    return self->width * self->height;
}
