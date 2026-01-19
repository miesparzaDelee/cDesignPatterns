#include "shape_api.h"

#include <stddef.h>  // for NULL

void shape_draw(hShape self) {
   // Safety check
   if (self == NULL || self->api == NULL || self->api->draw == NULL) {
       return;  // Or handle error appropriately
   }
   
   // Dispatch to the actual implementation through vtable
   self->api->draw(self);
}

float shape_get_area(hShape self) {
   // Safety check
   if (self == NULL || self->api == NULL || self->api->get_area == NULL) {
       return 0.0f;  // Or return error value
   }
   
   // Dispatch to the actual implementation through vtable
   return self->api->get_area(self);
}

uint32_t shape_get_perimeter(hShape self) {
   // Safety check
   if (self == NULL || self->api == NULL || self->api->get_perimeter == NULL) {
       return 0;  // Or return error value
   }
   
   // Dispatch to the actual implementation through vtable
   return self->api->get_perimeter(self);
}
