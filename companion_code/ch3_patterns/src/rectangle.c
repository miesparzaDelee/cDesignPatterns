
#include "rectangle.h"

void rect_init(rectangle_t *self, rect_config_t * conf) {
    self->width = conf->width;
    self->height = conf->height;
    rect_get_area(self);
}

uint32_t rect_get_area(rectangle_t *self) {
    *(uint32_t *)&self->area = self->height * self->width;
    return self->area;
}

void rect_updateWidth(rectangle_t *self, uint32_t newWidth)
{
    *(uint32_t *)&self->width = newWidth;
    rect_get_area(self);
}