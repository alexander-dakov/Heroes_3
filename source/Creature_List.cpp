#ifndef CREATURE_LIST_CPP
#define CREATURE_LIST_CPP

#include "Creature.h"

namespace Creature_List
{
    // Important - only Necropolis has its special abilities somewhat right. All special abilities should be implemented and the list creatures - updated.
    
    //                                     name,                   faction,        lvl, upg, growth,2_hex, A,  D,  S, mD, MD, hp, speed,  morale,           luck,       fight, ai, { gold, m, s, c, g }, special abilities );
    // Castle
    const Creature Pikeman (             "Pikeman",             Faction::Castle,     1, false, 14, false,  4,  5,  0,  1,  3,  10,  4, Morale::Good,    Luck::Neutral,  100,   80, {   60, 0, 0, 0, 0 }, "Immune to jousting.");
    const Creature Halberdier (          "Halberdier",          Faction::Castle,     1, true,  14, false,  6,  5,  0,  2,  3,  10,  5, Morale::Good,    Luck::Neutral,  115,  115, {   75, 0, 0, 0, 0 }, "Immune to jousting.");
    const Creature Archer (              "Archer",              Faction::Castle,     2, false,  9, false,  6,  3, 12,  2,  3,  10,  4, Morale::Good,    Luck::Neutral,  115,  126, {  100, 0, 0, 0, 0 }, "Ranged attack.");
    const Creature Marksman (            "Marksman",            Faction::Castle,     2, true,   9, false,  6,  3, 24,  2,  3,  10,  6, Morale::Good,    Luck::Neutral,  115,  184, {  150, 0, 0, 0, 0 }, "Ranged attack. Double attack.");
    const Creature Griffin (             "Griffin",             Faction::Castle,     3, false,  7, true,   8,  8,  0,  3,  6,  25,  6, Morale::Good,    Luck::Neutral,  324,  351, {  200, 0, 0, 0, 0 }, "Flying. Two retaliations.");
    const Creature Royal_Griffin (       "Royal Griffin",       Faction::Castle,     3, true,   7, true,   9,  9,  0,  3,  6,  25,  9, Morale::Good,    Luck::Neutral,  364,  448, {  240, 0, 0, 0, 0 }, "Flying. Unlimited retaliations.");
    const Creature Swordsman (           "Swordsman",           Faction::Castle,     4, false,  4, false, 10, 12,  0,  6,  9,  35,  5, Morale::Good,    Luck::Neutral,  445,  445, {  300, 0, 0, 0, 0 }, "");
    const Creature Crusader (            "Crusader",            Faction::Castle,     4, true,   4, false, 12, 12,  0,  7, 10,  35,  6, Morale::Good,    Luck::Neutral,  588,  588, {  400, 0, 0, 0, 0 }, "Double attack.");
    const Creature Monk (                "Monk",                Faction::Castle,     5, false,  3, false, 12,  7, 12, 10, 12,  30,  5, Morale::Good,    Luck::Neutral,  582,  485, {  400, 0, 0, 0, 0 }, "Ranged attack.");
    const Creature Zealot (              "Zealot",              Faction::Castle,     5, true,   3, false, 12, 10, 24, 10, 12,  30,  7, Morale::Good,    Luck::Neutral,  500,  750, {  450, 0, 0, 0, 0 }, "Ranged attack. No melee penalty.");
    const Creature Cavalier (            "Cavalier",            Faction::Castle,     6, false,  2, true,  15, 15,  0, 15, 25, 100,  7, Morale::Good,    Luck::Neutral, 1668, 1946, { 1000, 0, 0, 0, 0 }, "Jousting bonus.");
    const Creature Champion (            "Champion",            Faction::Castle,     6, true,   2, true,  16, 16,  0, 20, 25, 100,  9, Morale::Good,    Luck::Neutral, 1800, 2100, { 1200, 0, 0, 0, 0 }, "Jousting bonus.");
    const Creature Angel (               "Angel",               Faction::Castle,     7, false,  1, true,  20, 20,  0, 50, 50, 200, 12, Morale::Good,    Luck::Neutral, 3585, 5019, { 3000, 0, 0, 0, 1 }, "Flying. Hates Devils and Arch Devils. +1 morale to alias troops.");
    const Creature Archangel (           "Archangel",           Faction::Castle,     7, true,   1, true,  30, 30,  0, 50, 50, 250, 18, Morale::Good,    Luck::Neutral, 6033, 8776, { 5000, 0, 0, 0, 3 }, "Flying. Hates Devils and Arch Devils. +1 morale to alias troops. Can cast Ressurection once per battle.");
    
    // Rampart
    const Creature Centaur (             "Centaur",             Faction::Rampart,    1, false, 14, true,   5,  3,  0,  2,  3,   8,  6, Morale::Good,    Luck::Neutral,  100,  100, {   70, 0, 0, 0, 0 }, "");
    const Creature Centaur_Captain (     "Centaur Captain",     Faction::Rampart,    1, true,  14, true,   6,  3,  0,  2,  3,  10,  8, Morale::Good,    Luck::Neutral,  138,  138, {   90, 0, 0, 0, 0 }, "");
    const Creature Dwarf (               "Dwarf",               Faction::Rampart,    2, false,  8, false,  6,  7,  0,  2,  4,  20,  3, Morale::Good,    Luck::Neutral,  138,  138, {  120, 0, 0, 0, 0 }, "Magic resistance 20%.");
    const Creature Battle_Dwarf (        "Battle Dwarf",        Faction::Rampart,    2, true,   8, false,  7,  7,  0,  2,  4,  20,  5, Morale::Good,    Luck::Neutral,  209,  209, {  150, 0, 0, 0, 0 }, "Magic resistance 40%.");
    const Creature Wood_Elf (            "Wood Elf",            Faction::Rampart,    3, false,  7, false,  9,  5, 12,  3,  5,  15,  6, Morale::Good,    Luck::Neutral,  234,  234, {  200, 0, 0, 0, 0 }, "Ranged attack.");
    const Creature Grand_Elf (           "Grand Elf",           Faction::Rampart,    3, true,   7, false,  9,  5, 24,  3,  5,  15,  7, Morale::Good,    Luck::Neutral,  331,  331, {  225, 0, 0, 0, 0 }, "Ranged attack. Double attack.");
    const Creature Pegasus (             "Pegasus",             Faction::Rampart,    4, false,  5, true,   9,  8,  0,  5,  9,  30,  8, Morale::Good,    Luck::Neutral,  518,  518, {  250, 0, 0, 0, 0 }, "Magic damper.");
    const Creature Silver_Pegasus (      "Silver Pegasus",      Faction::Rampart,    4, true,   5, true,   9, 10,  0,  5,  9,  30, 12, Morale::Good,    Luck::Neutral,  532,  532, {  275, 0, 0, 0, 0 }, "Magic damper.");
    const Creature Dendroid_Guard (      "Dendroid Guard",      Faction::Rampart,    5, false,  3, false,  9, 12,  0, 10, 14,  55,  3, Morale::Good,    Luck::Neutral,  517,  517, {  350, 0, 0, 0, 0 }, "Binding attack.");
    const Creature Dendroid_Soldier (    "Dendroid Soldier",    Faction::Rampart,    5, true,   3, false,  9, 12,  0, 10, 14,  65,  4, Morale::Good,    Luck::Neutral,  765,  803, {  425, 0, 0, 0, 0 }, "Binding attack.");
    const Creature Unicorn (             "Unicorn",             Faction::Rampart,    6, false,  2, true,  15, 14,  0, 18, 22,  90,  7, Morale::Good,    Luck::Neutral, 1548, 1806, {  850, 0, 0, 0, 0 }, "20% chance to cast Blind per attack. Aura of magic resistance 20%.");
    const Creature War_Unicorn (         "War Unicorn",         Faction::Rampart,    6, true,   2, true,  15, 14,  0, 18, 22, 110,  9, Morale::Good,    Luck::Neutral, 2030, 2030, {  950, 0, 0, 0, 0 }, "20% chance to cast Blind per attack. Aura of magic resistance 20%.");
    const Creature Green_Dragon (        "Green Dragon",        Faction::Rampart,    7, false,  1, true,  18, 18,  0, 40, 50, 180, 10, Morale::Good,    Luck::Neutral, 3654, 4872, { 2400, 0, 0, 1, 0 }, "Breath attack. Immune to spells level 1-3.");
    const Creature Gold_Dragon (         "Gold Dragon",         Faction::Rampart,    7, true,   1, true,  27, 27,  0, 40, 50, 250, 16, Morale::Good,    Luck::Neutral, 6220, 8613, { 4000, 0, 0, 2, 0 }, "Breath attack. Immune to spells level 1-4.");

    // Tower
    const Creature Gremlin (             "Gremlin",             Faction::Tower,      1, false, 16, false,  3,  3,  0,  1,  2,   4,  4, Morale::Good,    Luck::Neutral,   55,   44, {   30, 0, 0, 0, 0 }, "");
    const Creature Master_Gremlin (      "Master Gremlin",      Faction::Tower,      1, true,  16, false,  4,  4,  8,  1,  2,   4,  5, Morale::Good,    Luck::Neutral,   55,   66, {   40, 0, 0, 0, 0 }, "Ranged attack.");
    const Creature Stone_Gargoyle (      "Stone Gargoyle",      Faction::Tower,      2, false,  9, false,  6,  6,  0,  2,  3,  16,  6, Morale::Good,    Luck::Neutral,  150,  165, {  130, 0, 0, 0, 0 }, "Non-living.");
    const Creature Obsidian_Gargoyle (   "Obsidian Gargoyle",   Faction::Tower,      2, true,   9, false,  7,  7,  0,  2,  3,  16,  9, Morale::Good,    Luck::Neutral,  155,  201, {  160, 0, 0, 0, 0 }, "Non-living.");
    const Creature Stone_Golem (         "Stone Golem",         Faction::Tower,      3, false,  6, false,  7, 10,  0,  4,  5,  30,  3, Morale::Good,    Luck::Neutral,  339,  250, {  150, 0, 0, 0, 0 }, "Non-living. Spell damage reduction 50%.");
    const Creature Iron_Golem (          "Iron Golem",          Faction::Tower,      3, true,   6, false,  9, 10,  0,  4,  5,  35,  5, Morale::Good,    Luck::Neutral,  412,  412, {  200, 0, 0, 0, 0 }, "Non-living. Spell damage reduction 75%.");
    const Creature Mage (                "Mage",                Faction::Tower,      4, false,  4, false, 11,  8, 24,  7,  5,  25,  5, Morale::Good,    Luck::Neutral,  418,  570, {  350, 0, 0, 0, 0 }, "Ranged attack. No melee penalty. No obstacle penalty. Hero's combat spells cost 2 less mana.");
    const Creature Arch_Mage (           "Arch Mage",           Faction::Tower,      4, true,   4, false, 12,  9, 24,  7,  9,  30,  7, Morale::Good,    Luck::Neutral,  467,  680, {  450, 0, 0, 0, 0 }, "Ranged attack. No melee penalty. No obstacle penalty. Hero's combat spells cost 2 less mana.");
    const Creature Genie (               "Genie",               Faction::Tower,      5, false,  3, false, 12, 12,  0, 13, 16,  40,  7, Morale::Good,    Luck::Neutral,  680,  884, {  550, 0, 0, 0, 0 }, "Hates Efreeti and Efreet Sultans.");
    const Creature Master_Genie (        "Master Genie",        Faction::Tower,      5, true,   3, false, 12, 12,  0, 13, 16,  40, 11, Morale::Good,    Luck::Neutral,  748,  942, {  600, 0, 0, 0, 0 }, "Hates Efreeti and Efreet Sultans. Spellcaster.");
    const Creature Naga (                "Naga",                Faction::Tower,      6, false,  2, true,  16, 13,  0, 20, 20, 110,  5, Morale::Good,    Luck::Neutral, 2016, 2016, { 1100, 0, 0, 0, 0 }, "No enemy retaliation.");
    const Creature Naga_Queen (          "Naga Queen",          Faction::Tower,      6, true,   2, true,  16, 13,  0, 30, 30, 110,  7, Morale::Good,    Luck::Neutral, 2840, 2840, { 1600, 0, 0, 0, 0 }, "No enemy retaliation.");
    const Creature Giant (               "Giant",               Faction::Tower,      7, false,  1, false, 19, 16,  0, 40, 60, 150,  7, Morale::Good,    Luck::Neutral, 3146, 3718, { 2000, 0, 0, 0, 1 }, "Immune to mind spells.");
    const Creature Titan (               "Titan",               Faction::Tower,      7, true,   1, false, 24, 24, 24, 40, 60, 300, 11, Morale::Good,    Luck::Neutral, 5000, 7500, { 5000, 0, 0, 0, 2 }, "Ranged attack. No melee penalty. Immune to mind spells. Hates Black Dragons.");

    // Inferno
    const Creature Imp (                 "Imp",                 Faction::Inferno,    1, false, 15, false,  2,  3,  0,  1,  2,   4,  5, Morale::Good,    Luck::Neutral,   50,   50, {   50, 0, 0, 0, 0 }, "");
    const Creature Familiar (            "Familiar",            Faction::Inferno,    1, true,  15, false,  4,  4,  0,  1,  2,   4,  7, Morale::Good,    Luck::Neutral,   60,   60, {   60, 0, 0, 0, 0 }, "Magic channel.");
    const Creature Gog (                 "Gog",                 Faction::Inferno,    2, false,  8, false,  6,  4, 12,  2,  4,  13,  4, Morale::Good,    Luck::Neutral,  145,  159, {  125, 0, 0, 0, 0 }, "Ranged attack.");
    const Creature Magog (               "Magog",               Faction::Inferno,    2, true,   8, false,  7,  4, 24,  2,  4,  13,  6, Morale::Good,    Luck::Neutral,  210,  240, {  175, 0, 0, 0, 0 }, "Ranged attack. Fireball attack.");
    const Creature Hell_Hound (          "Hell Hound",          Faction::Inferno,    3, false,  5, true,  10,  6,  0,  2,  7,  25,  7, Morale::Good,    Luck::Neutral,  275,  357, {  200, 0, 0, 0, 0 }, "");
    const Creature Cerberus (            "Cerberus",            Faction::Inferno,    3, true,   5, true,  10,  8,  0,  2,  7,  25,  8, Morale::Good,    Luck::Neutral,  308,  392, {  250, 0, 0, 0, 0 }, "3-headed attack. No enemy retaliation.");
    const Creature Demon (               "Demon",               Faction::Inferno,    4, false,  4, false, 10, 10,  0,  7,  9,  35,  5, Morale::Good,    Luck::Neutral,  445,  445, {  250, 0, 0, 0, 0 }, "");
    const Creature Horned_Demon (        "Horned Demon",        Faction::Inferno,    4, true,   4, false, 10, 10,  0,  7,  9,  40,  6, Morale::Good,    Luck::Neutral,  480,  480, {  270, 0, 0, 0, 0 }, "");
    const Creature Pit_Fiend (           "Pit Fiend",           Faction::Inferno,    5, false,  3, false, 13, 13,  0, 13, 17,  45,  6, Morale::Good,    Luck::Neutral,  765,  765, {  500, 0, 0, 0, 0 }, "");
    const Creature Pit_Lord (            "Pit Lord",            Faction::Inferno,    5, true,   3, false, 13, 13,  0, 13, 17,  45,  7, Morale::Good,    Luck::Neutral, 1071, 1224, {  700, 0, 0, 0, 0 }, "Summon Demons.");
    const Creature Efreet (              "Efreet",              Faction::Inferno,    6, false,  2, false, 16, 12,  0, 16, 24,  90,  9, Morale::Good,    Luck::Neutral, 1413, 1670, {  900, 0, 0, 0, 0 }, "Immune to fire (Magic Arrow included). Hates Genies and Master Genies.");
    const Creature Efreet_Sultan (       "Efreet Sultan",       Faction::Inferno,    6, true,   2, false, 16, 14,  0, 16, 24,  90, 13, Morale::Good,    Luck::Neutral, 1802, 2343, { 1100, 0, 0, 0, 0 }, "Immune to fire (Magic Arrow included). Hates Genies and Master Genies. Fire Shield.");
    const Creature Devil (               "Devil",               Faction::Inferno,    7, false,  1, false, 19, 21,  0, 30, 40, 160, 11, Morale::Good,    Luck::Neutral, 3759, 5101, { 2700, 1, 0, 0, 0 }, "-1 luck to enemy troops. No enemy retaliation. Hates Angels and Arch Angels.");
    const Creature Arch_Devil (          "Arch Devil",          Faction::Inferno,    7, true,   1, false, 26, 28,  0, 30, 40, 200, 17, Morale::Good,    Luck::Neutral, 5243, 7115, { 4500, 2, 0, 0, 0 }, "-2 luck to enemy troops. No enemy retaliation. Hates Angels and Arch Angels.");

    // Necropolis
    const Creature Skeleton (            "Skeleton",            Faction::Necropolis, 1, false, 12, false,  5,  4,  0,  1,  3,   6,  4, Morale::Neutral, Luck::Neutral,   75,   60, {   60, 0, 0, 0, 0 }, "Undead.");
    const Creature Skeleton_Warrior (    "Skeleton Warrior",    Faction::Necropolis, 1, true,  12, false,  6,  6,  0,  1,  3,   6,  5, Morale::Neutral, Luck::Neutral,   85,   85, {   70, 0, 0, 0, 0 }, "Undead.");
    const Creature Walking_Dead (        "Walking Dead",        Faction::Necropolis, 2, false,  8, false,  5,  5,  0,  2,  3,  15,  3, Morale::Neutral, Luck::Neutral,  140,   98, {  100, 0, 0, 0, 0 }, "Undead.");
    const Creature Zombie (              "Zombie",              Faction::Necropolis, 2, true,   8, false,  5,  5,  0,  2,  3,  20,  4, Morale::Neutral, Luck::Neutral,  160,  128, {  125, 0, 0, 0, 0 }, "Undead. 20% chance to cast Disease per attack.");
    const Creature Wight (               "Wight",               Faction::Necropolis, 3, false,  7, false,  7,  7,  0,  3,  5,  18,  5, Morale::Neutral, Luck::Neutral,  231,  252, {  200, 0, 0, 0, 0 }, "Undead. Regeneration.");
    const Creature Wraith (              "Wraith",              Faction::Necropolis, 3, true,   7, false,  7,  7,  0,  3,  5,  18,  7, Morale::Neutral, Luck::Neutral,  252,  315, {  230, 0, 0, 0, 0 }, "Undead. Regeneration. Mana drain.");
    const Creature Vampire (             "Vampire",             Faction::Necropolis, 4, false,  4, false, 10,  9,  0,  5,  8,  30,  6, Morale::Neutral, Luck::Neutral,  518,  555, {  360, 0, 0, 0, 0 }, "Undead. No enemy retaliation.");
    const Creature Vampire_Lord (        "Vampire Lord",        Faction::Necropolis, 4, true,   4, false, 10, 10,  0,  5,  8,  40,  9, Morale::Neutral, Luck::Neutral,  652,  783, {  500, 0, 0, 0, 0 }, "Undead. No enemy retaliation. Life drain.");
    const Creature Lich (                "Lich",                Faction::Necropolis, 5, false,  3, false, 13, 10, 12, 11, 13,  30,  6, Morale::Neutral, Luck::Neutral,  742,  848, {  550, 0, 0, 0, 0 }, "Undead. Ranged attack. Death cloud.");
    const Creature Power_Lich (          "Power Lich",          Faction::Necropolis, 5, true,   3, false, 13, 10, 24, 11, 15,  40,  7, Morale::Neutral, Luck::Neutral,  889, 1079, {  600, 0, 0, 0, 0 }, "Undead. Ranged attack. Death cloud.");
    const Creature Black_Knight (        "Black Knight",        Faction::Necropolis, 6, false,  2, true,  16, 16,  0, 15, 30, 120,  7, Morale::Neutral, Luck::Neutral, 1753, 2087, { 1200, 0, 0, 0, 0 }, "Undead. 25% chance to cast Curse per attack.");
    const Creature Dread_Knight (        "Dread Knight",        Faction::Necropolis, 6, true,   2, true,  18, 18,  0, 15, 30, 120,  9, Morale::Neutral, Luck::Neutral, 2029, 2382, { 1500, 0, 0, 0, 0 }, "Undead. 25% chance to cast Curse per attack. 20% chance to cast Death Blow per attack.");
    const Creature Bone_Dragon (         "Bone Dragon",         Faction::Necropolis, 7, false,  1, true,  17, 15,  0, 25, 50, 150,  9, Morale::Neutral, Luck::Neutral, 2420, 3388, { 1800, 0, 0, 0, 0 }, "Undead. -1 morale to enemy troops.");
    const Creature Ghost_Dragon (        "Ghost Dragon",        Faction::Necropolis, 7, true,   1, true,  19, 17,  0, 25, 50, 200, 14, Morale::Neutral, Luck::Neutral, 3228, 4696, { 3000, 1, 0, 0, 0 }, "Undead. -1 morale to enemy troops. 20% chance to cast Aging per attack.");
    
    // Dungeon
    const Creature Troglodyte (          "Troglodyte",          Faction::Dungeon,    1, false, 14, false,  4,  3,  0,  1,  3,   5,  4, Morale::Good,    Luck::Neutral,   73,   59, {   50, 0, 0, 0, 0 }, "Immune to Blind. Immune to Petrify.");
    const Creature Infernal_Troglodyte ( "Infernal Troglodyte", Faction::Dungeon,    1, true,  14, false,  5,  4,  0,  1,  3,   6,  5, Morale::Good,    Luck::Neutral,   84,   84, {   65, 0, 0, 0, 0 }, "Immune to Blind. Immune to Petrify.");
    const Creature Harpy (               "Harpy",               Faction::Dungeon,    2, false,  8, false,  6,  5,  0,  1,  4,  14,  6, Morale::Good,    Luck::Neutral,  140,  154, {  130, 0, 0, 0, 0 }, "Strike and return.");
    const Creature Harpy_Hag (           "Harpy Hag",           Faction::Dungeon,    2, true,   8, false,  6,  6,  0,  1,  4,  14,  9, Morale::Good,    Luck::Neutral,  196,  238, {  170, 0, 0, 0, 0 }, "Strike and return. No enemy retaliation.");
    const Creature Beholder (            "Beholder",            Faction::Dungeon,    3, false,  7, false,  9,  7, 12,  3,  5,  22,  5, Morale::Good,    Luck::Neutral,  240,  336, {  250, 0, 0, 0, 0 }, "Ranged attack. No melee penalty.");
    const Creature Evil_Eye (            "Evil Eye",            Faction::Dungeon,    3, true,   7, false, 10,  8, 24,  3,  5,  22,  7, Morale::Good,    Luck::Neutral,  245,  367, {  280, 0, 0, 0, 0 }, "Ranged attack. No melee penalty.");
    const Creature Medusa (              "Medusa",              Faction::Dungeon,    4, false,  4, true,   9,  9,  4,  6,  8,  25,  5, Morale::Good,    Luck::Neutral,  379,  517, {  300, 0, 0, 0, 0 }, "Ranged attack. No melee penalty. 20% chance to cast Petrify per melee attack.");
    const Creature Medusa_Queen (        "Medusa Queen",        Faction::Dungeon,    4, true,   4, true,  10, 10,  8,  6,  8,  30,  6, Morale::Good,    Luck::Neutral,  423,  577, {  330, 0, 0, 0, 0 }, "Ranged attack. No melee penalty. 20% chance to cast Petrify per melee attack.");
    const Creature Minotaur (            "Minotaur",            Faction::Dungeon,    5, false,  3, false, 14, 12,  0, 12, 20,  50,  6, Morale::Good,    Luck::Neutral,  835,  835, {  500, 0, 0, 0, 0 }, "Minimum morale is +1.");
    const Creature Minotaur_King (       "Minotaur King",       Faction::Dungeon,    5, true,   3, false, 15, 15,  0, 12, 20,  50,  8, Morale::Good,    Luck::Neutral,  890, 1068, {  575, 0, 0, 0, 0 }, "Minimum morale is +1.");
    const Creature Manticore (           "Manticore",           Faction::Dungeon,    6, false,  2, true,  15, 13,  0, 14, 20,  80,  7, Morale::Good,    Luck::Neutral, 1215, 1547, {  850, 0, 0, 0, 0 }, "");
    const Creature Scorpicore (          "Scorpicore",          Faction::Dungeon,    6, true,   2, true,  16, 14,  0, 14, 20,  80, 11, Morale::Good,    Luck::Neutral, 1248, 1589, { 1050, 0, 0, 0, 0 }, "20% chance to cast Paralyzing Venom per attack.");
    const Creature Red_Dragon (          "Red Dragon",          Faction::Dungeon,    7, false,  1, true,  19, 19,  0, 40, 50, 180, 11, Morale::Good,    Luck::Neutral, 3762, 4702, { 2500, 0, 1, 0, 0 }, "Breath attack. Immune to spells level 1-3.");
    const Creature Black_Dragon (        "Black Dragon",        Faction::Dungeon,    7, true,   1, true,  25, 25,  0, 40, 50, 300, 15, Morale::Good,    Luck::Neutral, 6783, 8721, { 4000, 0, 2, 0, 0 }, "Breath attack. Immune to all spells. Hates Titans.");
  
    // Fortress

    // Stronghold

    // Conflux
    const Creature Pixie (               "Pixie",               Faction::Conflux,    1, false, 20, false,  2,  2,  0,  1,  2,   3,  7, Morale::Good,    Luck::Neutral,   40,   55, {   25, 0, 0, 0, 0 }, "");
    const Creature Sprite (              "Sprite",              Faction::Conflux,    1, true,  20, false,  2,  2,  0,  1,  3,   3,  9, Morale::Good,    Luck::Neutral,   70,   95, {   30, 0, 0, 0, 0 }, "No enemy retaliation.");
    const Creature Air_Elemental (       "Air Elemental",       Faction::Conflux,    2, false,  6, false,  9,  9,  0,  2,  8,  25,  7, Morale::Good,    Luck::Neutral,  324,  356, {  250, 0, 0, 0, 0 }, "Non-living. Immune to Meteor Shower. Vulnerable to Lightning Bolt, Chain Lightning and Armageddon.");
    const Creature Storm_Elemental (     "Storm Elemental",     Faction::Conflux,    2, true,   6, false,  9,  9, 24,  2,  8,  25,  8, Morale::Good,    Luck::Neutral,  324,  486, {  275, 0, 0, 0, 0 }, "Ranged attack. Non-living. Immune to Meteor Shower. Vulnerable to Lightning Bolt, Chain Lightning and Armageddon. Spellcaster (Protection from Air).");
    const Creature Water_Elemental (     "Water Elemental",     Faction::Conflux,    3, false,  6, true,   8, 10,  0,  3,  7,  30,  5, Morale::Good,    Luck::Neutral,  315,  315, {  300, 0, 0, 0, 0 }, "Non-living. Immune to Ice Bolt and Frost Ring. Vulnerable to Armageddon, Fireball, Inferno.");
    const Creature Ice_Elemental (       "Ice Elemental",       Faction::Conflux,    3, true,   6, true,   8, 10, 24,  3,  7,  30,  6, Morale::Good,    Luck::Neutral,  315,  380, {  375, 0, 0, 0, 0 }, "Ranged attack. Non-living. Immune to Ice Bolt and Frost Ring. Vulnerable to Armageddon, Fireball, Inferno. Spellcaster (Protection from Water).");
    const Creature Fire_Elemental (      "Fire Elemental",      Faction::Conflux,    4, false,  5, false, 10,  8,  0,  4,  6,  35,  6, Morale::Good,    Luck::Neutral,  345,  345, {  350, 0, 0, 0, 0 }, "Non-living. Immune to fire (Magic Arrow included). Vulnerable to Ice Bolt and Frost Ring.");
    const Creature Energy_Elemental (    "Energy Elemental",    Faction::Conflux,    4, true,   5, false, 12,  8,  0,  4,  6,  35,  8, Morale::Good,    Luck::Neutral,  360,  470, {  400, 0, 0, 0, 0 }, "Non-living. Immune to fire (Magic Arrow included). Vulnerable to Ice Bolt and Frost Ring. Spellcaster (Protection from Fire).");
    const Creature Earth_Elemental (     "Earth Elemental",     Faction::Conflux,    5, false,  4, false, 10, 10,  0,  4,  8,  40,  4, Morale::Good,    Luck::Neutral,  415,  330, {  400, 0, 0, 0, 0 }, "Non-living. Immune to Lightning Bolt, Chain Lightning and Armageddon. Vulnerable to Meteor Shower.");
    const Creature Magma_Elemental (     "Magma Elemental",     Faction::Conflux,    5, true,   4, false, 11, 11,  0,  6, 10,  40,  6, Morale::Good,    Luck::Neutral,  490,  490, {  500, 0, 0, 0, 0 }, "Non-living. Immune to Lightning Bolt, Chain Lightning and Armageddon. Vulnerable to Meteor Shower. Spellcaster (Protection from Earth).");
    const Creature Psychic_Elemental (   "Psychic Elemental",   Faction::Conflux,    6, false,  2, false, 15, 13,  0, 10, 20,  75,  7, Morale::Good,    Luck::Neutral, 1431, 1669, {  750, 0, 0, 0, 0 }, "Non-living. No enemy retaliation. Attack all adjacent hexes. Immune to mind spells.");
    const Creature Magic_Elemental (     "Magic Elemental",     Faction::Conflux,    6, true,   2, false, 15, 13,  0, 15, 25,  80,  9, Morale::Good,    Luck::Neutral, 1724, 2012, {  800, 0, 0, 0, 0 }, "Non-living. No enemy retaliation. Attack all adjacent hexes. Immune to all spells.");
    const Creature Firebird (            "Firebird",            Faction::Conflux,    7, false,  2, true,  18, 18,  0, 30, 40, 150, 15, Morale::Good,    Luck::Neutral, 3248, 4547, { 1500, 0, 0, 0, 0 }, "Breath attack. Immune to fire (Magic Arrow included).");
    const Creature Phoenix (             "Phoenix",             Faction::Conflux,    7, true,   2, true,  21, 18,  0, 30, 40, 200, 21, Morale::Good,    Luck::Neutral, 4929, 6721, { 2000, 1, 0, 0, 0 }, "Breath attack. Rebirth. Immune to fire (Magic Arrow included).");
  
    // Cove

    // Neutral
    
}

#endif