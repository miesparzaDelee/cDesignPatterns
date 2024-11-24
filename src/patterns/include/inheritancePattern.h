#ifndef INHERITANCE_PATTERN_H
#define INHERITANCE_PATTERN_H

#include <stdint.h>
#include "linked_list.h"

/** @file inheritancePattern.h
 *  @brief Demonstrates an inheritance pattern in C using struct composition.
 *
 *  This module illustrates how to extend the functionality of a linked list node
 *  by embedding it into another structure. The `customLinkedNode` struct extends
 *  the base linked list node (`sLinL_node`) by adding a custom ID field, enabling
 *  additional functionality while maintaining compatibility with the linked list
 *  operations provided by the `linked_list` module.
 */

 /**
  * @brief Represents a custom linked list node with an extended ID field.
  *
  * The `customLinkedNode` embeds a basic linked list node structure (`sLinL_node`)
  * and adds a custom ID field. This design enables the use of standard linked list
  * operations while allowing additional data to be stored in each node.
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
 * Initializes the `id` field to 0 and prepares the node for use in a linked list.
 *
 * @param me Pointer to the `customLinkedNode` to initialize.
 */
void cln_Init(hCustomLinkedNode me);

#endif // INHERITANCE_PATTERN_H
