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


TEST(inheritancePattern, CompositeTraitsBehavior)
{
    incrementCompositeTraits composite;

    /* Initialize Composite Traits */
    incrementCompositeTraits_Init(&composite);

    /* Use Trait X and Trait Y */
    hTraitX traitX = &composite.incrementXtrait;
    hTraitY traitY = &composite.incrementYtrait;

    /* Test Trait X Behavior */
    traitX_do(traitX); /* Call TraitX's method */
    CHECK(composite.counterX == 1); /* Verify TraitX counter is incremented */

    /* Test Trait Y Behavior */
    traitY_do(traitY); /* Call TraitY's method */
    CHECK(composite.counterY == 1); /* Verify TraitY counter is incremented */

    /* Call TraitX and TraitY again */
    traitX_do(traitX);
    traitY_do(traitY);

    /* Validate counters again */
    CHECK(composite.counterX == 2); /* Counter for TraitX should be 2 */
    CHECK(composite.counterY == 2); /* Counter for TraitY should be 2 */
}

TEST(inheritancePattern, MultipleObjectsWithTraits)
{
    /* Initialize first object (CompositeTraits) */
    incrementCompositeTraits increment;
    incrementCompositeTraits_Init(&increment);

    /* Initialize second object (AnotherCompositeTraits) */
    otherCompositeTraits other;
    otherCompositeTraits_Init(&other);

    /* Use Trait X and Trait Y for CompositeTraits */
    hTraitX incrementTraitX = &increment.incrementXtrait;
    hTraitY incrementTraitY = &increment.incrementYtrait;

    /* Use Trait X and Trait Y for AnotherCompositeTraits */
    hTraitX otherTraitX = &other.sumFiveTrait;
    hTraitY otherTraitY = &other.multiplyTwoTrait;

    /* Test CompositeTraits behavior */
    traitX_do(incrementTraitX); /* Call TraitX's method */
    CHECK(increment.counterX == 1); /* Verify counter increment */
    traitY_do(incrementTraitY); /* Call TraitY's method */
    CHECK(increment.counterY == 1); /* Verify counter increment */

    /* Test AnotherCompositeTraits behavior */
    traitX_do(otherTraitX); /* Call TraitX's method */
    CHECK(other.sumFive == 5); /* Verify sum updated */
    traitY_do(otherTraitY); /* Call TraitY's method */
    CHECK(other.multiplyTwo == 2); /* Verify product updated */
}
