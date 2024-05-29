#ifndef HERO_LIST_CPP
#define HERO_LIST_CPP

#include "Hero.h"
#include "Specialty_List.cpp"
#include "Secondary_Skill_List.cpp"

namespace Hero_List
{
    Hero None(      "None",      Hero::Gender::Male,   Hero::Role::Might, Faction::Neutral,    Team::Neutral, 0, 0, 0, 0, 0, 0, Specialty_List::None,    Morale::Neutral,  Luck::Neutral, { false, false, false, false }, false );
    Hero Him(       "Him",       Hero::Gender::Male,   Hero::Role::Might, Faction::Neutral,    Team::Red,     0, 0, 8, 7, 0, 0, Specialty_List::None,    Morale::Neutral,  Luck::Neutral, { false, false, false, false }, false );
    Hero Her(       "Her",       Hero::Gender::Female, Hero::Role::Might, Faction::Neutral,    Team::Tan,     0, 0, 2, 3, 0, 0, Specialty_List::None,    Morale::Terrible, Luck::Superb,  { false, false, false, false }, false );

    // Castle
    Hero Orrin(     "Orrin",     Hero::Gender::Male,   Hero::Role::Might, Faction::Castle,     Team::Neutral, 1, 0, 2, 2, 1, 1, Specialty_List::Archery, Morale::Neutral,  Luck::Neutral, { false, false, false, false }, false );

    // Stronghold
    Hero Crag_Hack( "Crag Hack", Hero::Gender::Male,   Hero::Role::Might, Faction::Stronghold, Team::Neutral, 1, 0, 4, 0, 1, 1, Specialty_List::Offense, Morale::Neutral,  Luck::Neutral, { false, false, false, false }, false );

    // Fortress
    Hero Tazar(     "Tazar",     Hero::Gender::Male,   Hero::Role::Might, Faction::Fortress,   Team::Neutral, 1, 0, 0, 4, 1, 1, Specialty_List::Armorer, Morale::Neutral,  Luck::Neutral, { false, false, false, false }, false );
}

#endif