#ifndef RESOURCES_H
#define RESOURCES_H

#include "../utilities/types.h"

struct Resources
{
    uint32_t Gold;
    uint32_t Wood;
    uint32_t Ore;
    uint32_t Mercury;
    uint32_t Sulfur;
    uint32_t Crystals;
    uint32_t Gems;

    Resources(uint32_t gold = 0, uint32_t mercury = 0, uint32_t sulfur = 0, uint32_t crystals = 0, uint32_t gems = 0, uint32_t wood = 0, uint32_t ore = 0 ) :
             Gold(gold), Mercury(mercury), Sulfur(sulfur), Crystals(crystals), Gems(gems), Wood(wood), Ore(ore)
             {};
};

#endif