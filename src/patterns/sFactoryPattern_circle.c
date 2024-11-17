#include "sFactoryPattern_circle.h"

#include "simpleFactoryPatternPrivate.h"	

static void _shape_circle_draw(hShape shape) {
	shape_circle* me = CONTAINER_OF(shape, shape_circle, api);
	// now we can access private methods
	//_do_draw_circle(self->radius);
}
struct shape_api _circle_api = {
  .draw = _shape_circle_draw
};

void shape_circle_init(shape_circle* self) {
	memset(self, 0, sizeof(*self));
	self->api.api = &_circle_api;
}
