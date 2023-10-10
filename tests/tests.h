#ifndef TESTS_H
#define TESTS_H

#include <iostream>

// Prints a message in the out stream in order to mark the output of a test .
void print_before_testing_output();

// Constructs an instance of class Creature and then calls 2 copy constructors - by reference and by pointer.
void test_create_creature();

// Constructs enough different instances of class Stack to fill all of the hero's army slots.
void test_create_creature_stack();

// Constructs creature stacks : "attacker" and "defender" (from different teams) and "attacker" attacks "defender" to check if damage gets calculated rightfully.
void test_creature_stack_vs_creature_stack();

// Constructs an instance of class Hero.
void test_create_hero();

// Checks if creature stacks' battle stats get hero bonuses when they : become part of the army / are removed from the army / hero levels up / gets updated morale and luck / equips an item
void test_hero_army_bonuses();

// Constructs creature stacks : "attacker" and "defender" (from different teams). "attacker" gets assigned to a hero's army to gain bonuses and "attacker" attacks "defender" to check if damage gets calculated rightfully.
void test_hero_vs_creature_stack();

#endif