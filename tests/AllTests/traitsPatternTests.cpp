#include "CppUTest/TestHarness.h"

extern "C" {
#include "traitsPattern.h"
}

TEST_GROUP(TraitsPattern)
{
    void setup() { /* Run before every test */ }
    void teardown() { /* Run after every test */ }
};

TEST(TraitsPattern, DogTraitsBehavior)
{
    Dog myDog;
    Dog_Init(&myDog);

    /* Ensure initial state */
    CHECK(myDog.moveCalled == 0);
    CHECK(myDog.soundCalled == 0);

    /* Test move behavior */
    move(&myDog.moveTrait);
    CHECK(myDog.moveCalled == 1);

    /* Test make_sound behavior */
    make_sound(&myDog.soundTrait);
    CHECK(myDog.soundCalled == 1);
}

TEST(TraitsPattern, RobotTraitsBehavior)
{
    Robot myRobot;
    Robot_Init(&myRobot);

    /* Ensure initial state */
    CHECK(myRobot.moveCalled == 0);
    CHECK(myRobot.soundCalled == 0);

    /* Test move behavior */
    move(&myRobot.moveTrait);
    CHECK(myRobot.moveCalled == 1);

    /* Test make_sound behavior */
    make_sound(&myRobot.soundTrait);
    CHECK(myRobot.soundCalled == 1);
}

TEST(TraitsPattern, IndependentBehavior)
{
    Dog myDog;
    Robot myRobot;

    Dog_Init(&myDog);
    Robot_Init(&myRobot);

    /* Test independent calls */
    move(&myDog.moveTrait);
    CHECK(myDog.moveCalled == 1);
    CHECK(myRobot.moveCalled == 0);

    make_sound(&myRobot.soundTrait);
    CHECK(myRobot.soundCalled == 1);
    CHECK(myDog.soundCalled == 0);
}
