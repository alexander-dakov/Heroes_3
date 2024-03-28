#ifndef TESTS_H
#define TESTS_H

#include <iostream>
#include <memory>
#include "tests.h"
#include "../utilities/types.h"
#include "../source/Creature_Stack.cpp"
#include "../source/Creature_List.cpp"
#include "../source/Hero_List.cpp"
#include "../source/Item_List.cpp"
#include "../source/Battle.h"

// Flushes std::cout and std::cerr and prints a message in order to mark the output of a test.
void print_before_testing_output();

// Prints which of the some of the many special abilities a certain creature has.
void print_some_special_abilities(Creature* c);

// Constructs an instance of struct Creature and then calls 2 copy constructors - by reference and by pointer.
void test_create_creature();

// Constructs enough different instances of class Stack to fill all of the hero's army slots.
void test_create_creature_stack();

// Constructs creature stacks : "attacker" and "defender" (from different teams) and "attacker" attacks "defender" to check if damage gets calculated rightfully.
void test_creature_stack_vs_creature_stack();

// Constructs an instance of struct Item.
void test_create_item();

// Constructs an instance of class Hero.
void test_create_hero();

// Checks if hero's stats get hero bonuses when : hero levels up / gets updated morale and luck / equips an item / unequips an item.
void test_hero_item_bonuses();

// Checks if creature stacks' battle stats get hero bonuses when they : become part of the army / are removed from the army / hero levels up / gets updated morale and luck / equips an item / unequips an item.
void test_army_hero_bonuses();

// Constructs creature stacks : "attacker" and "defender" (from different teams). "attacker" gets assigned to a hero's army to gain bonuses and "attacker" attacks "defender" to check if damage gets calculated rightfully.
void test_hero_vs_creature_stack();

// Concstructs an instance of Battle by : creating a field, positioning the armies with their bonuses from their respective heroes on said field and applying terrain bonuses to the stacks.
void test_position_armies_on_battlefield();

#endif