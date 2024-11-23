#ifndef COMMON_H
#define COMMON_H

#include <stddef.h>

#define CONTAINER_OF(ptr, type, member) \
    ((type *)((char *)(ptr) - offsetof(type, member)))

#endif