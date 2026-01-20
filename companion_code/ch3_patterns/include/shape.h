#ifndef SHAPE_H
#define SHAPE_H

#include <stdint.h>
#include <stdbool.h>


typedef enum {
   SHAPE_TYPE_RECTANGLE = 1,
   SHAPE_TYPE_CIRCLE,
   SHAPE_TYPE_TRIANGLE
} shape_type_t;

/*
* Base shape structure.
* Fields placed here are inherited by all derived shapes.
*/
typedef struct {
   shape_type_t type;      // identifies the concrete shape type
   uint32_t color;         // shared property (RGB or index)
   bool visible;        // 0 = hidden, 1 = visible
} shape_t;

#endif // SHAPE_BASE_H
