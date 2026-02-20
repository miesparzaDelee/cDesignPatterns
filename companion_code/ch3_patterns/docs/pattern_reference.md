# Pattern Reference - ch3 Library

## Design Patterns Implemented

| Module | Pattern | Purpose |
|--------|---------|---------|
| `rectangle.h/.c` | Composition | Rectangle geometry with area calculation |
| `circle.h/.c` | Opaque Handle | Circle geometry with memory management |
| `triangle.h/.c` | Private Data | Triangle geometry with information hiding |
| `shape.h/.c` | Family(Inheritance) | Base shape interface |
| `api_shape.h/.c` | VTable | Runtime polymorphism for shapes |
| `api_rectangle.h/.c` | VTable + Composition | Rectangle API wrapper |
| `api_circle.h/.c` | VTable + Opaque Handle | Circle API wrapper |
| `api_triangle.h/.c` | VTable + Private Data | Triangle API wrapper |
| `factory_shape.h/.c` | Factory | Object creation based on type |
| `shape_registry.h/.c` | Singleton | Global shape registry management |
| `canvas.h/.c` | Simple Callback (3.9) | 1:1 position change listener with enable/disable |
| `canvas.h/.c` | Observer (3.10) | 1:N move completion notifications via opaque nodes |

## Module Dependencies

```
common.h
├── shape.h
│   ├── rectangle.h
│   ├── circle.h
│   └── triangle.h
├── api_shape.h
│   ├── api_rectangle.h
│   ├── api_circle.h
│   └── api_triangle.h
├── factory_shape.h
├── shape_registry.h
└── canvas.h
```

## API Surface

| Module | Public Functions |
|--------|-----------------|
| Core Shapes | `rect_init()`, `circle_init()`, `triangle_init()` |
| API Shapes | `shape_draw()`, `shape_get_area()`, `shape_get_perimeter()` |
| Factory | `factory_shape_create()` |
| Registry | `shapeRegistry_Init()`, `shapeRegistry_Register()` |
| Canvas | `canvas_init()`, `canvas_addShape()`, `canvas_moveShape()`, `canvas_task()` |
| Canvas (3.9) | `canvas_setPositionChangeCallback()`, `canvas_enablePositionListener()`, `canvas_disablePositionListener()` |
| Canvas (3.10) | `canvas_register_move_observer()`, `canvas_deregister_move_observer()` |
| Utilities | `cbOwner_Init()`, `cbOwner_AddCallback()` |
