#include <stdio.h>
#include <stdarg.h>
#include "CppUTest/TestHarness.h"

extern "C" {
#include "inheritancePattern.h"
#include "common.h"
}


TEST_GROUP(inheritancePattern)
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

// Static callback function
static void forEachCallback(hLinL_node baseNode)
{
    static uint32_t id = 1;
    customLinkedNode * object = CONTAINER_OF(baseNode, customLinkedNode, baseNode);
    object->id = id;
    id++;
}

TEST(inheritancePattern, inheritedBehavesAsBase)
{
    struct sLinL_list sObjectList;
    hLinL_list hObjectList = &sObjectList;
    LinL_iterateCallback cb = { forEachCallback };
    LinL_init(hObjectList, &cb);

    customLinkedNode customNode1;
    customLinkedNode customNode2;
    customLinkedNode customNode3;


    LinL_append(hObjectList, &customNode1.baseNode);
    LinL_append(hObjectList, &customNode2.baseNode);
    LinL_append(hObjectList, &customNode3.baseNode);

    LinL_iterate(hObjectList);

    CHECK(customNode1.id == 1);
    CHECK(customNode2.id == 2);
    CHECK(customNode3.id == 3);
}