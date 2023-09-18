#include <iostream>
#include "../utilities/types.h"
#include "Creature_Stack.cpp"
#include "Creature_List.cpp"
#include "Hero_List.cpp"

#include "../tests/tests.cpp"


/* Thought processes that influence the development :

0. Code testing :
1) All tests should be a call to a certain function reproducing the example. Those tests are held in a different file - tests.cpp, so the result could be shown whenever needed.
2) New tests will be added with ease and kept for future references.

1. Creatures :
1) Since creatures in the game a influenced by the hero leading them (if they have one) they get to be treated as structures of data (no setters, only getters),
that are constructed thanks to Creature.h.
2) A library of all in-game creatures, with their basic stats, is kept in a namespace called Creature_List (created in Creature_List.cpp)
3) Creature stacks are the interactable objects forming the armies, used in battles, which COPY an instance of a creature from Creature_List. It should not be a reference or a pointer
as the object will suffer changes and there may be many instances of the same creature on the battle field.
4) Those stacks should have constructors for both hero-lead and non-hero-lead armies. When there is no hero - the basic stats of the creatures will be used in battle.
When there is a hero - the stack of creatures should get bonuses from the hero's primary and secondary skills.
5) On the battle field, each stack has its own turn which may be skipped (if perished / lacks morale / under a certain spell). A flag should be used to help with the problem.
6) A team flag should also be used in order to ban friendly fire, unless the spell 'Berserk' is casted.
7) When a stack attacks another stack/stacks it should be able to : reach it and attack it / target it and shoot it.

2. Heroes :
1) Heroes should be interactable objects that hold and army of up to 8 creature stacks.
2) A library of all in-game heroes, with in-game up-to-date stats, is kept in a namespace called Hero_List (created in Hero_List.cpp). Since a hero could exist only once 
in a game, they will be directly referenced for each player.
3) Special abilities, secondary skills, items and war machines should aslo be treated as structs of data. All of them should have their own namespace of instances, which will
be referenced by a hero.


TO DO:
 1) Test a creature vs creature battle
 2) Test a hero vs creature battle (no spells)
 3) Test a hero vs hero battle (no spells)
 4) Fix the implementation of secondary skills and test it in battle
 5) Fix the implementation of war machines and test it in battle
 6) Fix the implementation of items and test it in battle
 7) Fix the implementation of specialties and test it in battle
 8) Fix the implementation of spells and spellbook and test it in battle
 9) Implement the battle event with all of its quirks (actions = wait/attack/defend/retreat, terrain, map) and test it
10) Implement adventure map object
11) Implement map
12) Implement towns and castle walls during seige
13) Implement players
14) Implement time - days, weeks, months
15) Implement hero rotation in town taverns and "week of ..."
16) Implement a winning condition for the map

*/

int main()
{
    test_create_creature_stack();
    
    system("pause");
    return 0;
}
