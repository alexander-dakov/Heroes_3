#ifndef CREATURE_LIST_CPP
#define CREATURE_LIST_CPP

#include "Creature.h"

namespace Creature_List
{
    // Important - only Necropolis has its special abilities somewhat right. All special abilities should be implemented and the list creatures - updated.
    
    //                                 name,                faction,           lvl, upg, growth,2_hex, A,  D,  S, mD, MD, hp, speed,  morale,        luck,       fight, ai, { gold, m, s, c, g },undead, unliv,flying,ranged,dragon,att_all );
    // Castle
    const Creature Pikeman (          "Pikeman",            Faction::Castle,     1, false, 14, false,  4,  5,  0,  1,  3,  10,  4, Morale::Good, Luck::Neutral,  100,   80, {   60, 0, 0, 0, 0 }, false, false, false, false, false, false );
    const Creature Halberdier (       "Halberdier",         Faction::Castle,     1, true,  14, false,  6,  5,  0,  2,  3,  10,  5, Morale::Good, Luck::Neutral,  115,  115, {   75, 0, 0, 0, 0 }, false, false, false, false, false, false );
    const Creature Archer (           "Archer",             Faction::Castle,     2, false,  9, false,  6,  3, 12,  2,  3,  10,  4, Morale::Good, Luck::Neutral,  115,  126, {  100, 0, 0, 0, 0 }, false, false, false, true,  false, false );
    const Creature Marksman (         "Marksman",           Faction::Castle,     2, true,   9, false,  6,  3, 24,  2,  3,  10,  6, Morale::Good, Luck::Neutral,  115,  184, {  150, 0, 0, 0, 0 }, false, false, false, true,  false, false );
    const Creature Griffin (          "Griffin",            Faction::Castle,     3, false,  7, true,   8,  8,  0,  3,  6,  25,  6, Morale::Good, Luck::Neutral,  324,  351, {  200, 0, 0, 0, 0 }, false, false, true,  false, false, false );
    const Creature Royal_Griffin (    "Royal Griffin",      Faction::Castle,     3, true,   7, true,   9,  9,  0,  3,  6,  25,  9, Morale::Good, Luck::Neutral,  364,  448, {  240, 0, 0, 0, 0 }, false, false, true,  false, false, false );
    const Creature Swordsman (        "Swordsman",          Faction::Castle,     4, false,  4, false, 10, 12,  0,  6,  9,  35,  5, Morale::Good, Luck::Neutral,  445,  445, {  300, 0, 0, 0, 0 }, false, false, false, false, false, false );
    const Creature Crusader (         "Crusader",           Faction::Castle,     4, true,   4, false, 12, 12,  0,  7, 10,  35,  6, Morale::Good, Luck::Neutral,  588,  588, {  400, 0, 0, 0, 0 }, false, false, false, false, false, false );
    const Creature Monk (             "Monk",               Faction::Castle,     5, false,  3, false, 12,  7, 12, 10, 12,  30,  5, Morale::Good, Luck::Neutral,  485,  485, {  400, 0, 0, 0, 0 }, false, false, false, true,  false, false );
    const Creature Zealot (           "Zealot",             Faction::Castle,     5, true,   3, false, 12, 10, 24, 10, 12,  30,  7, Morale::Good, Luck::Neutral,  500,  750, {  450, 0, 0, 0, 0 }, false, false, false, true,  false, false );
    const Creature Cavalier (         "Cavalier",           Faction::Castle,     6, false,  2, true,  15, 15,  0, 15, 25, 100,  7, Morale::Good, Luck::Neutral, 1668, 1946, { 1000, 0, 0, 0, 0 }, false, false, false, false, false, false );
    const Creature Champion (         "Champion",           Faction::Castle,     6, true,   2, true,  16, 16,  0, 20, 25, 100,  9, Morale::Good, Luck::Neutral, 1800, 2100, { 1200, 0, 0, 0, 0 }, false, false, false, false, false, false );
    const Creature Angel (            "Angel",              Faction::Castle,     7, false,  1, true,  20, 20,  0, 50, 50, 200, 12, Morale::Good, Luck::Neutral, 3585, 5019, { 3000, 0, 0, 0, 1 }, false, false, true,  false, false, false );
    const Creature Archangel (        "Archangel",          Faction::Castle,     7, true,   1, true,  30, 30,  0, 50, 50, 250, 18, Morale::Good, Luck::Neutral, 6033, 8776, { 5000, 0, 0, 0, 3 }, false, false, true,  false, false, false );
    
    // Rampart
    const Creature Centaur (         "Centaur",             Faction::Rampart,    1, false, 14, true,   5,  3,  0,  2,  3,   8,  6, Morale::Good, Luck::Neutral,  100,  100, {   70, 0, 0, 0, 0 }, false, false, false, false, false, false );
    const Creature Centaur_Captain ( "Centaur Captain",     Faction::Rampart,    1, true,  14, true,   6,  3,  0,  2,  3,  10,  8, Morale::Good, Luck::Neutral,  138,  138, {   90, 0, 0, 0, 0 }, false, false, false, false, false, false );
    const Creature Dwarf (           "Dwarf",               Faction::Rampart,    2, false,  8, false,  6,  7,  0,  2,  4,  20,  3, Morale::Good, Luck::Neutral,  138,  138, {  120, 0, 0, 0, 0 }, false, false, false, false, false, false );
    const Creature Battle_Dwarf (    "Battle Dwarf",        Faction::Rampart,    2, true,   8, false,  7,  7,  0,  2,  4,  20,  5, Morale::Good, Luck::Neutral,  209,  209, {  150, 0, 0, 0, 0 }, false, false, false, false, false, false );
    const Creature Wood_Elf (        "Wood Elf",            Faction::Rampart,    3, false,  7, false,  9,  5, 12,  3,  5,  15,  6, Morale::Good, Luck::Neutral,  234,  234, {  200, 0, 0, 0, 0 }, false, false, false, true,  false, false );
    const Creature Grand_Elf (       "Grand Elf",           Faction::Rampart,    3, true,   7, false,  9,  5, 24,  3,  5,  15,  7, Morale::Good, Luck::Neutral,  331,  331, {  225, 0, 0, 0, 0 }, false, false, false, true,  false, false );
    const Creature Pegasus (         "Pegasus",             Faction::Rampart,    4, false,  5, true,   9,  8,  0,  5,  9,  30,  8, Morale::Good, Luck::Neutral,  518,  518, {  250, 0, 0, 0, 0 }, false, false, true,  false, false, false );
    const Creature Silver_Pegasus (  "Silver Pegasus",      Faction::Rampart,    4, true,   5, true,   9, 10,  0,  5,  9,  30, 12, Morale::Good, Luck::Neutral,  532,  532, {  275, 0, 0, 0, 0 }, false, false, true,  false, false, false );
    const Creature Dendroid_Guard (   "Dendroid Guard",     Faction::Rampart,    5, false,  3, false,  9, 12,  0, 10, 14,  55,  3, Morale::Good, Luck::Neutral,  517,  517, {  350, 0, 0, 0, 0 }, false, false, false, false, false, false );
    const Creature Dendroid_Soldier ( "Dendroid Soldier",   Faction::Rampart,    5, true,   3, false,  9, 12,  0, 10, 14,  65,  4, Morale::Good, Luck::Neutral,  765,  803, {  425, 0, 0, 0, 0 }, false, false, false, false, false, false );
    const Creature Unicorn (          "Unicorn",            Faction::Rampart,    6, false,  2, true,  15, 14,  0, 18, 22,  90,  7, Morale::Good, Luck::Neutral, 1548, 1806, {  850, 0, 0, 0, 0 }, false, false, false, false, false, false );
    const Creature War_Unicorn (      "War Unicorn",        Faction::Rampart,    6, true,   2, true,  15, 14,  0, 18, 22, 110,  9, Morale::Good, Luck::Neutral, 2030, 2030, {  950, 0, 0, 0, 0 }, false, false, false, false, false, false );
    const Creature Green_Dragon (     "Green Dragon",       Faction::Rampart,    7, false,  1, true,  18, 18,  0, 40, 50, 180, 10, Morale::Good, Luck::Neutral, 3654, 4872, { 2400, 0, 0, 1, 0 }, false, false, true,  false, true,  false );
    const Creature Gold_Dragon (      "Gold Dragon",        Faction::Rampart,    7, true,   1, true,  27, 27,  0, 40, 50, 250, 16, Morale::Good, Luck::Neutral, 6220, 8613, { 4000, 0, 0, 2, 0 }, false, false, true,  false, true,  false );
    
    // Tower                                                                                                                                                                                      undead, unliv,flying,ranged,dragon,att_all );
    const Creature Gremlin (           "Gremlin",           Faction::Tower,      1, false, 16, false,  3,  3,  0,  1,  2,   4,  4, Morale::Good, Luck::Neutral,   55,   44, {   30, 0, 0, 0, 0 }, false, false, false, false, false, false );
    const Creature Master_Gremlin (    "Master Gremlin",    Faction::Tower,      1, true,  16, false,  4,  4,  8,  1,  2,   4,  5, Morale::Good, Luck::Neutral,   55,   66, {   40, 0, 0, 0, 0 }, false, false, false, true,  false, false );
    const Creature Stone_Gargoyle (    "Stone Gargoyle",    Faction::Tower,      2, false,  9, false,  6,  6,  0,  2,  3,  16,  6, Morale::Good, Luck::Neutral,  150,  165, {  130, 0, 0, 0, 0 }, false, true,  true,  false, false, false );
    const Creature Obsidian_Gargoyle ( "Obsidian Gargoyle", Faction::Tower,      2, true,   9, false,  7,  7,  0,  2,  3,  16,  9, Morale::Good, Luck::Neutral,  155,  201, {  160, 0, 0, 0, 0 }, false, true,  true,  false, false, false );
    const Creature Stone_Golem (       "Stone Golem",       Faction::Tower,      3, false,  6, false,  7, 10,  0,  4,  5,  30,  3, Morale::Good, Luck::Neutral,  339,  250, {  150, 0, 0, 0, 0 }, false, true,  false, false, false, false );
    const Creature Iron_Golem (        "Iron Golem",        Faction::Tower,      3, true,   6, false,  9, 10,  0,  4,  5,  35,  5, Morale::Good, Luck::Neutral,  412,  412, {  200, 0, 0, 0, 0 }, false, true,  false, false, false, false );
    const Creature Mage (              "Mage",              Faction::Tower,      4, false,  4, false, 11,  8, 24,  7,  5,  25,  5, Morale::Good, Luck::Neutral,  418,  570, {  350, 0, 0, 0, 0 }, false, false, false, true,  false, false );
    const Creature Arch_Mage (         "Arch Mage",         Faction::Tower,      4, true,   4, false, 12,  9, 24,  7,  9,  30,  7, Morale::Good, Luck::Neutral,  467,  680, {  450, 0, 0, 0, 0 }, false, false, false, true,  false, false );
    const Creature Genie (             "Genie",             Faction::Tower,      5, false,  3, false, 12, 12,  0, 13, 16,  40,  7, Morale::Good, Luck::Neutral,  680,  884, {  550, 0, 0, 0, 0 }, false, false, true,  false, false, false );
    const Creature Master_Genie (      "Master Genie",      Faction::Tower,      5, true,   3, false, 12, 12,  0, 13, 16,  40, 11, Morale::Good, Luck::Neutral,  748,  942, {  600, 0, 0, 0, 0 }, false, false, true,  false, false, false );
    const Creature Naga (              "Naga",              Faction::Tower,      6, false,  2, true,  16, 13,  0, 20, 20, 110,  5, Morale::Good, Luck::Neutral, 2016, 2016, { 1100, 0, 0, 0, 0 }, false, false, false, false, false, false );
    const Creature Naga_Queen (        "Naga Queen",        Faction::Tower,      6, true,   2, true,  16, 13,  0, 30, 30, 110,  7, Morale::Good, Luck::Neutral, 2840, 2840, { 1600, 0, 0, 0, 0 }, false, false, false, false, false, false );
    const Creature Giant (             "Giant",             Faction::Tower,      7, false,  1, true,  19, 16,  0, 40, 60, 150,  7, Morale::Good, Luck::Neutral, 3146, 3718, { 2000, 0, 0, 0, 1 }, false, false, false, false, false, false );
    const Creature Titan (             "Titan",             Faction::Tower,      7, true,   1, true,  24, 24, 24, 40, 60, 300, 11, Morale::Good, Luck::Neutral, 5000, 7500, { 5000, 0, 0, 0, 2 }, false, false, false, true,  false, false );
    
    // Inferno

    // Necropolis
    const Creature Skeleton (         "Skeleton",           Faction::Necropolis, 1, false, 12, false,  5,  4,  0,  1,  3,   6,  4, Morale::Neutral, Luck::Neutral,   75,   60, {   60, 0, 0, 0, 0 }, true, false, false, false, false, false );
    const Creature Skeleton_Warrior ( "Skeleton Warrior",   Faction::Necropolis, 1, true,  12, false,  6,  6,  0,  1,  3,   6,  5, Morale::Neutral, Luck::Neutral,   85,   85, {   70, 0, 0, 0, 0 }, true, false, false, false, false, false );
    const Creature Walking_Dead (     "Walking Dead",       Faction::Necropolis, 2, false,  8, false,  5,  5,  0,  2,  3,  15,  3, Morale::Neutral, Luck::Neutral,  140,   98, {  100, 0, 0, 0, 0 }, true, false, false, false, false, false );
    const Creature Zombie (           "Zombie",             Faction::Necropolis, 2, true,   8, false,  5,  5,  0,  2,  3,  20,  4, Morale::Neutral, Luck::Neutral,  160,  128, {  125, 0, 0, 0, 0 }, true, false, false, false, false, false );
    const Creature Wight (            "Wight",              Faction::Necropolis, 3, false,  7, false,  7,  7,  0,  3,  5,  18,  5, Morale::Neutral, Luck::Neutral,  231,  252, {  200, 0, 0, 0, 0 }, true, false, true,  false, false, false );
    const Creature Wraith (           "Wraith",             Faction::Necropolis, 3, true,   7, false,  7,  7,  0,  3,  5,  18,  7, Morale::Neutral, Luck::Neutral,  252,  315, {  230, 0, 0, 0, 0 }, true, false, true,  false, false, false );
    const Creature Vampire (          "Vampire",            Faction::Necropolis, 4, false,  4, false, 10,  9,  0,  5,  8,  30,  6, Morale::Neutral, Luck::Neutral,  518,  555, {  360, 0, 0, 0, 0 }, true, false, true,  false, false, false );
    const Creature Vampire_Lord (     "Vampire Lord",       Faction::Necropolis, 4, true,   4, false, 10, 10,  0,  5,  8,  40,  9, Morale::Neutral, Luck::Neutral,  652,  783, {  500, 0, 0, 0, 0 }, true, false, true,  false, false, false );
    const Creature Lich (             "Lich",               Faction::Necropolis, 5, false,  3, false, 13, 10, 12, 11, 13,  30,  6, Morale::Neutral, Luck::Neutral,  742,  848, {  550, 0, 0, 0, 0 }, true, false, false, true,  false, false );
    const Creature Power_Lich (       "Power Lich",         Faction::Necropolis, 5, true,   3, false, 13, 10, 24, 11, 15,  40,  7, Morale::Neutral, Luck::Neutral,  889, 1079, {  600, 0, 0, 0, 0 }, true, false, false, true,  false, false );
    const Creature Black_Knight (     "Black Knight",       Faction::Necropolis, 6, false,  2, true,  16, 16,  0, 15, 30, 120,  7, Morale::Neutral, Luck::Neutral, 1753, 2087, { 1200, 0, 0, 0, 0 }, true, false, false, false, false, false );
    const Creature Dread_Knight (     "Dread Knight",       Faction::Necropolis, 6, true,   2, true,  18, 18,  0, 15, 30, 120,  9, Morale::Neutral, Luck::Neutral, 2029, 2382, { 1500, 0, 0, 0, 0 }, true, false, false, false, false, false );
    const Creature Bone_Dragon (      "Bone Dragon",        Faction::Necropolis, 7, false,  1, true,  17, 15,  0, 25, 50, 150,  9, Morale::Neutral, Luck::Neutral, 2420, 3388, { 1800, 0, 0, 0, 0 }, true, false, true,  false, true,  false );
    const Creature Ghost_Dragon (     "Ghost Dragon",       Faction::Necropolis, 7, true,   1, true,  19, 17,  0, 25, 50, 200, 14, Morale::Neutral, Luck::Neutral, 3228, 4696, { 3000, 1, 0, 0, 0 }, true, false, true,  false, true,  false );
    
    // Dungeon

    // Fortress

    // Stronghold

    // Conflux

    // Cove

    // Neutral

    //Necropolis
    
}

#endif