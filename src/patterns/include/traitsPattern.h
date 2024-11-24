#ifndef TRAITS_PATTERN_H
#define TRAITS_PATTERN_H

#include <stdint.h>

/** @file traitsPattern.h
 *  @brief Demonstrates the traits pattern in C for reusable behavior.
 *
 *  This module implements the traits pattern, which allows the definition of
 *  modular, reusable behaviors that can be shared across unrelated entities.
 *  The `Move` and `MakeSound` traits are defined as independent behaviors and
 *  can be implemented by any entity, such as `Dog` or `Robot`, without requiring
 *  a hierarchical relationship.
 */

 /**
  * @brief Represents a trait for "Move" behavior.
  *
  * The `Move` trait defines an abstract behavior (`do_x`) that can be implemented
  * differently by various entities. This enables reusable movement functionality
  * without enforcing a parent-child relationship.
  */
typedef struct Move {
    void (*move)(struct Move* self); /**< Pointer to the implementation of the move behavior. */
} Move;

typedef Move* hMove;

/**
 * @brief Invokes the move behavior.
 *
 * Calls the `move` function associated with the given `Move` trait.
 *
 * @param self Pointer to the `Move` trait instance.
 */
static inline void move(hMove self) {
    self->move(self);
}

/**
 * @brief Represents a trait for "MakeSound" behavior.
 *
 * The `MakeSound` trait defines an abstract behavior (`make_sound`) that can be
 * implemented differently by various entities. This enables reusable sound-making
 * functionality without enforcing a parent-child relationship.
 */
typedef struct MakeSound {
    void (*make_sound)(struct MakeSound* self); /**< Pointer to the implementation of the make_sound behavior. */
} MakeSound;

typedef MakeSound* hMakeSound;

/**
 * @brief Invokes the make_sound behavior.
 *
 * Calls the `make_sound` function associated with the given `MakeSound` trait.
 *
 * @param self Pointer to the `MakeSound` trait instance.
 */
static inline void make_sound(hMakeSound self) {
    self->make_sound(self);
}

/**
 * @brief Represents a Dog entity that implements `Move` and `MakeSound` traits.
 *
 * The `Dog` entity provides specific implementations of the `Move` and `MakeSound`
 * traits, enabling it to perform actions such as "running" and "barking." It also
 * includes indicators to track whether the respective behaviors have been invoked.
 */
typedef struct Dog {
    Move moveTrait;          /**< Implements the `Move` trait. */
    MakeSound soundTrait;    /**< Implements the `MakeSound` trait. */
    uint8_t moveCalled;      /**< Tracks if the `Move` trait was invoked. */
    uint8_t soundCalled;     /**< Tracks if the `MakeSound` trait was invoked. */
} Dog;

/**
 * @brief Initializes a Dog entity with its traits.
 *
 * @param dog Pointer to the `Dog` instance to initialize.
 */
void Dog_Init(Dog* dog);

/**
 * @brief Represents a Robot entity that implements `Move` and `MakeSound` traits.
 *
 * The `Robot` entity provides specific implementations of the `Move` and `MakeSound`
 * traits, enabling it to perform actions such as "wheeling forward" and "beeping."
 * It also includes indicators to track whether the respective behaviors have been invoked.
 */
typedef struct Robot {
    Move moveTrait;          /**< Implements the `Move` trait. */
    MakeSound soundTrait;    /**< Implements the `MakeSound` trait. */
    uint8_t moveCalled;      /**< Tracks if the `Move` trait was invoked. */
    uint8_t soundCalled;     /**< Tracks if the `MakeSound` trait was invoked. */
} Robot;

/**
 * @brief Initializes a Robot entity with its traits.
 *
 * @param robot Pointer to the `Robot` instance to initialize.
 */
void Robot_Init(Robot* robot);

#endif // TRAITS_PATTERN_H
