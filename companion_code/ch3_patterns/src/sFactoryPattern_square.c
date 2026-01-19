#include "sFactoryPattern_square.h"

#include "simpleFactoryPatternPrivate.h"
#include <string.h>

static void _shape_square_draw(hShape shape) {
	shape_rectangle* me = CONTAINER_OF(shape, shape_rectangle, api);
	// now we can access private methods
	//_do_draw_rectangle(self->width, self->height);
}
struct shape_api _rectangle_api = {
  .draw = _shape_square_draw
};
void shape_square_init(shape_rectangle* me) {
	memset(me, 0, sizeof(*me));
	me->api.api = &_rectangle_api;

	// Add more init
}