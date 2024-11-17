#include "CppUTest/TestHarness.h"

extern "C" {
#include "simpleFactoryPattern.h"
    // other references
}

TEST_GROUP(sFactoryPattern)
{
    void setup()
    {
        // Run before every test.
    }
    void teardown()
    {
        // Run after every test.
    }
};


TEST(sFactoryPattern, Create_Circle)
{
    hShape circle = shape_create(SHAPE_CIRCLE);
}

TEST(sFactoryPattern, Draw_Circle)
{
    hShape circle = shape_create(SHAPE_CIRCLE);
    shape_draw(circle);
}

TEST(sFactoryPattern, Create_Square)
{
    hShape square = shape_create(SHAPE_SQUARE);
}

TEST(sFactoryPattern, Draw_Square)
{
    hShape square = shape_create(SHAPE_SQUARE);
    shape_draw(square);
}