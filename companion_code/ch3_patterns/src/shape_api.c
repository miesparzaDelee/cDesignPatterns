#include "shape_api.h"

#include <stddef.h>  // for NULL

void shape_draw(hShape self) {
   if (self == NULL || self->api == NULL || self->api->draw == NULL) {
       return;
   }
   
   self->api->draw(self);
}

float shape_get_area(hShape self) {
   if (self == NULL || self->api == NULL || self->api->get_area == NULL) {
       return 0.0f;
   }
   
   return self->api->get_area(self);
}

uint32_t shape_get_perimeter(hShape self) {
   if (self == NULL || self->api == NULL || self->api->get_perimeter == NULL) {
       return 0;
   }
   
   return self->api->get_perimeter(self);
}
