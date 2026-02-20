#include "CppUTest/TestHarness.h"

extern "C" {
    #include "canvas.h"
    #include "api_rectangle.h"
}

// Common Test Helpers
static api_shape_t *g_callbackShape = NULL;
static void *g_callbackContext = NULL;
static int g_callbackCount = 0;

static void testCallback(api_shape_t *shape, void *context)
{
    g_callbackShape = shape;
    g_callbackContext = context;
    g_callbackCount++;
}

static int16_t g_positionX = 0;
static int16_t g_positionY = 0;
static int g_positionCallbackCount = 0;
static void *g_positionCallbackContext = NULL;

static void positionTestCallback(api_shape_t *shape, int16_t x, int16_t y, void *context)
{
    (void)shape;
    g_positionCallbackContext = context;
    g_positionX = x;
    g_positionY = y;
    g_positionCallbackCount++;
}

// ============================================
// Group 1: Canvas Core Behavior
// ============================================
TEST_GROUP(Canvas)
{
    void setup()
    {
        canvas_config_t config = {};
        canvas_init(&config);
    }

    void teardown()
    {
    }
};

TEST(Canvas, AddShape_ReturnsTrue)
{
    api_rectangle_t rect = {};
    rect_config_t rect_conf = {10, 20};
    shape_config_t shape_conf = {SHAPE_TYPE_RECTANGLE, 0xFF0000, true};
    api_rectangle_init(&rect, &rect_conf, &shape_conf);
    
    CHECK_TRUE(canvas_addShape((api_shape_t*)&rect, 0, 0));
}

TEST(Canvas, AddShape_MultipleShapes_ReturnsTrue)
{
    api_rectangle_t rect1 = {};
    api_rectangle_t rect2 = {};
    rect_config_t rect_conf = {10, 20};
    shape_config_t shape_conf = {SHAPE_TYPE_RECTANGLE, 0xFF0000, true};
    api_rectangle_init(&rect1, &rect_conf, &shape_conf);
    api_rectangle_init(&rect2, &rect_conf, &shape_conf);
    
    CHECK_TRUE(canvas_addShape((api_shape_t*)&rect1, 0, 0));
    CHECK_TRUE(canvas_addShape((api_shape_t*)&rect2, 10, 10));
}

TEST(Canvas, MoveShape_IsMovingReturnsTrue)
{
    api_rectangle_t rect = {};
    rect_config_t rect_conf = {10, 20};
    shape_config_t shape_conf = {SHAPE_TYPE_RECTANGLE, 0xFF0000, true};
    api_rectangle_init(&rect, &rect_conf, &shape_conf);
    
    canvas_addShape((api_shape_t*)&rect, 0, 0);
    canvas_moveShape((api_shape_t*)&rect, 5, 5);
    
    CHECK_TRUE(canvas_isMoving((api_shape_t*)&rect));
}

TEST(Canvas, MoveShape_AfterArrival_IsMovingReturnsFalse)
{
    api_rectangle_t rect = {};
    rect_config_t rect_conf = {10, 20};
    shape_config_t shape_conf = {SHAPE_TYPE_RECTANGLE, 0xFF0000, true};
    api_rectangle_init(&rect, &rect_conf, &shape_conf);
    
    canvas_config_t config = {};
    canvas_init(&config);
    canvas_addShape((api_shape_t*)&rect, 0, 0);
    canvas_moveShape((api_shape_t*)&rect, 2, 2);
    
    canvas_task();
    canvas_task();
    canvas_task();
    
    CHECK_FALSE(canvas_isMoving((api_shape_t*)&rect));
}

TEST(Canvas, RemoveShape_ShapeNoLongerTracked)
{
    api_rectangle_t rect = {};
    rect_config_t rect_conf = {10, 20};
    shape_config_t shape_conf = {SHAPE_TYPE_RECTANGLE, 0xFF0000, true};
    api_rectangle_init(&rect, &rect_conf, &shape_conf);
    
    canvas_addShape((api_shape_t*)&rect, 0, 0);
    canvas_removeShape((api_shape_t*)&rect);
    
    CHECK_FALSE(canvas_isMoving((api_shape_t*)&rect));
}

// ============================================
// Group 2: Canvas Move Observer (1:N)
// ============================================
TEST_GROUP(CanvasMove)
{
    void setup()
    {
        g_callbackShape = NULL;
        g_callbackContext = NULL;
        g_callbackCount = 0;
        
        canvas_config_t config = {};
        canvas_init(&config);
    }
    
    void teardown()
    {
    }
};

TEST(CanvasMove, MoveShape_AfterTaskArrives_CallbackFired)
{
    int context = 42;
    canvas_move_observer_t obs;
    
    api_rectangle_t rect = {};
    rect_config_t rect_conf = {10, 20};
    shape_config_t shape_conf = {SHAPE_TYPE_RECTANGLE, 0xFF0000, true};
    api_rectangle_init(&rect, &rect_conf, &shape_conf);
    
    canvas_register_move_observer(&obs, testCallback, &context);
    
    canvas_addShape((api_shape_t*)&rect, 0, 0);
    canvas_moveShape((api_shape_t*)&rect, 3, 3);
    
    canvas_task();
    canvas_task();
    canvas_task();
    canvas_task();
    
    CHECK_EQUAL(1, g_callbackCount);
    CHECK_EQUAL((api_shape_t*)&rect, g_callbackShape);
    CHECK_EQUAL(&context, g_callbackContext);
}

TEST(CanvasMove, DeregisterObserver_RemovesCallback)
{
    int context1 = 1;
    canvas_move_observer_t obs;
    
    api_rectangle_t rect = {};
    rect_config_t rect_conf = {10, 20};
    shape_config_t shape_conf = {SHAPE_TYPE_RECTANGLE, 0xFF0000, true};
    api_rectangle_init(&rect, &rect_conf, &shape_conf);
    
    canvas_addShape((api_shape_t*)&rect, 0, 0);
    
    canvas_register_move_observer(&obs, testCallback, &context1);
    
    canvas_moveShape((api_shape_t*)&rect, 1, 1);
    canvas_task();
    canvas_task(); // Extra tick for completion check
    
    CHECK_EQUAL(1, g_callbackCount);
    
    // Deregister
    canvas_deregister_move_observer(&obs);
    
    // Move again
    canvas_moveShape((api_shape_t*)&rect, 2, 2);
    canvas_task();
    canvas_task(); // Extra tick
    
    // Should NOT fire again
    CHECK_EQUAL(1, g_callbackCount);
}

TEST(CanvasMove, usage_example)
{
    // Example application state
    int appState1 = 100;
    int appState2 = 200;
    
    canvas_move_observer_t obs1;
    canvas_move_observer_t obs2;

    // 1. Register observer
    canvas_register_move_observer(&obs1, testCallback, &appState1);

    // 2. Create and add shapes
    api_rectangle_t rect1 = {};
    rect_config_t rect1_conf = {10, 20};
    shape_config_t rect1_shape = {SHAPE_TYPE_RECTANGLE, 0xFF0000, true};
    api_rectangle_init(&rect1, &rect1_conf, &rect1_shape);
    canvas_addShape((api_shape_t*)&rect1, 0, 0);
    
    api_rectangle_t rect2 = {};
    rect_config_t rect2_conf = {15, 25};
    shape_config_t rect2_shape = {SHAPE_TYPE_RECTANGLE, 0x00FF00, true};
    api_rectangle_init(&rect2, &rect2_conf, &rect2_shape);
    canvas_addShape((api_shape_t*)&rect2, 10, 10);
    
    // 3. Start async movements
    canvas_moveShape((api_shape_t*)&rect1, 3, 3);
    canvas_moveShape((api_shape_t*)&rect2, 5, 5);
    
    // 4. Register a second observer
    canvas_register_move_observer(&obs2, testCallback, &appState2);
    
    api_rectangle_t rect3 = {};
    rect_config_t rect3_conf = {8, 12};
    shape_config_t rect3_shape = {SHAPE_TYPE_RECTANGLE, 0x0000FF, true};
    api_rectangle_init(&rect3, &rect3_conf, &rect3_shape);
    canvas_addShape((api_shape_t*)&rect3, 20, 20);
    canvas_moveShape((api_shape_t*)&rect3, 22, 22);
    
    // 5. Simulate main loop
    for (int i = 0; i < 8; i++) {
        canvas_task();
    }
    
    // 6. Verify callbacks
    CHECK_EQUAL(6, g_callbackCount);
    CHECK_FALSE(canvas_isMoving((api_shape_t*)&rect1));
    CHECK_FALSE(canvas_isMoving((api_shape_t*)&rect2));
    CHECK_FALSE(canvas_isMoving((api_shape_t*)&rect3));
}

// ============================================
// Group 3: Canvas Position Listener (1:1)
// ============================================
TEST_GROUP(CanvasPosition)
{
    void setup()
    {
        g_positionX = 0;
        g_positionY = 0;
        g_positionCallbackCount = 0;
        g_positionCallbackContext = NULL;
        
        canvas_config_t config = {};
        canvas_init(&config);
    }

    void teardown()
    {
    }
};

TEST(CanvasPosition, PositionListener_FiresOnEveryPositionChange)
{
    int context = 100;
    api_rectangle_t rect = {};
    rect_config_t rect_conf = {10, 20};
    shape_config_t shape_conf = {SHAPE_TYPE_RECTANGLE, 0xFF0000, true};
    api_rectangle_init(&rect, &rect_conf, &shape_conf);
    
    canvas_config_t config = {};
    config.positionListener = positionTestCallback;
    config.positionContext = &context;
    canvas_init(&config);
    
    canvas_addShape((api_shape_t*)&rect, 0, 0);
    canvas_moveShape((api_shape_t*)&rect, 3, 0);
    
    // Each task moves 1 step, listener fires on each change
    canvas_task();
    CHECK_EQUAL(1, g_positionCallbackCount);
    CHECK_EQUAL(1, g_positionX);
    CHECK_EQUAL(0, g_positionY);
    
    canvas_task();
    CHECK_EQUAL(2, g_positionCallbackCount);
    CHECK_EQUAL(2, g_positionX);
    
    canvas_task();
    CHECK_EQUAL(3, g_positionCallbackCount);
    CHECK_EQUAL(3, g_positionX);
}

TEST(CanvasPosition, PositionListener_Disabled_DoesNotFire)
{
    api_rectangle_t rect = {};
    rect_config_t rect_conf = {10, 20};
    shape_config_t shape_conf = {SHAPE_TYPE_RECTANGLE, 0xFF0000, true};
    api_rectangle_init(&rect, &rect_conf, &shape_conf);
    
    canvas_config_t config = {};
    config.positionListener = positionTestCallback;
    canvas_init(&config);
    canvas_disablePositionListener();
    
    canvas_addShape((api_shape_t*)&rect, 0, 0);
    canvas_moveShape((api_shape_t*)&rect, 2, 0);
    
    canvas_task();
    CHECK_EQUAL(0, g_positionCallbackCount);
}

TEST(CanvasPosition, PositionListener_CanBeReEnabled)
{
    api_rectangle_t rect = {};
    rect_config_t rect_conf = {10, 20};
    shape_config_t shape_conf = {SHAPE_TYPE_RECTANGLE, 0xFF0000, true};
    api_rectangle_init(&rect, &rect_conf, &shape_conf);
    
    canvas_config_t config = {};
    config.positionListener = positionTestCallback;
    canvas_init(&config);
    canvas_disablePositionListener();
    
    canvas_addShape((api_shape_t*)&rect, 0, 0);
    canvas_moveShape((api_shape_t*)&rect, 1, 0);
    
    canvas_task();
    CHECK_EQUAL(0, g_positionCallbackCount);
    
    canvas_enablePositionListener();
    canvas_moveShape((api_shape_t*)&rect, 2, 0);
    canvas_task();
    CHECK_EQUAL(1, g_positionCallbackCount);
}

TEST(CanvasPosition, SetPositionChangeCallback_ChangesCallback)
{
    int context1 = 1;
    int context2 = 2;
    
    api_rectangle_t rect = {};
    rect_config_t rect_conf = {10, 20};
    shape_config_t shape_conf = {SHAPE_TYPE_RECTANGLE, 0xFF0000, true};
    api_rectangle_init(&rect, &rect_conf, &shape_conf);
    
    canvas_config_t config = {};
    config.positionListener = positionTestCallback;
    config.positionContext = &context1;
    canvas_init(&config);
    
    canvas_addShape((api_shape_t*)&rect, 0, 0);
    canvas_moveShape((api_shape_t*)&rect, 1, 0);
    canvas_task();
    
    CHECK_EQUAL(&context1, g_positionCallbackContext);
    
    canvas_setPositionChangeCallback(positionTestCallback, &context2);
    canvas_moveShape((api_shape_t*)&rect, 2, 0);
    canvas_task();
    
    CHECK_EQUAL(&context2, g_positionCallbackContext);
}

TEST(CanvasPosition, usage_example)
{
    int loggerId = 1;
    int uiId = 2;
    
    // 1. Initialize
    canvas_config_t config = {};
    config.positionListener = positionTestCallback;
    config.positionContext = &loggerId;
    canvas_init(&config);
    
    // 2. Add shapes
    api_rectangle_t rect1 = {};
    rect_config_t rect1_conf = {10, 20};
    shape_config_t rect1_shape = {SHAPE_TYPE_RECTANGLE, 0xFF0000, true};
    api_rectangle_init(&rect1, &rect1_conf, &rect1_shape);
    canvas_addShape((api_shape_t*)&rect1, 0, 0);
    
    api_rectangle_t rect2 = {};
    rect_config_t rect2_conf = {15, 25};
    shape_config_t rect2_shape = {SHAPE_TYPE_RECTANGLE, 0x00FF00, true};
    api_rectangle_init(&rect2, &rect2_conf, &rect2_shape);
    canvas_addShape((api_shape_t*)&rect2, 10, 10);
    
    // 3. Start movements
    canvas_moveShape((api_shape_t*)&rect1, 2, 0);
    canvas_moveShape((api_shape_t*)&rect2, 12, 10);
    
    // 4. Simulate loop
    for (int i = 0; i < 4; i++) {
        canvas_task();
    }
    
    // 5. Verify callbacks
    CHECK_EQUAL(4, g_positionCallbackCount);
    
    // 6. Disable
    canvas_disablePositionListener();
    canvas_moveShape((api_shape_t*)&rect1, 3, 0);
    canvas_task();
    
    CHECK_EQUAL(4, g_positionCallbackCount);
    
    // 7. Re-enable with new context
    canvas_setPositionChangeCallback(positionTestCallback, &uiId);
    canvas_enablePositionListener();
    canvas_moveShape((api_shape_t*)&rect1, 4, 0);
    canvas_task();
    
    CHECK_EQUAL(5, g_positionCallbackCount);
}
