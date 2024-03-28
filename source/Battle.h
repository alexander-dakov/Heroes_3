#ifndef BATTLE_H
#define BATTLE_H

#include <iostream>
#include "../utilities/types.h"
#include "Battlefield_Tile.h"
#include "Terrains.h"
#include "Creature_Stack.h"
#include "Hero.h"

constexpr uint8_t BATTLEFIELD_LENGTH = 15;
constexpr uint8_t BATTLEFIELD_WIDTH  = 11;

enum class Battle_Format
{
    Normal,
    Siege,      // like 'Normal' but builds a wall if the town has it
    Surrounded, // Creature bank
    Ships
};

class Battle
{
    private:
        Hero& _attacker; // left side
        Hero& _defender; // right side
        // Defender may not have a hero. A possible solution is to create a new instance of a dummy/fake hero which will have no army bonuses. He will be there simply to 'carry' the army.
        // Maybe there should be struct Army which will be comprised of 7 slots for creatures with some in-battle modifiers as private fields (has_perished, retaliations_left, etc.), instead of having some stacks assigned via pointer to a hero.
        
        // Maybe it will be better for class Battle to have the methods take_action(), attack(), wait(), defend(), move(), instead of class Stack.
        // Items which have effect - "Decrease enemy ...", "-? to enemy ...", "Negate all ? bonuses ...", etc. should take place here.

        Battlefield_Tile battlefield[BATTLEFIELD_WIDTH][BATTLEFIELD_LENGTH];
        Battle_Format _format;
        Terrain _terrain;

    public:
        // no default or copy constructors allowed
        Battle(Hero& attacker, Hero& defender, const Battle_Format format, const Terrain terrain); // constructing the battlefield, managing the event and then destroying the constructed objects 

        ~Battle();

        Hero* get_attacker() { return &_attacker;}
        Hero* get_defender() { return &_defender;}

        void check_valid_battlefield_pos(const uint8_t x, const uint8_t y);

        void set_battlefield_pos(const uint8_t x, const uint8_t y, const Tile tile = Tile::Normal, const Team team = Team::Neutral, const char ch = ARMY_CHAR);
        char get_battlefield_pos(const uint8_t x, const uint8_t y);

        void set_battlefield_pos(const Position pos, const Tile tile = Tile::Normal, const Team team = Team::Neutral, const char ch = ARMY_CHAR);
        char get_battlefield_pos(const Position pos);

        // Places a stack on the battlefield if the tile is free and reachable and changes the tile's team.
        void place_stack_on_battlefield(Stack* stack, const char ch);

        Battle_Format get_battle_format() { return _format;  };
        Terrain get_terrain()             { return _terrain; };

        // Populate the battlefield with tiles, set up the unreachable tiles according to the format of the battle and position the armies.
        void set_up_battlefield();
        
        // Prints the battlefield with colors according to the team + a legend below.
        void print_battlefield();

        // Applies terrain bonuses to a stack of creatures.
        void apply_terrain_bonuses_to_stack(Stack* stack); // should be applicable to stacks individually, as new stacks of Air/Water/Fire/Earth Elementals might be summoned on the battle field
        
        // Sets stack's position (private member) and copies it to the battlefield.
        void position_armies();
};


#endif