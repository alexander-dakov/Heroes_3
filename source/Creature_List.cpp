#ifndef CREATURE_LIST_CPP
#define CREATURE_LIST_CPP

#include "Creature.h"

namespace Creature_List
{
    //                                 name,              faction,           lvl, upg, growth,2_hex, A,  D, S, mD, MD, hp, speed,   morale,          luck,       fight, ai, { gold, m, s, c, g },undead,unliv,flying,ranged,dragon,att_all );

    //Necropolis
    const Creature Skeleton (         "Skeleton",         Faction::Necropolis, 1, false, 12, false,  5,  4, 0,  1,  3,   6,  4, Morale::Neutral, Luck::Neutral,   75,   60, {   60, 0, 0, 0, 0 }, true, false, false, false, false, false );
    const Creature Skeleton_Warrior ( "Skeleton Warrior", Faction::Necropolis, 1, true,  12, false,  6,  6, 0,  1,  3,   6,  5, Morale::Neutral, Luck::Neutral,   85,   85, {   70, 0, 0, 0, 0 }, true, false, false, false, false, false );
    const Creature Walking_Dead (     "Walking Dead",     Faction::Necropolis, 2, false,  8, false,  5,  5, 0,  2,  3,  15,  3, Morale::Neutral, Luck::Neutral,  140,   98, {  100, 0, 0, 0, 0 }, true, false, false, false, false, false );
    const Creature Zombie (           "Zombie",           Faction::Necropolis, 2, true,   8, false,  5,  5, 0,  2,  3,  20,  4, Morale::Neutral, Luck::Neutral,  160,  128, {  125, 0, 0, 0, 0 }, true, false, false, false, false, false );
    const Creature Wight (            "Wight",            Faction::Necropolis, 3, false,  7, false,  7,  7, 0,  3,  5,  18,  5, Morale::Neutral, Luck::Neutral,  231,  252, {  200, 0, 0, 0, 0 }, true, false, true,  false, false, false );
    const Creature Wraith (           "Wraith",           Faction::Necropolis, 3, true,   7, false,  7,  7, 0,  3,  5,  18,  7, Morale::Neutral, Luck::Neutral,  252,  315, {  230, 0, 0, 0, 0 }, true, false, true,  false, false, false );
    const Creature Vampire (          "Vampire",          Faction::Necropolis, 4, false,  4, false, 10,  9, 0,  5,  8,  30,  6, Morale::Neutral, Luck::Neutral,  518,  555, {  360, 0, 0, 0, 0 }, true, false, true,  false, false, false );
    const Creature Vampire_Lord (     "Vampire Lord",     Faction::Necropolis, 4, true,   4, false, 10, 10, 0,  5,  8,  40,  9, Morale::Neutral, Luck::Neutral,  652,  783, {  500, 0, 0, 0, 0 }, true, false, true,  false, false, false );
    const Creature Lich (             "Lich",             Faction::Necropolis, 5, false,  3, false, 13, 10, 0, 11, 13,  30,  6, Morale::Neutral, Luck::Neutral,  742,  848, {  550, 0, 0, 0, 0 }, true, false, false, true,  false, false );
    const Creature Power_Lich (       "Power Lich",       Faction::Necropolis, 5, true,   3, false, 13, 10, 0, 11, 15,  40,  7, Morale::Neutral, Luck::Neutral,  889, 1079, {  600, 0, 0, 0, 0 }, true, false, false, true,  false, false );
    const Creature Black_Knight (     "Black Knight",     Faction::Necropolis, 6, false,  2, true,  16, 16, 0, 15, 30, 120,  7, Morale::Neutral, Luck::Neutral, 1753, 2087, { 1200, 0, 0, 0, 0 }, true, false, false, false, false, false );
    const Creature Dread_Knight (     "Dread Knight",     Faction::Necropolis, 6, true,   2, true,  18, 18, 0, 15, 30, 120,  9, Morale::Neutral, Luck::Neutral, 2029, 2382, { 1500, 0, 0, 0, 0 }, true, false, false, false, false, false );
    const Creature Bone_Dragon (      "Bone Dragon",      Faction::Necropolis, 7, false,  1, true,  17, 15, 0, 25, 50, 150,  9, Morale::Neutral, Luck::Neutral, 2420, 3388, { 1800, 0, 0, 0, 0 }, true, false, true,  false, true,  false );
    const Creature Ghost_Dragon (     "Ghost Dragon",     Faction::Necropolis, 7, true,   1, true,  19, 17, 0, 25, 50, 200, 14, Morale::Neutral, Luck::Neutral, 3228, 4696, { 3000, 1, 0, 0, 0 }, true, false, true,  false, true,  false );

    
}

#endif