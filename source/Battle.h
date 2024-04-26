#ifndef BATTLE_H
#define BATTLE_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>
#include <limits>
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
        // Maybe it will be better for class Battle to have the methods take_action(), attack(), wait(), defend(), move(), instead of class Stack.
        // Items which have effect - "Decrease enemy ...", "-? to enemy ...", "Negate all ? bonuses ...", etc. should take place here.

        Battlefield_Tile battlefield[BATTLEFIELD_WIDTH][BATTLEFIELD_LENGTH];
        Battle_Format _format;
        Terrain _terrain;

        uint16_t _round = 0;
        std::vector<Stack*> _turns;
        std::vector<Stack*> _wait_turns;

        bool _spirit_of_oppression_present = false;
        bool _hourglass_of_evil_hour_present = false;

    public:
        // no default or copy constructors allowed
        Battle(Hero& attacker, Hero& defender, const Battle_Format format, const Terrain terrain); // constructing the battlefield, managing the event and then destroying the constructed objects 

        ~Battle();

        Hero* get_attacker() { return &_attacker;}
        Hero* get_defender() { return &_defender;}

        Battle_Format get_battle_format() { return _format;  };
        Terrain get_terrain()             { return _terrain; };

        uint16_t get_round() { return _round; };

        auto get_turns()                       { return &_turns;   };
        Stack* get_stack_turn(const uint8_t i) { return _turns[i]; };

        auto get_wait_turns()                       { return &_wait_turns;   };
        Stack* get_stack_wait_turn(const uint8_t i) { return _wait_turns[i]; };

        bool get_spirit_of_oppression_present()   { return _spirit_of_oppression_present;  };
        bool get_hourglass_of_evil_hour_present() { return _hourglass_of_evil_hour_present; };

        Position enter_battlefield_coordinates();
        
        void check_valid_battlefield_pos(const uint8_t x, const uint8_t y);

        void set_battlefield_pos(const uint8_t x, const uint8_t y, const Tile tile = Tile::Normal, const Team team = Team::Neutral, const char ch = ARMY_CHAR);
        char get_battlefield_pos(const uint8_t x, const uint8_t y);

        void set_battlefield_pos(const Position pos, const Tile tile = Tile::Normal, const Team team = Team::Neutral, const char ch = ARMY_CHAR);
        char get_battlefield_pos(const Position pos);
        
        // Places a stack on the battlefield if the tile is free and reachable and changes the tile's team.
        void place_stack_on_battlefield(Stack* stack, const char ch);

        // Sets stack's position (private member) and copies it to the battlefield.
        void position_armies();
        
        // Populate the battlefield with tiles, set up the unreachable tiles according to the format of the battle and position the armies.
        void set_up_battlefield();

        // Prints the battlefield with colors according to the team + a legend below.
        void print_battlefield(Stack* current_stack);

        // Applies terrain bonuses to a stack of creatures.
        void apply_terrain_bonuses_to_stack(Stack* stack); // should be applicable to stacks individually, as new stacks of Air/Water/Fire/Earth Elementals might be summoned on the battle field

        // Updates the round counter, the action and buffs/debuffs on each stack, and then reorders the turns of all stacks according to the fastest units on the battlefield.
        void set_up_next_round();

        // Populate the turns with pointers to army stacks and order them according to the fastest units on the battlefield. It is used only before the first round.
        void set_up_initial_turns();
        
        // Orders the stacks that allready exist in the turn vector. It is used before the begining of every round after the first one.
        void set_up_normal_turns();

        // Orders the stacks that decided to wait during their own turn.
        void set_up_wait_turns();

        // Prints the normal and then the wait turns, as a chain, in which every stack is represented with the same symbol used to on the battlefield.
        void print_turns();

        // On stack's turn:
        // 1. Roll for negative morale - if negative => skip
        // 2. Wait / Defend / Move / Attack (roll for luck, target = able to reach / shoot) / Cast creature spell
        // 3. Roll for positive morale - if positive => do 2 again
        void on_stack_turn(Stack* stack, bool morale_rolled = false); // do any of the following functions

        std::string select_action_for_stack(const bool stack_can_wait);

        // Checks if heroes have equipped items which debuff the moral and luck of every stack.
        void set_global_moral_and_luck_debuffs();

        // Returns 'true' if the tile can be occupied by the stack and is located within the stack's reach.
        bool tile_is_reachable(const uint8_t x, const uint8_t y, Stack* stack);

        // Returns 'true' if a tile next to an enemy can be occupied by the stack and is located within the stack's reach.
        bool enemy_is_reachable(Stack* stack, Stack* enemy_stack);

        // Shows the coordinates of all surrounding tiles from which the defending stack can be attack, and the player picks one.
        Position* select_location_around_enemy_stack(Stack* stack, Stack* enemy_stack);

        Stack* find_existing_enemy_stack_via_symbol(const char* ch, const Team team);

        // Checks if there is an adjacent enemy stack.
        bool has_adjacent_enemy(Stack* stack);

        // Returns 'true' if the stacks are adjacent and 'false', if not.
        bool stacks_are_adjacent(Stack* stack, Stack* enemy_stack);

        // Moves stack according to type of traveling (walking, flying, teleporting) and updates the battlefield.
        void move_stack(Stack* stack, const uint8_t x, const uint8_t y);

        // Moves the stack if needed and attacks the enemy stack.
        void attack_stack(Stack* attacking_stack, Stack* defending_stack);

        // Checks if a ranged stack can shoot = has ammo + if stack has no melee penalty when there is adjacent enemy.
        bool stack_can_shoot(Stack* attacking_stack, Stack* defending_stack);

        bool check_battle_finished();
};

#endif