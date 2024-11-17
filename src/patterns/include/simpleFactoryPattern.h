#ifndef SHAPE_FACTORY_PATTERN_H
#define SHAPE_FACTORY_PATTERN_H

// this is our public header
typedef enum shape_type {
	SHAPE_CIRCLE,
	SHAPE_SQUARE
}shape_type;

typedef struct shape_api** hShape;

struct shape {
	const struct shape_api* api;
};

hShape shape_create(shape_type type);

void shape_draw(hShape shape);

#endif