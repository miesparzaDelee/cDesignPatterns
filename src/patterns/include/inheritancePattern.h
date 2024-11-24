#ifndef INHERITANCE_PATTERN_H
#define INHERITANCE_PATTERN_H

#include <stdint.h>
#include "linked_list.h"

/** @file inheritancePattern.h
 *  @brief Demonstrates an inheritance and traits-based pattern in C.
 *
 *  This module showcases how to implement "inheritance" and "traits" in C using struct composition.
 *  It provides:
 *  - A base linked list node (`customLinkedNode`) with extended functionality.
 *  - Two distinct composite objects (`incrementCompositeTraits` and `otherCompositeTraits`)
 *    demonstrating different behaviors via traits.
 *
 *  ### Key Features
 *  - Reusability: Common functionality encapsulated in traits (`traitX` and `traitY`).
 *  - Flexibility: Composite objects independently define their own behaviors.
 *  - Integration: Combines with linked list functionality for hierarchical structures.
 */

 /// @name Linked List Extension
 /// @{
 /**
  * @brief Represents a custom linked list node extending the base functionality.
  *
  * The `customLinkedNode` extends the basic linked list node structure (`sLinL_node`)
  * by adding an `id` field. This allows each node to store additional data while
  * still behaving as a standard linked list node.
  */
typedef struct
{
    uint32_t id;               /**< Custom ID field for the node. */
    struct sLinL_node baseNode; /**< Base linked list node. */
} customLinkedNode;

typedef customLinkedNode* hCustomLinkedNode;

/**
 * @brief Initializes a custom linked list node.
 *
 * @param me Pointer to the `customLinkedNode` to initialize.
 */
void cln_Init(hCustomLinkedNode me);
/// @}

/// @name Trait Definitions
/// @{
/**
 * @brief Represents TraitX functionality.
 *
 * This trait defines a generic operation `do_x` that can be implemented
 * differently in derived objects.
 */
typedef struct traitX
{
    void (*do_x)(struct traitX* me); /**< Function pointer for TraitX operation. */
} traitX;

typedef struct traitX* hTraitX;

/**
 * @brief Invokes the TraitX operation.
 *
 * @param me Pointer to the `traitX` instance to invoke.
 */
static inline void traitX_do(hTraitX me)
{
    me->do_x(me);
}

/**
 * @brief Represents TraitY functionality.
 *
 * This trait defines a generic operation `do_y` that can be implemented
 * differently in derived objects.
 */
typedef struct traitY
{
    void (*do_y)(struct traitY* me); /**< Function pointer for TraitY operation. */
} traitY;

typedef struct traitY* hTraitY;

/**
 * @brief Invokes the TraitY operation.
 *
 * @param me Pointer to the `traitY` instance to invoke.
 */
static inline void traitY_do(hTraitY me)
{
    me->do_y(me);
}
/// @}

/// @name Increment Composite Traits
/// @{
/**
 * @brief Composite object implementing increment behavior for TraitX and TraitY.
 *
 * - `TraitX` increments `counterX` each time `do_x` is invoked.
 * - `TraitY` increments `counterY` each time `do_y` is invoked.
 */
typedef struct
{
    traitX incrementXtrait; /**< TraitX implementation for incrementing. */
    traitY incrementYtrait; /**< TraitY implementation for incrementing. */
    uint32_t counterX;      /**< Counter for TraitX operations. */
    uint32_t counterY;      /**< Counter for TraitY operations. */
} incrementCompositeTraits;

/**
 * @brief Initializes an `incrementCompositeTraits` object.
 *
 * @param me Pointer to the `incrementCompositeTraits` to initialize.
 */
void incrementCompositeTraits_Init(incrementCompositeTraits* me);
/// @}

/// @name Other Composite Traits
/// @{
/**
 * @brief Composite object implementing summing and multiplying behavior.
 *
 * - `TraitX` adds 5 to `sumFive` each time `do_x` is invoked.
 * - `TraitY` multiplies `multiplyTwo` by 2 each time `do_y` is invoked.
 */
typedef struct
{
    traitX sumFiveTrait;    /**< TraitX implementation for summing. */
    traitY multiplyTwoTrait; /**< TraitY implementation for multiplying. */
    uint32_t sumFive;       /**< Accumulator for summing operations. */
    uint32_t multiplyTwo;   /**< Accumulator for multiplying operations. */
} otherCompositeTraits;

/**
 * @brief Initializes an `otherCompositeTraits` object.
 *
 * @param me Pointer to the `otherCompositeTraits` to initialize.
 */
void otherCompositeTraits_Init(otherCompositeTraits* me);
/// @}

#endif // INHERITANCE_PATTERN_H
