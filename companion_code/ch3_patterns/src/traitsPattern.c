#include "traitsPattern.h"
#include "common.h" // Contains the CONTAINER_OF macro

/* Dog Move Implementation */
static void dog_move(Move* self) {
    Dog* dog = CONTAINER_OF(self, Dog, moveTrait); /* Use CONTAINER_OF to get parent */
    dog->moveCalled = 1; /* Mark move as called */
}

/* Dog Sound Implementation */
static void dog_make_sound(MakeSound* self) {
    Dog* dog = CONTAINER_OF(self, Dog, soundTrait); /* Use CONTAINER_OF to get parent */
    dog->soundCalled = 1; /* Mark sound as called */
}

/* Initialize Dog */
void Dog_Init(Dog* dog) {
    dog->moveCalled = 0; /* Initialize indicators */
    dog->soundCalled = 0;
    dog->moveTrait = (Move){ .move = dog_move };
    dog->soundTrait = (MakeSound){ .make_sound = dog_make_sound };
}

/* Robot Move Implementation */
static void robot_move(Move* self) {
    Robot* robot = CONTAINER_OF(self, Robot, moveTrait); /* Use CONTAINER_OF to get parent */
    robot->moveCalled = 1; /* Mark move as called */
}

/* Robot Sound Implementation */
static void robot_make_sound(MakeSound* self) {
    Robot* robot = CONTAINER_OF(self, Robot, soundTrait); /* Use CONTAINER_OF to get parent */
    robot->soundCalled = 1; /* Mark sound as called */
}

/* Initialize Robot */
void Robot_Init(Robot* robot) {
    robot->moveCalled = 0; /* Initialize indicators */
    robot->soundCalled = 0;
    robot->moveTrait = (Move){ .move = robot_move };
    robot->soundTrait = (MakeSound){ .make_sound = robot_make_sound };
}
