#include "simpleFactoryPattern.h"

#include "simpleFactoryPatternPrivate.h"
#include "sFactoryPattern_square.h"
#include "sFactoryPattern_circle.h"

hShape shape_create(shape_type type) {
	switch (type) {
	case SHAPE_CIRCLE: {
		shape_circle* circle_shape = (shape_circle*)malloc(sizeof(shape_circle));
		shape_circle_init(circle_shape);
		return &circle_shape->api;
	} break;
	case SHAPE_SQUARE: {
		shape_rectangle* shape = (shape_rectangle*)malloc(sizeof(shape_rectangle));
		shape_square_init(shape);
		return &shape->api;
	} break;
	}
	return NULL;
}

void shape_draw(hShape shape) {
	// call the virtual method
	(*shape)->draw(shape);
}