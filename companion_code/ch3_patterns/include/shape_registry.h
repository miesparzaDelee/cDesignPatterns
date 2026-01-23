#ifndef SHAPE_REGISTRY_H
#define SHAPE_REGISTRY_H

// region: registry_header
#include <stdint.h>
#include <stdbool.h>
#include "api_shape.h"

#define MAX_SHAPES 12

typedef struct 
{
    uint32_t count;
    api_shape_t * api_shapes[MAX_SHAPES];
    api_shape_t * biggestArea;
    api_shape_t * biggestPerimeter;    
}shape_registry_data_t;

/* Initialize/Get the singleton instance */
const shape_registry_data_t * shapeRegistry_Init(void);

// Updates the data (can allow handling async events)
void shapeRegistry_Tasks(void);

/* Core registry operations */
bool shapeRegistry_Register(api_shape_t * shape);

bool shapeRegistry_Unregister(api_shape_t * shape);
// endregion

#endif /* SHAPE_REGISTRY_H */
