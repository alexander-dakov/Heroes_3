#ifndef SKILLS_PROBABILITY_H
#define SKILLS_PROBABILITY_H

#include <iostream>
#include "../utilities/types.h"

// whenever hero levels up he/she gains a primary skill bonus depending on the class
// primary skills for each class ordered in 2 groups - before and after hero reaches level 10
// primary skills ordered            = { {  a,  d,  p,  k,}, {a10,d10,p10,k10 } }
const uint8_t p_s_knight[2][4]       = { { 35, 45, 10, 10 }, { 30, 30, 20, 20 } };
const uint8_t p_s_cleric[2][4]       = { { 20, 15, 30, 35 }, { 20, 20, 30, 30 } };
const uint8_t p_s_ranger[2][4]       = { { 35, 45, 10, 10 }, { 30, 30, 20, 20 } };
const uint8_t p_s_druid[2][4]        = { { 10, 20, 35, 35 }, { 20, 20, 30, 30 } };
const uint8_t p_s_alchemist[2][4]    = { { 30, 30, 20, 20 }, { 30, 30, 20, 20 } };
const uint8_t p_s_wizard[2][4]       = { { 10, 10, 40, 40 }, { 30, 20, 20, 30 } };
const uint8_t p_s_demoniac[2][4]     = { { 35, 35, 15, 15 }, { 30, 30, 20, 20 } };
const uint8_t p_s_heretic[2][4]      = { { 15, 15, 35, 35 }, { 20, 20, 30, 30 } };
const uint8_t p_s_death_knight[2][4] = { { 30, 25, 20, 25 }, { 25, 25, 25, 25 } };
const uint8_t p_s_necromancer[2][4]  = { { 15, 15, 35, 35 }, { 25, 25, 25, 25 } };
const uint8_t p_s_overlord[2][4]     = { { 35, 35, 15, 15 }, { 30, 30, 20, 20 } };
const uint8_t p_s_warlock[2][4]      = { { 10, 10, 50, 30 }, { 20, 20, 30, 30 } };
const uint8_t p_s_barbarian[2][4]    = { { 55, 35,  5,  5 }, { 30, 30, 20, 20 } };
const uint8_t p_s_battle_mage[2][4]  = { { 30, 20, 25, 25 }, { 25, 25, 25, 25 } };
const uint8_t p_s_beastmaster[2][4]  = { { 30, 50, 10, 10 }, { 30, 30, 20, 20 } };
const uint8_t p_s_witch[2][4]        = { {  5, 15, 40, 40 }, { 20, 20, 30, 30 } };
const uint8_t p_s_planeswalker[2][4] = { { 45, 25, 15, 15 }, { 30, 30, 20, 20 } };
const uint8_t p_s_elementalist[2][4] = { { 15, 15, 35, 35 }, { 25, 25, 25, 25 } };
const uint8_t p_s_captain[2][4]      = { { 45, 25, 20, 10 }, { 30, 30, 20, 20 } };
const uint8_t p_s_navigator[2][4]    = { { 15, 10, 40, 35 }, { 30, 20, 20, 30 } };

#endif