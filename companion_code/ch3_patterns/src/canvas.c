#include "canvas.h"

#include <string.h>

#define CANVAS_STEP_SIZE 1

typedef struct {
    api_shape_t *shape;
    int16_t current_x;
    int16_t current_y;
    int16_t target_x;
    int16_t target_y;
    bool is_moving;
} canvas_item_t;

static canvas_item_t priv_items[CANVAS_MAX_SHAPES];
static canvas_moveCallback_t priv_moveCallback;
static void *priv_moveContext;

static int32_t find_item_index(api_shape_t *shape);
static void update_position(canvas_item_t *item);

void canvas_init(const canvas_config_t *config)
{
    memset(priv_items, 0, sizeof(priv_items));
    priv_moveCallback = config->moveCallback;
    priv_moveContext = config->moveContext;
}

void canvas_setMoveCallback(canvas_moveCallback_t callback, void *context)
{
    priv_moveCallback = callback;
    priv_moveContext = context;
}

bool canvas_addShape(api_shape_t *shape, int16_t x, int16_t y)
{
    for (int32_t i = 0; i < CANVAS_MAX_SHAPES; i++) {
        if (priv_items[i].shape == NULL) {
            priv_items[i].shape = shape;
            priv_items[i].current_x = x;
            priv_items[i].current_y = y;
            priv_items[i].target_x = x;
            priv_items[i].target_y = y;
            priv_items[i].is_moving = false;
            return true;
        }
    }
    return false;
}

void canvas_removeShape(api_shape_t *shape)
{
    int32_t index = find_item_index(shape);
    if (index >= 0) {
        memset(&priv_items[index], 0, sizeof(canvas_item_t));
    }
}

void canvas_moveShape(api_shape_t *shape, int16_t target_x, int16_t target_y)
{
    int32_t index = find_item_index(shape);
    if (index >= 0) {
        priv_items[index].target_x = target_x;
        priv_items[index].target_y = target_y;
        priv_items[index].is_moving = true;
    }
}

void canvas_task(void)
{
    for (int32_t i = 0; i < CANVAS_MAX_SHAPES; i++) {
        if (priv_items[i].is_moving) {
            update_position(&priv_items[i]);
            if (!priv_items[i].is_moving && priv_moveCallback != NULL) {
                priv_moveCallback(priv_items[i].shape, priv_moveContext);
            }
        }
    }
}

bool canvas_isMoving(api_shape_t *shape)
{
    int32_t index = find_item_index(shape);
    if (index >= 0) {
        return priv_items[index].is_moving;
    }
    return false;
}

static int32_t find_item_index(api_shape_t *shape)
{
    for (int32_t i = 0; i < CANVAS_MAX_SHAPES; i++) {
        if (priv_items[i].shape == shape) {
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
    
    if (!moved) {
        item->is_moving = false;
    }
}
