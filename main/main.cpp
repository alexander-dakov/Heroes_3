#include <iostream>
#include "../utilities/types.h"

#define SHOW_DEBUG_INFO (1) // show(1) or hide(0) debug messages

#define TESTS (1) // include(1) or exclude(0) tests library
#if TESTS == 1
    #include "../tests/tests.cpp"
#endif


/* Thought processes that influence the development :

0. Code testing :
    1) All tests are written in functions in file tests.cpp. That way the result could be shown whenever needed.
    2) New tests are added with ease and kept for future references.

1. Creatures :
    1) Creatures in the game are influenced by the hero leading them, if they have one. Thus they get to be treated as structures of data without setters, but with getters.
    Methods are written in Creature.h.
    2) A library of all in-game creatures, with their basic stats, is kept in a namespace called Creature_List, written in Creature_List.cpp. Creatures' special abilities are 
    derived from the string in the end of the constructor.
    3) One creature can have 2 upgrades. Some modes add second upgrade to other units as well. Thus the upgrade level for all creatures is set to hold 3 options - None, First, Second.
    4) Creature stacks are the interactable objects forming the armies, used in battles, which COPY an instance of a creature from Creature_List. It should not be a reference or 
    a pointer as the object will suffer changes and there may be many instances of the same creature in the game.

2. Creature stacks :
    1) Stacks are basically a group of creatures placed in one slot in armies and on battle field. They can hold up to 3 spell effects (buffs and debuffs) at the same time. 
    If the stack is not part of a hero's army - the basic stats of the creatures will be used in battle.
    If the stack is part of a hero's army - the stack of creatures should get bonuses from the hero's primary and secondary skills, morale and luck, specialty and items.
    2) On the battle field, each stack has its own turn which may be skipped (if perished / lacks morale / under a certain spell). A flag should be used to help with the problem.
    3) A team flag should also be used in order to ban friendly fire, unless the spell 'Berserk' is casted.
    4) When a stack attacks another stack it should be able to : reach it and attack it / target it and shoot it.

3. Heroes :
    1) Heroes should be interactable objects that hold an army of up to 7 creature stacks.
    2) A library of all in-game heroes, with in-game up-to-date stats, is kept in a namespace called Hero_List (created in Hero_List.cpp). Since a hero could exist only once 
    in a game, they will be directly referenced for each player.
    3) Special abilities, secondary skills, items and war machines should aslo be treated as structs of data. All of them should have their own namespace of instances, which will
    be referenced by a hero.
    4) Hero should have a map for item slots and flags that get turn automatically when equipping/unequipping an item.

4. Hero specialties :


5. Hero secondary skills :


6. War machines :
    1) Those are :
    - First Aid Tent - regenerates some hp of a stack in the beggining of the battle round.
    - Ammo Cart - gives ranged units unlimited ammo, while the cart is not destroyed.
    - Ballista / Cannon - shoots at an enemy stack in the beggining of the battle round.
    - Catapult - used only during sieges, it damages the enemy's fortress bringing down its walls and shooting towers. It can be destroyed in battle. Every gets one automatically.
    2) They resemble creatures as they : have battle stats, can take damage, have spell immunities, cannot move or retaliate. Their aim/target could be altered by the hero if 
    her posseses certain secondary abilities.
    3) They are found in War_Machines_List.cpp

7. Items :
    1) Items are non-changeable structures of data. They are found in Items_List.cpp
    2) One item can be found multiple times in a game.
    3) Heroes hold a pointer to an item and if it is placed outside the treasure chest, the hero gets the bonus.


TO DO:
- When you try to add a stack into an army/slot, if there is already such creature - add the new stack to the existing one.
- Test a hero vs hero battle (no spells)
- Test a hero vs hero battle (with spells)
- Fix the implementation of secondary skills and test it in battle
- Fix the implementation of war machines and test it in battle
- Fix the implementation of items and test it in battle
- Fix the implementation of specialties and test it in battle
- Fix the implementation of spells and spellbook and test it in battle
- Implement the battle event with all of its quirks (actions = wait/attack/defend/retreat, terrain, map) and test it
- Implement adventure map object
- Implement map
- Implement towns and castle walls during seige
- Implement players
- Implement time - days, weeks, months
- Implement hero rotation in town taverns and "week of ..."
- Implement a winning condition for the map

*/

int main()
{
    // test_create_creature();
    // test_create_creature_stack();
    // test_creature_stack_vs_creature_stack();
    // test_create_item();
    // test_create_hero();
    // test_hero_item_bonuses();
    // test_army_hero_bonuses();
    // test_hero_vs_creature_stack();
    test_position_armies_on_battlefield();

    system("pause");
    return 0;
}