#include <stdio.h>
#include <stdarg.h>
#include "CppUTest/TestHarness.h"

extern "C" {
    #include "linked_list.h"
}

// Global static variable for iteration count
static int iterationCount;

// Static callback function
static void forEachCallback(hLinL_node node)
{
    iterationCount++; // Increment the iteration counter
}

TEST_GROUP(LinkedLists)
{
    struct sLinL_list sTestList;
    hLinL_list hTestList;

    LinL_iterateCallback cb;

    void setup()
    {
        // Initialize the list and callback
        hTestList = &sTestList;
        cb.forEachCb = forEachCallback;
        LinL_init(hTestList, &cb);
    }

    void teardown()
    {
        // Cleanup if necessary
    }
};


TEST(LinkedLists, init)
{
   
    CHECK(hTestList != NULL); 
    CHECK(hTestList->head == NULL); 
    CHECK(hTestList->tail == NULL); 
    CHECK(hTestList->foreachIterator == &cb);
    CHECK(hTestList->foreachIterator->forEachCb == forEachCallback);
}

TEST(LinkedLists, AppendSingleNode)
{
    struct sLinL_node node1;

    // Append a single node
    bool result = LinL_append(hTestList, &node1);

    // Validate the results
    CHECK(result == true); // Append should succeed
    CHECK(hTestList->head == &node1); // Head should point to the new node
    CHECK(hTestList->tail == &node1); // Tail should also point to the new node
    CHECK(hTestList->head->next == NULL); // New node should not point to anything
}

TEST(LinkedLists, AppendNullList)
{
    struct sLinL_node node1;

    // Attempt to append with a NULL list handle
    bool result = LinL_append(NULL, &node1);

    // Validate the result
    CHECK(result == false); // Append should fail
}

TEST(LinkedLists, AppendNullNode)
{
    // Attempt to append a NULL node to the list
    bool result = LinL_append(hTestList, NULL);

    // Validate the result
    CHECK(result == false); // Append should fail
}

TEST(LinkedLists, RemoveFromEmptyList)
{
    struct sLinL_node node1;

    // Attempt to remove from an empty list
    bool result = LinL_remove(hTestList, &node1);

    // Validate the result
    CHECK(result == false); // Remove should fail
}

TEST(LinkedLists, RemoveHeadNode)
{
    struct sLinL_node node1;

    // Append a single node
    LinL_append(hTestList, &node1);

    // Attempt to remove the head node
    bool result = LinL_remove(hTestList, &node1);

    // Validate the results
    CHECK(result == true); // Remove should succeed
    CHECK(hTestList->head == NULL); // Head should be NULL after removal
    CHECK(hTestList->tail == NULL); // Tail should also be NULL after removal
}

TEST(LinkedLists, RemoveMiddleNode)
{
    struct sLinL_node node1, node2, node3;

    // Append three nodes to the list
    LinL_append(hTestList, &node1);
    LinL_append(hTestList, &node2);
    LinL_append(hTestList, &node3);

    // Attempt to remove the middle node
    bool result = LinL_remove(hTestList, &node2);

    // Validate the results
    CHECK(result == true); // Removal should succeed
    CHECK(hTestList->head == &node1); // Head should still point to the first node
    CHECK(hTestList->tail == &node3); // Tail should still point to the last node
    CHECK(hTestList->head->next == &node3); // The first node should now point to the last node
}

TEST(LinkedLists, RemoveTailNode)
{
    struct sLinL_node node1, node2, node3;

    // Append three nodes to the list
    LinL_append(hTestList, &node1);
    LinL_append(hTestList, &node2);
    LinL_append(hTestList, &node3);

    // Attempt to remove the tail node
    bool result = LinL_remove(hTestList, &node3);

    // Validate the results
    CHECK(result == true); // Removal should succeed
    CHECK(hTestList->head == &node1); // Head should still point to the first node
    CHECK(hTestList->tail == &node2); // Tail should now point to the second node
    CHECK(hTestList->tail->next == NULL); // The new tail should not point to anything
}

TEST(LinkedLists, RemoveNodeNotInList)
{
    struct sLinL_node node1, node2, node3, nodeNotInList;

    // Append three nodes to the list
    LinL_append(hTestList, &node1);
    LinL_append(hTestList, &node2);
    LinL_append(hTestList, &node3);

    // Attempt to remove a node not in the list
    bool result = LinL_remove(hTestList, &nodeNotInList);

    // Validate the results
    CHECK(result == false); // Removal should fail
    CHECK(hTestList->head == &node1); // Head should still point to the first node
    CHECK(hTestList->tail == &node3); // Tail should still point to the last node
    CHECK(hTestList->head->next == &node2); // Links in the list should remain intact
    CHECK(hTestList->head->next->next == &node3); // The second node should still point to the third node
}

TEST(LinkedLists, IterateEmptyList)
{
    // Initialize iteration counter
    iterationCount = 0;

    // Attempt to iterate over an empty list
    LinL_iterate(hTestList);

    // Validate the callback was not called
    CHECK(iterationCount == 0);
}

TEST(LinkedLists, IterateWithNodes)
{
    struct sLinL_node node1, node2, node3;

    // Append nodes to the list
    LinL_append(hTestList, &node1);
    LinL_append(hTestList, &node2);
    LinL_append(hTestList, &node3);

    // Initialize iteration counter
    iterationCount = 0;

    // Iterate through the list
    LinL_iterate(hTestList);

    // Validate the callback was called for each node
    CHECK(iterationCount == 3);
}

static hLinL_node lastVisitedNode = NULL;

static void orderTestCallback(hLinL_node node)
{
    CHECK(lastVisitedNode != node); // Ensure no node is visited twice
    lastVisitedNode = node; // Track the last visited node
}

TEST(LinkedLists, IterateNodeOrder)
{
    cb.forEachCb = orderTestCallback;
    LinL_init(hTestList, &cb);
    struct sLinL_node node1, node2, node3;

    // Append nodes to the list
    LinL_append(hTestList, &node1);
    LinL_append(hTestList, &node2);
    LinL_append(hTestList, &node3);

    // Initialize tracker
    lastVisitedNode = NULL;

    // Iterate through the list
    LinL_iterate(hTestList);
}

