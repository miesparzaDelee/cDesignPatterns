#include "linked_list.h"
#include <stddef.h>

void LinL_init(hLinL_list me, LinL_iterateCallback* cb)
{
    if (me == NULL) return; // Validar entrada

    me->head = NULL; // Inicializar cabeza como NULL
    me->tail = NULL; // Inicializar cola como NULL

    if (cb != NULL) {
        me->foreachIterator = cb; // Copiar el callback si se proporciona
    }
    else {
        me->foreachIterator = NULL; // Asegurarse de que sea NULL si no se proporciona
    }
}

bool LinL_append(hLinL_list me, hLinL_node baseNode)
{
    if (!me || !baseNode) return false; // Validate inputs

    baseNode->next = NULL; // Ensure the new node points to NULL

    if (me->head == NULL) {
        // If the list is empty, the new node becomes both head and tail
        me->head = baseNode;
        me->tail = baseNode;
    }
    else {
        // Link the new node at the end of the list
        me->tail->next = baseNode;
        me->tail = baseNode; // Update the tail pointer
    }

    return true; // Return true if the node was successfully added
}

bool LinL_remove(hLinL_list me, hLinL_node baseNode) 
{
    if (!me || !baseNode || me->head == NULL) return false; // Validate inputs

    hLinL_node current = me->head;
    hLinL_node previous = NULL;

    while (current != NULL) {
        if (current == baseNode) { // Node found
            if (previous == NULL) {
                me->head = current->next; // Remove head
            }
            else {
                previous->next = current->next; // Bypass the current node
            }

            if (current == me->tail) {
                me->tail = previous; // Update tail if the last node is removed
            }
            return true;
        }
        previous = current;
        current = current->next;
    }

    return false; // Node not found in the list
}

void LinL_iterate(hLinL_list me) {
    if (!me || !me->head || !me->foreachIterator->forEachCb) return; // Validate inputs

    hLinL_node current = me->head;

    while (current != NULL) {
        me->foreachIterator->forEachCb(current); // Call the callback with the current node
        current = current->next; // Move to the next node
    }
}