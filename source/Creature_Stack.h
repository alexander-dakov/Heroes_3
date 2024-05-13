#ifndef CREATURE_STACK_H
#define CREATURE_STACK_H

#include <iostream>
#include "../utilities/types.h"
#include "Team.h"
#include "Creature.h"
#include "Position.h"
#include "Creature_List.cpp"

// TO DO :
// get hero's special abilities form creature and place in creature_stack
// allow creature to hold up to 3 buffs/debuffs and reduce their duration on each turn with 1
// fix function new_turn
// add defend to attack function
// make creature a struct to be used as a library (could be added in a namespace) and leave only getters in it. all setters and modifiers should be in creature stack.
// Stack should be constructed with the help of a copy constructor when it comes to creatures

constexpr uint8_t min_num_for_stack_to_count_as_group_to_calc_rand_dmg = 10;

enum Stack_Action // Used on every turn of a stack during battle
{
    Attack, // normal state in which the stack is going to move or attacks
    Defend,
    Wait,
    Skip // perished / negative morale rolled / blinded
};

class Stack
{
    private:
        Team _team = Team::Neutral;
        Creature _creature;
        struct battle_stats
        {
            uint8_t _att;                  // modified by hero's attack skill
            uint8_t _def;                  // modified by battle and hero's defense skill
            uint8_t _shots_left;           // modified by battle and ammo cart
            uint16_t _hp;                  // modified by battle and hero's items
            uint16_t _hp_left;             // modified by battle and hero's items
            uint8_t _speed;                // modified by hero's items
            Morale _morale;                // modified by hero's morale
            Luck _luck;                    // modified by hero's luck
            uint8_t _number_of_casts_left; // modified by battle

            // Constructs a private structure containing data used during battles when no hero is leading the army.
            battle_stats(Creature _creature)
            {
                _att        = _creature.get_att();
                _def        = _creature.get_def();
                _shots_left = _creature.get_shots();
                _hp         = _creature.get_hp();
                _hp_left    = _hp;
                _speed      = _creature.get_speed();
                _morale     = _creature.get_morale();
                _luck       = _creature.get_luck();
                _number_of_casts_left = _creature.get_number_of_casts();
            };
        }battle_stats;

        uint32_t _number;
        char _battlefield_symbol = ' ';
        Position _pos = Position(0, 0);
        uint8_t _distance_traveled = 0;
        bool _has_perished = false;
        uint8_t _retaliations_left = 1; // can be 0,1,2. Not applicable for special ability 'Unlimited retaliations'.
        Stack_Action _action = Stack_Action::Attack;

        // Each creature can hold up to 3 spell effects at the same time.
        // std::array< Spell - duration , 3 > _spell_slots; // Should work as LIFO but also be able to have spells removed regardless of the order - thus normal container with fixed length.

        bool _has_acquired_regeneration = false;

    public:
        // Parametrized constructor used during battle.
        Stack(const Creature creature, const uint32_t number, const uint8_t pos_x, const uint8_t pos_y, const char battlefield_symbol, const Team team);
        
        // Parametrized constructor used in when purchasing a stack, moving it from one army to another or seperating it into smaller stacks.
        Stack(const Creature creature, const uint32_t number, const Team team);

        // Copy constructors by reference. Used when moving a stack from one army to another or seperating it into smaller stacks.
        Stack(const Stack& stack, const uint32_t number);

        // Copy constructors by pointer. Used when moving a stack from one army to another or seperating it into smaller stacks.
        Stack(const Stack* stack, const uint32_t number);
        
        // Destructor
        ~Stack();

        Team get_team() { return _team; };
        std::string get_team_as_string();

        Creature* get_creature() { return &_creature; };

        std::string get_creature_name() { return get_creature()->get_name(); };        // for ease of code writing
        Faction get_faction() { return get_creature()->get_faction(); };               // for ease of code writing
        Terrain get_native_terrain() { return get_creature()->get_native_terrain(); }; // for ease of code writing

        // Used when stacks are removed from an army or are moved from one army to another;
        void reset_stats();

        void set_att(const uint8_t att) { battle_stats._att = att; };
        uint8_t get_att() { return battle_stats._att; };

        void set_def(const uint8_t def) { battle_stats._def = def; };
        uint8_t get_def() { return battle_stats._def; };

        void set_shots_left(const uint8_t shots_left) { battle_stats._shots_left = shots_left; };
        uint8_t get_shots_left() { return battle_stats._shots_left; };
        
        void set_hp(const uint16_t hp) { battle_stats._hp = hp; }; // for bonuses from items
        uint16_t get_hp() { return battle_stats._hp; };

        void set_hp_left(const uint16_t hp) { battle_stats._hp_left = std::min(hp, battle_stats._hp); };
        uint16_t get_hp_left() { return battle_stats._hp_left; };

        void set_speed(const uint8_t speed) { battle_stats._speed = speed; };
        uint8_t get_speed() { return battle_stats._speed; };

        void set_morale(const Morale morale);
        void add_morale(const Morale morale);
        Morale get_morale() { return battle_stats._morale; };

        void set_luck(const Luck luck) { battle_stats._luck = luck; };
        void add_luck(const Luck luck) { battle_stats._luck = static_cast<Luck>( std::min( std::max( static_cast<int8_t>(battle_stats._luck) + static_cast<int8_t>(luck), -3), 3) ); };
        Luck get_luck() { return battle_stats._luck; };

        uint8_t get_number_of_casts_left() { return battle_stats._number_of_casts_left; };

        void set_number(const uint32_t number) { _number = number; _has_perished = !number; set_action(Stack_Action::Skip); }; // when recieving damage
        uint32_t get_number() {return _number; };

        void set_battlefield_symbol(const char ch) { _battlefield_symbol = ch; };
        char get_battlefield_symbol() { return _battlefield_symbol; };
        void reset_battlefield_symbol() { _battlefield_symbol = ' '; };

        void set_position(const Position position) { _pos = position; };
        void set_position(const uint8_t x, const uint8_t y) { _pos = {x, y}; };
        Position get_position() { return _pos; };

        void set_distance_traveled(const uint8_t distance_traveled) { _distance_traveled = distance_traveled; };
        uint8_t get_distance_traveled() { return _distance_traveled; };

        void set_has_perished(const bool has_perished) { _has_perished = has_perished; }; // when a stack dies
        bool get_has_perished() { return _has_perished; }; // to skip turns during battle, forbid attacks and reduce retaliation

        void set_retaliations_left(const uint8_t retaliations) { _retaliations_left = retaliations; };
        uint8_t get_retaliations_left() { return _retaliations_left; };

        void set_action(const Stack_Action action) { _action = action; };
        Stack_Action get_action() { return _action; };

        void set_has_acquired_regeneration(const bool regenerates) { _has_acquired_regeneration = regenerates; };
        bool get_has_acquired_regeneration() { return _has_acquired_regeneration; };

        // Stack's number and/or remaining health of last units get affected.
        void recieve_damage(const uint32_t damage);

        // Prints information of the stack during battle = creature forming the stack + hp left + shots left + stack number, stack position, buffs and defbuffs
        void print_battle_info();

        // Prints information of the stack outide battle = creature forming the stack + hp left + shots left + stack number, stack position, buffs and defbuffs
        void print_full_info();
};

#endif