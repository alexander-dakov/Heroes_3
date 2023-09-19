#ifndef HERO_LIST_CPP
#define HERO_LIST_CPP

#include "Hero.h"
#include "Specialty_List.cpp"
#include "Secondary_Skill_List.cpp"

namespace Hero_List
{
    Hero None("None", Gender::Male, Class::Might, Faction::Neutral, Team::None, 0, 0, 0, 0, 0, 0, Specialty_List::None, Morale::Neutral, Luck::Neutral, false, false, false, false,  false);
}

#endif