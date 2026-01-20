# Design Patterns for Embedded modular development
[x] Object
[x] Opaque
[x] Private
 
 ## INHERITANCE PATTERN

Inheritance in C is implemented by placing a base struct as the FIRST member of a derived struct. This guarantees that the address of the derived object equals the address of its base part, enabling safe upcasting (derived -> base) and downcasting (base -> derived). This allows sharing common fields and building polymorphic behaviors.

Example: typedef struct { uint32_t color; uint8_t visible; shape_type_t type; } shape_t;

typedef struct { shape_t base; // MUST be first rectangle_t rect; // specific object } shape_rectangle_t;

typedef struct { shape_t base;
circle_memory_t mem; hCircle_t circle; } shape_circle_t;

typedef struct { shape_t base; triangle_t triangle; } shape_triangle_t;

Important notes:

- initialize base first, then the specific object
- this pattern allows storing all shapes as (shape_t*) for generic processing
- opaque pattern becomes awkward here because extra memory blobs and handles clutter derived structs, which reveals why private pattern - fits inheritance better

## API / VTABLE PATTERN

Adds runtime polymorphism. A base API type contains a pointer to a vtable (table of function pointers). Each derived type provides its own vtable implementation. All polymorphic objects are accessed via the single shared base type.

Example vtable: typedef struct { uint32_t (get_area)(void self); void (draw)(void self); } shape_api_vtable_t;

Example API base: typedef struct { shape_t* base; const shape_api_vtable_t* vtable; } shape_api_t;

Example derived API shapes (wrapping the inheritance-layer shapes): typedef struct { shape_api_t api; shape_rectangle_t* shape; } api_rectangle_t;

Now you can do: shape_api_t* s = (shape_api_t*)&apiRect; s->vtable->draw(s);

Important notes:

- this layer is NEW and does not modify earlier example files
- it “upgrades” inheritance into full polymorphism
- derived api_shapes wrap your existing inheritance shapes

## FACTORY PATTERN

Centralizes object creation. The factory decides which concrete shape to build and returns a unified polymorphic type (shape_api_t*). It hides the complexity of building the shape, initializing it, and assigning a vtable.

Example: shape_api_t* shapeFactory_create(shape_type_t type, void* config);

Internally:

allocate or use static memory for api_rectangle_t / api_circle_t / api_triangle_t
initialize the underlying shape_rectangle / shape_circle / shape_triangle
attach the correct vtable
return (shape_api_t*)
Important notes:

- factory works best at the VTABLE LAYER, not the inheritance layer
- this allows the user to call get_area/draw generically regardless of shape type
- cleanly hides creation logic and promotes modularity

## SINGLETON PATTERN

Not object-oriented. This is a module-level pattern using static internal state. Guarantees that a module has exactly one instance and exposes an init -> task -> deinit flow. Useful when only one hardware resource or system service must exist.

Example: static struct { uint32_t counter; bool initialized; } g_system;

void system_init(void) { ... } void system_task(void) { ... } void system_deinit(void) { ... }

Important notes:

- this is not inheritance or polymorphism
- avoids global variables by grouping them internally
- optionally lazy-initialize or add RTOS mutex for thread safety
- perfect for modules that manage tasks, hardware, or global subsystems
- this escapes OOP and stands alone as a modular pattern

## SIMPLE CALLBACK PATTERN

A 1:1, one-shot notification system. Only meaningful when the operation is asynchronous. The module performs work over time (multiple task() calls), and triggers a single callback when the operation finishes.

Example module: shapeMover shapeMover_startMoveTo(x, y, callback) shapeMover_task()

The task() increments position gradually: if movement finished: callback(context)

Important notes:

- MUST be asynchronous to be meaningful
- fires callback exactly once
- good for one-shot completion (motor movement, ADC done, transfer done)

## OBSERVER PATTERN (MULTI-CALLBACK)

1:N notifications. Multiple listeners register to be notified whenever something changes. Works extremely well with asynchronous task loops because it repeatedly checks for changes and notifies all listeners.

Example module: shapeMonitor Listeners: shapeMonitor_addListener(cb, ctx) shapeMonitor_removeListener(cb, ctx)

Task: shapeMonitor_update(shape) detects area/visibility/dimension changes notifies ALL listeners

Important notes:

- suitable for repeated change-driven events
- ideal for logging, UI refresh, telemetry, statistics
- decouples producer (shape changes) from multiple consumers

## INTRUSIVE CALLBACK PATTERN

High-performance event system using embedded callback nodes. Listener objects embed the callback structure. The event source holds an intrusive linked list of these nodes. Uses CONTAINER_OF to recover the listener object from the embedded callback field.

Example listener: typedef struct { shape_event_listener_t listener; // embedded node uint32_t count; } MyListener;

Example event source: shapeEventSource_process(shape) checks boundary/threshold/collision if event: for each listener node: listener->onEvent(listener, shape)

Listener retrieves itself: MyListener* self = CONTAINER_OF(listener, MyListener, listener);

Important notes:

- zero allocation, extremely efficient
- ideal for real-time loops and kernel-like systems
- embedded nodes allow fast registration and minimal memory overhead
- most powerful but most advanced callback pattern