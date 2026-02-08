#ifndef CANVAS_H
#define CANVAS_H

#include <stdint.h>
#include <stdbool.h>
#include "api_shape.h"

#define CANVAS_MAX_SHAPES 8

typedef void (*canvas_moveCallback_t)(api_shape_t *shape, void *context);

typedef struct {
    canvas_moveCallback_t moveCallback;
    void *moveContext;
} canvas_config_t;

void canvas_init(const canvas_config_t *config);
void canvas_setMoveCallback(canvas_moveCallback_t callback, void *context);
bool canvas_addShape(api_shape_t *shape, int16_t x, int16_t y);
void canvas_removeShape(api_shape_t *shape);
void canvas_moveShape(api_shape_t *shape, int16_t target_x, int16_t target_y);
void canvas_task(void);
bool canvas_isMoving(api_shape_t *shape);

#endif /* CANVAS_H */
