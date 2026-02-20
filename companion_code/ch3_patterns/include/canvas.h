#ifndef CANVAS_H
#define CANVAS_H

#include <stdint.h>
#include <stdbool.h>
#include "api_shape.h"

#define CANVAS_MAX_SHAPES 8

/* 3.10 Observer Pattern (1:N) - fired when movement completes.
 * User allocates this struct, but its fields are hidden/managed by the canvas module. */
#define CANVAS_OBSERVER_SIZE 3 // next, callback, context

typedef struct {
    void * _reserved[CANVAS_OBSERVER_SIZE]; 
} canvas_move_observer_t;

// Callback function signature
typedef void (*canvas_moveCallback_t)(api_shape_t *shape, void *context);

/* 3.9 Simple Callback Pattern - fired on every position change */
typedef void (*canvas_positionListener_t)(api_shape_t *shape, int16_t x, int16_t y, void *context);

typedef struct {
    // Position listener stored within the module
    canvas_positionListener_t positionListener; 
    void *positionContext;
} canvas_config_t;

void canvas_init(const canvas_config_t *config);

// Register and configure the observer node
void canvas_register_move_observer(canvas_move_observer_t *observer, 
                                   canvas_moveCallback_t callback, 
                                   void *context);

// Deregister the observer node (removes from list)
void canvas_deregister_move_observer(canvas_move_observer_t *observer);

void canvas_setPositionChangeCallback(canvas_positionListener_t callback, void *context);
void canvas_enablePositionListener(void);
void canvas_disablePositionListener(void);
bool canvas_addShape(api_shape_t *shape, int16_t x, int16_t y);
void canvas_removeShape(api_shape_t *shape);
void canvas_moveShape(api_shape_t *shape, int16_t target_x, int16_t target_y);
void canvas_task(void);
bool canvas_isMoving(api_shape_t *shape);

#endif /* CANVAS_H */
