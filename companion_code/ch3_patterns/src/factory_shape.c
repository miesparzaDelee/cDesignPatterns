#include "factory_shape.h"

api_shape_t* factory_shape_create(api_shape_t * shape, factory_config_t * config)
{
    if (shape == NULL || config == NULL) {
        return NULL;
    }

    shape_config_t * shape_conf = &config->shape_conf;

    switch (shape_conf->type) {
        case SHAPE_TYPE_RECTANGLE: {
            api_rectangle_t *rect = (api_rectangle_t*)shape;
            api_rectangle_init(rect, &config->shape.rect, shape_conf);
            return (api_shape_t*)rect;
        }
        case SHAPE_TYPE_CIRCLE: {
            api_circle_t *circle = (api_circle_t*)shape;
            api_circle_init(circle, &config->shape.circle, shape_conf);
            return (api_shape_t*)circle;
        }
        case SHAPE_TYPE_TRIANGLE: { 
            api_triangle_t *tri = (api_triangle_t*)shape;
            api_triangle_init(tri, &config->shape.triangle, shape_conf);
            return (api_shape_t*)tri;
        }
        default:
            return NULL;
    }
}
