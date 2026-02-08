#include "canvas.h"

#include <string.h>

#define CANVAS_STEP_SIZE 1

/* Shape item tracked by canvas */
typedef struct {
    api_shape_t *shape;
    int16_t current_x;
    int16_t current_y;
    int16_t target_x;
    int16_t target_y;
    bool is_moving;
} canvas_item_t;

/* Private singleton state */
typedef struct {
    canvas_item_t items[CANVAS_MAX_SHAPES];
    /* 3.9 Simple Callback */
    canvas_moveCallback_t moveCallback;
    void *moveContext;
    /* 3.10 Observer Pattern */
    canvas_positionListener_t positionListener;
    void *positionContext;
    bool positionListenerEnabled;
} canvas_private_t;

static canvas_private_t priv_canvas = {0};

static int32_t find_item_index(api_shape_t *shape);
static void update_position(canvas_item_t *item);

void canvas_init(const canvas_config_t *config)
{
    memset(&priv_canvas, 0, sizeof(priv_canvas));
    
    priv_canvas.moveCallback = config->moveCallback;
    priv_canvas.moveContext = config->moveContext;
    priv_canvas.positionListener = config->positionListener;
    priv_canvas.positionContext = config->positionContext;
    priv_canvas.positionListenerEnabled = (config->positionListener != NULL);
}

void canvas_setMoveCallback(canvas_moveCallback_t callback, void *context)
{
    priv_canvas.moveCallback = callback;
    priv_canvas.moveContext = context;
}

void canvas_setPositionChangeCallback(canvas_positionListener_t callback, void *context)
{
    priv_canvas.positionListener = callback;
    priv_canvas.positionContext = context;
    priv_canvas.positionListenerEnabled = (callback != NULL);
}

void canvas_enablePositionListener(void)
{
    priv_canvas.positionListenerEnabled = (priv_canvas.positionListener != NULL);
}

void canvas_disablePositionListener(void)
{
    priv_canvas.positionListenerEnabled = false;
}

bool canvas_addShape(api_shape_t *shape, int16_t x, int16_t y)
{
    for (int32_t i = 0; i < CANVAS_MAX_SHAPES; i++) {
        if (priv_canvas.items[i].shape == NULL) {
            priv_canvas.items[i].shape = shape;
            priv_canvas.items[i].current_x = x;
            priv_canvas.items[i].current_y = y;
            priv_canvas.items[i].target_x = x;
            priv_canvas.items[i].target_y = y;
            priv_canvas.items[i].is_moving = false;
            return true;
        }
    }
    return false;
}

void canvas_removeShape(api_shape_t *shape)
{
    int32_t index = find_item_index(shape);
    if (index >= 0) {
        memset(&priv_canvas.items[index], 0, sizeof(canvas_item_t));
    }
}

void canvas_moveShape(api_shape_t *shape, int16_t target_x, int16_t target_y)
{
    int32_t index = find_item_index(shape);
    if (index >= 0) {
        priv_canvas.items[index].target_x = target_x;
        priv_canvas.items[index].target_y = target_y;
        priv_canvas.items[index].is_moving = true;
    }
}

void canvas_task(void)
{
    for (int32_t i = 0; i < CANVAS_MAX_SHAPES; i++) {
        if (priv_canvas.items[i].is_moving) {
            update_position(&priv_canvas.items[i]);
            if (!priv_canvas.items[i].is_moving && priv_canvas.moveCallback != NULL) {
                priv_canvas.moveCallback(priv_canvas.items[i].shape, priv_canvas.moveContext);
            }
        }
    }
}

bool canvas_isMoving(api_shape_t *shape)
{
    int32_t index = find_item_index(shape);
    if (index >= 0) {
        return priv_canvas.items[index].is_moving;
    }
    return false;
}

static int32_t find_item_index(api_shape_t *shape)
{
    for (int32_t i = 0; i < CANVAS_MAX_SHAPES; i++) {
        if (priv_canvas.items[i].shape == shape) {
            return i;
        }
    }
    return -1;
}

static void update_position(canvas_item_t *item)
{
    bool moved = false;
    
    if (item->current_x < item->target_x) {
        item->current_x += CANVAS_STEP_SIZE;
        if (item->current_x > item->target_x) {
            item->current_x = item->target_x;
        }
        moved = true;
    } else if (item->current_x > item->target_x) {
        item->current_x -= CANVAS_STEP_SIZE;
        if (item->current_x < item->target_x) {
            item->current_x = item->target_x;
        }
        moved = true;
    }
    
    if (item->current_y < item->target_y) {
        item->current_y += CANVAS_STEP_SIZE;
        if (item->current_y > item->target_y) {
            item->current_y = item->target_y;
        }
        moved = true;
    } else if (item->current_y > item->target_y) {
        item->current_y -= CANVAS_STEP_SIZE;
        if (item->current_y < item->target_y) {
            item->current_y = item->target_y;
        }
        moved = true;
    }
    
    /* 3.10 Observer Pattern - notify on every position change */
    if (moved && priv_canvas.positionListenerEnabled && priv_canvas.positionListener != NULL) {
        priv_canvas.positionListener(item->shape, item->current_x, item->current_y, priv_canvas.positionContext);
    }
    
    if (!moved) {
        item->is_moving = false;
    }
}
