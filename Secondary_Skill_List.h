#ifndef SECONDARY_SKILL_LIST_H
#define SECONDARY_SKILL_LIST_H

#include "Secondary_Skill.h"

namespace Secondary_Skill_List
{
    Secondary_Skill None(             Skill_level::None,     "None",    "None");

    // Archery
    Secondary_Skill Basic_Archery(    Skill_level::Basic,    "Archery", "Increases the damage done by range attacking creatures by 10%.");
    Secondary_Skill Advanced_Archery( Skill_level::Advanced, "Archery", "Increases the damage done by range attacking creatures by 25%.");
    Secondary_Skill Expert_Archery(   Skill_level::Expert,   "Archery", "Increases the damage done by range attacking creatures by 50%.");

    // Armorer
    Secondary_Skill Basic_Armorer(    Skill_level::Basic,    "Armorer", "Reduces all damage inflicted against the hero's troops by 5%.");
    Secondary_Skill Advanced_Armorer( Skill_level::Advanced, "Armorer", "Reduces all damage inflicted against the hero's troops by 10%.");
    Secondary_Skill Expert_Armorer(   Skill_level::Expert,   "Armorer", "Reduces all damage inflicted against the hero's troops by 15%.");

    // Offense
    Secondary_Skill Basic_Offense(    Skill_level::Basic,    "Offense", "Increases all hand-to-hand damage inflicted by the hero's troops by 10%.");
    Secondary_Skill Advanced_Offense( Skill_level::Advanced, "Offense", "Increases all hand-to-hand damage inflicted by the hero's troops by 20%.");
    Secondary_Skill Expert_Offense(   Skill_level::Expert,   "Offense", "Increases all hand-to-hand damage inflicted by the hero's troops by 30%.");

}

#endif