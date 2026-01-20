#include "triangle.h"

#define PI 3.14159f

void triangle_init(hTriangle_t self, triangle_config_t *config)
{
    self->_private.base = config->base;
    self->_private.height = config->height;
    
    *(float *)&self->area = (float)(self->_private.base * self->_private.height) / 2.0f;
}

void triangle_updateDimensions(hTriangle_t self, uint32_t base, uint32_t height)
{
    self->_private.base = base;
    self->_private.height = height;
    
    *(float *)&self->area = (float)(base * height) / 2.0f;
}

_triangle_private_t* triangle_getPrivateInfo(hTriangle_t self)
{
    return &self->_private;
}
