#include "inheritancePattern.h"
#include "common.h"

#include <stdio.h>

void cln_Init(hCustomLinkedNode me)
{
	me->id = 0;
}

static void incrementCompositeTraits_DoX(hTraitX trait);
static void incrementCompositeTraits_DoY(hTraitY trait);

void incrementCompositeTraits_Init(incrementCompositeTraits* me)
{
	me->incrementXtrait = (traitX){ .do_x = incrementCompositeTraits_DoX };
	me->incrementYtrait = (traitY){ .do_y = incrementCompositeTraits_DoY };
	me->counterX = 0;
	me->counterY = 0;
}

static void incrementCompositeTraits_DoX(hTraitX trait) {
	incrementCompositeTraits* me = CONTAINER_OF(trait, incrementCompositeTraits, incrementXtrait);
	me->counterX++;
}
static void incrementCompositeTraits_DoY(hTraitY trait) {
	incrementCompositeTraits* me = CONTAINER_OF(trait, incrementCompositeTraits, incrementYtrait);
	me->counterY++;
}

static void otherCompositeTraits_DoX(hTraitX trait);
static void otherCompositeTraits_DoY(hTraitY trait);

void otherCompositeTraits_Init(otherCompositeTraits* me)
{
	me->sumFiveTrait = (traitX){ .do_x = otherCompositeTraits_DoX };
	me->multiplyTwoTrait = (traitY){ .do_y = otherCompositeTraits_DoY };
	me->sumFive = 0;
	me->multiplyTwo = 1;
}

static void otherCompositeTraits_DoX(hTraitX trait) {
	otherCompositeTraits* me = CONTAINER_OF(trait, otherCompositeTraits, sumFiveTrait);
	me->sumFive += 5;
}
static void otherCompositeTraits_DoY(hTraitY trait) {
	otherCompositeTraits* me = CONTAINER_OF(trait, otherCompositeTraits, multiplyTwoTrait);
	me->multiplyTwo *= 2;
}