#include "shape.h"
#include <stddef.h>

void shape_init(shape_t *self, shape_config_t *config) {
    if (self == NULL) {
        return;
    }
    self->type = config->type;
    self->visible = config->visible;
    self->color = config->color;
}
