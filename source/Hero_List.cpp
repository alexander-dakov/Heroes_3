#ifndef HERO_LIST_CPP
#define HERO_LIST_CPP

#include "Hero.h"
#include "Specialty_List.cpp"
#include "Secondary_Skill_List.cpp"

namespace Hero_List
{
    Hero None("None", Gender::Male, Class::Might, Faction::Neutral, Team::Neutral, 0, 0, 0, 0, 0, 0, Specialty_List::None, Morale::Neutral, Luck::Neutral, { false, false, false, false }, false );
    Hero Someone("Someone", Gender::Male, Class::Might, Faction::Neutral, Team::Neutral, 0, 0, 8, 7, 0, 0, Specialty_List::None, Morale::Terrible, Luck::Superb, { false, false, false, false }, false );

    // Castle
    Hero Orrin("Orrin", Gender::Male, Class::Might, Faction::Castle, Team::Neutral, 1, 0, 2, 2, 1, 1, Specialty_List::Archery, Morale::Neutral, Luck::Neutral, { false, false, false, false }, false );
}

#endif