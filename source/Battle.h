#ifndef BATTLE_H
#define BATTLE_H

#include <iostream>
#include "../utilities/types.h"
#include "Terrains.h" 
#include "Hero.h"

enum class Format
{
    Normal,
    Siege,
    Surrounded,
    Ships
};

class Battle
{
    private:
    
        Terrain terrain;
        uint8_t length = 15;
        uint8_t width = 11;
        Hero& attacker; // left side
        Hero& defender; // right side
        // Defender may not have a hero. A possible solution is to create a new instance of a dummy/fake hero which will have no army bonuses. He will be there simply to 'carry' the army.
        // May be there should be struct Army which will be comprised of 7 slots for creatures with some in-battle modifiers as private fields (has_perished, retaliations_left, etc.), instead of having some stacks assigned via pointer to a hero.
        
        // May be it will be better for class Battle to have the methods take_action(), attack(), wait(), defend(), move(), instead of class Stack.
        // Items which have effect - "Decrease enemy ...", "-? to enemy ...", "Negate all ? bonuses ...", etc. should take place here. 
    public:

        Battle();

        ~Battle();

        Terrain get_terrain();
        uint8_t get_length();
        uint8_t get_width();
};


#endif