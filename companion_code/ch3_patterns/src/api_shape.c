#include "api_shape.h"
#include <stddef.h>

void api_shape_init(api_shape_t *self, shape_config_t *config, const shape_vtable_t *vptr)
{
    if (self == NULL || config == NULL || vptr == NULL) {
        return;
    }

    // 1. Initialize the base (shape_t)
    shape_init(&self->base, config);

    // 2. Initialize the vptr
    self->vptr = vptr;
}

void shape_draw(api_shape_t *self)
{
    if (self && self->vptr && self->vptr->draw) {
        self->vptr->draw(self); 
    }
}

float shape_get_area(api_shape_t *self)
{
    if (self && self->vptr && self->vptr->get_area) {
        return self->vptr->get_area(self);
    }
    return 0.0f;
}

uint32_t shape_get_perimeter(api_shape_t *self)
{
    if (self && self->vptr && self->vptr->get_perimeter) {
        return self->vptr->get_perimeter(self);
    }
    return 0;
}
