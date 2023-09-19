#ifndef TESTS_H
#define TESTS_H

#include <iostream>

// Prints a message in the out stream in order to mark the output of a test 
void print_before_testing_output();

// Constructs an instance of class Creature and then calls 2 copy constructors - by reference and by pointer
void test_create_creature();

// Constructs enough instances of class Stack to fill all of the hero's army slots. Stacks are called "stack_1, stack_2 , etc." as the need to be easily refered to in battle.
void test_create_creature_stack();

#endif