#ifndef TRIANGLE_PRIVATE_H
#define TRIANGLE_PRIVATE_H

#include <stdint.h>

typedef struct
{
    uint32_t base;
    uint32_t height;
} _triangle_private_t;

_triangle_private_t* triangle_getPrivateInfo(hTriangle_t self);

#endif // TRIANGLE_PRIVATE_H
