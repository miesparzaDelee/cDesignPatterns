
#include "shape_rectangle.h"

static void draw(void * self);
static float get_area(void * self);
static uint32_t get_perimeter(void * self);

static const shape_api_t rectangle_vtable = {
   .draw = draw,
   .get_area = get_area,
   .get_perimeter = get_perimeter
};

void srect_init(srectangle_t *self, srect_config_t * conf) {
    self->width = conf->width;
    self->height = conf->height;
    self->base.api = &rectangle_vtable;
    srect_get_area(self);
}

uint32_t srect_get_area(srectangle_t *self) {
    *(uint32_t *)&self->area = self->height * self->width;
    return self->area;
}

void srect_updateWidth(srectangle_t *self, uint32_t newWidth)
{
    *(uint32_t *)&self->width = newWidth;
    srect_get_area(self);
}

uint32_t srect_get_perimeter(srectangle_t * self)
{
    return self->width*2 + self->height*2;
}

static void draw(void * self)
{
    (void)self;
}

static float get_area(void * self)
{
    return (float)(((srectangle_t *)self)->area);
}

static uint32_t get_perimeter(void * base)
{
    srectangle_t * self = (srectangle_t *)base;
    return self->width*2 + self->height*2;
}