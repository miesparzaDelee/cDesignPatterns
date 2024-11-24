/**
 * @file linked_list.h
 * @brief A lightweight static linked list for embedded systems.
 *
 * This module provides a simple and efficient linked list implementation that relies on static
 * memory management, making it suitable for resource-constrained environments. It supports
 * basic operations like adding, removing, and iterating over nodes using customizable callbacks.
 *
 * Designed for simplicity and minimal dependencies, this module ensures predictable behavior
 * without dynamic memory allocation, leaving memory management to the user.
 */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>

 /**
  * @brief Handle to a linked list node.
  *
  * This is a pointer to the internal structure representing a node in the linked list.
  */
struct sLinL_node;
typedef struct sLinL_node* hLinL_node;

/**
 * @brief Handle to a linked list.
 *
 * This is a pointer to the internal structure representing the linked list.
 */
struct sLinL_list;
typedef struct sLinL_list* hLinL_list;

/**
 * @brief Callback function type for iterating over linked list nodes.
 *
 * @param node The current node being iterated.
 */
typedef void (*sLinL_iterate_cb)(hLinL_node baseNode);

/**
 * @brief Struct containing iteration callback details.
 */
typedef struct
{
    sLinL_iterate_cb forEachCb; /**< Callback function to invoke during iteration. */
} LinL_iterateCallback;

#include "private_linked_list.h"

/**
 * @brief Initializes a linked list.
 *
 * @param me Pointer to the linked list handle to initialize.
 * @param cb Pointer to a LinL_iterateCallback structure containing the callback function.
 *
 * @note If `cb` is NULL, iteration will not be possible until a valid callback is assigned.
 */
void LinL_init(hLinL_list me, LinL_iterateCallback* cb);

/**
 * @brief Appends a node to the linked list.
 *
 * @param me Pointer to the linked list handle.
 * @param node Pointer to the node to append.
 *
 * @return `true` if the node was successfully appended, `false` if the list or node is invalid.
 *
 * @note The `node` must not already be part of another linked list.
 * @note The `node->next` pointer is updated to NULL internally.
 */
bool LinL_append(hLinL_list me, hLinL_node baseNode);

/**
 * @brief Removes a node from the linked list.
 *
 * @param me Pointer to the linked list handle.
 * @param node Pointer to the node to remove.
 *
 * @return `true` if the node was successfully removed, `false` if the node was not found or the list is invalid.
 *
 * @note The `node` is not freed; memory management is the responsibility of the caller.
 */
bool LinL_remove(hLinL_list me, hLinL_node baseNode);

/**
 * @brief Iterates over all nodes in the linked list and invokes the callback function for each.
 *
 * @param me Pointer to the linked list handle.
 *
 * @note If no callback function is assigned (`me->foreachIterator->forEachCb` is NULL), the function does nothing.
 * @note Iteration stops when all nodes have been visited or if the list is empty.
 */
void LinL_iterate(hLinL_list me);

#endif
