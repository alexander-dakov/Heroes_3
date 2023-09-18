#ifndef CREATURE_STACK_H
#define CREATURE_STACK_H

#include <iostream>
#include "../utilities/types.h"
#include "Team.h"
#include "Creature.h"
#include "Hero.h"
#include "Position.h"

// get hero's special abilities form creature and place in creature_stack
// allow creature to hold up to 3 buffs/debuffs and reduce their duration on each turn with 1
// fix function new_turn
// add defend to attack function
// make creature a struct to be used as a library (could be added in a namespace) and leave only getters in it. all setters and modifiers should be in creature stack.
// Stack should be constructed with the help of a copy constructor when it comes to creatures

enum Stack_Action
{
    Attack,
    Defend,
    Wait,
    Skip
};

class Stack
{
    private:
        // Hero& _hero;
        Team _team = Team::None; // MUST BE INHERITED
        Creature _creature;

        struct battle_stats
        {
            uint8_t _att; // modified by hero's attack skill
            uint8_t _def; // modified by hero's defence skill
            uint8_t _shots_left; // modified battle and ammo cart
            uint8_t _hp; // modified by hero's items
            uint8_t _hp_left; // modified battle and hero's items
            uint8_t _speed; // modified by hero's items
            Morale _morale; // modified by hero's morale
            Luck _luck; // modified by hero's luck

            battle_stats(Creature _creature)
            {
                _att = _creature.get_att();
                _def = _creature.get_def();
                _shots_left = _creature.get_shots();
                _hp = _creature.get_hp();
                _hp_left = _hp;
                _speed = _creature.get_speed();
                _morale = _creature.get_morale();
                _luck = _creature.get_luck();
            };

            // battle_stats(Creature _creature, Hero& _hero)
            // {
            //     _att = _creature.get_att() + _hero.get_attack();
            //     _def = _creature.get_def() + _hero.get_defence();
            //     _shots_left = _creature.get_shots();
            //     _hp = _creature.get_hp();
            //     _hp_left = _hp;
            //     _speed = _creature.get_speed();
            //     _morale = static_cast<Morale>( std::min( std::max( static_cast<int8_t>(_creature.get_morale()) + static_cast<int8_t>(_hero.get_morale()), -3), 3) );
            //     _luck   = static_cast<Luck>  ( std::min( std::max( static_cast<int8_t>(_creature.get_luck())   + static_cast<int8_t>(_hero.get_luck()),   -3), 3) );
            // };
        }battle_stats;

        uint32_t _number;
        Position _pos = Position(0, 0);
        bool _has_perished = false;
        Stack_Action _action = Stack_Action::Attack;


        struct hero_specialty_and_secondary_skills
        {
            std::string _hero_specialty_name = "";

            Skill_level _level_of_archery    = Skill_level::None;
            Skill_level _level_of_offence    = Skill_level::None;
            Skill_level _level_of_armorer    = Skill_level::None;
            Skill_level _level_of_resistance = Skill_level::None;
            Skill_level _level_of_leadership = Skill_level::None;
            Skill_level _level_of_luck       = Skill_level::None;

            hero_specialty_and_secondary_skills()
            {
                _hero_specialty_name = "";

                _level_of_archery    = Skill_level::None;
                _level_of_offence    = Skill_level::None;
                _level_of_armorer    = Skill_level::None;
                _level_of_resistance = Skill_level::None;
                _level_of_leadership = Skill_level::None;
                _level_of_luck       = Skill_level::None;
            };

            // hero_specialty_and_secondary_skills(Hero& _hero) // not called when no hero is available
            // {
            //     _hero_specialty_name = _hero.get_specialty().get_name();

            //     for(uint8_t i = 0; i < MAX_SECONDARY_SKILLS; i++)
            //     {
            //         if     ( _hero.get_secondary_skill(i)->get_name() == "Archery")    { _level_of_archery    = _hero.get_secondary_skill(i)->get_level(); }
            //         else if( _hero.get_secondary_skill(i)->get_name() == "Offence")    { _level_of_offence    = _hero.get_secondary_skill(i)->get_level(); }
            //         else if( _hero.get_secondary_skill(i)->get_name() == "Armorer")    { _level_of_armorer    = _hero.get_secondary_skill(i)->get_level(); }
            //         else if( _hero.get_secondary_skill(i)->get_name() == "Resistance") { _level_of_resistance = _hero.get_secondary_skill(i)->get_level(); }
            //         else if( _hero.get_secondary_skill(i)->get_name() == "Leadership") { _level_of_leadership = _hero.get_secondary_skill(i)->get_level(); }
            //         else if( _hero.get_secondary_skill(i)->get_name() == "Luck")       { _level_of_luck       = _hero.get_secondary_skill(i)->get_level(); }
            //     }
            // };
        }hero_specialty_and_secondary_skills;

    public:
        // Stack(const Hero& hero, const Creature creature, const uint32_t number, const uint8_t pos_x, const uint8_t pos_y); // hero should be fixed 

        Stack(const Creature creature, const uint32_t number, const uint8_t pos_x, const uint8_t pos_y);
        
        Stack(const Creature creature, const uint32_t number);
        
        ~Stack();

        Team get_team() { return _team; };

        void set_att(const uint8_t att) { battle_stats._att = att; };
        uint8_t get_att() { return battle_stats._att; };

        void set_def(const uint8_t def) { battle_stats._def = def; };
        uint8_t get_def() { return battle_stats._def; };

        void set_shots_left(const uint8_t shots_left) { battle_stats._shots_left = shots_left; };
        uint8_t get_shots_left() { return battle_stats._shots_left; };
        
        void set_hp(const uint8_t hp) { battle_stats._hp = hp; }; // for bonuses from items
        uint8_t get_hp() { return battle_stats._hp; };

        void set_hp_left(const uint8_t hp) { battle_stats._hp_left = std::min(hp, battle_stats._hp); };
        uint8_t get_hp_left() { return battle_stats._hp_left; };

        void set_speed(const uint8_t speed) { battle_stats._speed = speed; };
        uint8_t get_speed() { return battle_stats._speed; };

        void set_morale(const Morale morale) { battle_stats._morale = morale; };
        void add_morale(const Morale morale) { battle_stats._morale = static_cast<Morale>( std::min( std::max( static_cast<int8_t>(battle_stats._morale) + static_cast<int8_t>(morale), -3), 3) ); };
        Morale get_morale() { return battle_stats._morale; };

        void set_luck(const Luck luck) { battle_stats._luck = luck; };
        void add_luck(const Luck luck) { battle_stats._luck = static_cast<Luck>( std::min( std::max( static_cast<int8_t>(battle_stats._luck) + static_cast<int8_t>(luck), -3), 3) ); };
        Luck get_luck() { return battle_stats._luck; };

        void set_number(uint32_t number) { _number = number; _has_perished = !number; set_action(Stack_Action::Skip); }; // when receiving damage
        uint32_t get_number() {return _number; };

        void set_initial_position(Position initial_position) { _pos = initial_position; };
        Position get_initial_position() { return _pos; };

        void set_has_perished(bool has_perished) { _has_perished = has_perished; } // when a stack dies
        bool get_has_perished() { return _has_perished; } // to skip turns during battle, forbid attacks and reduce retaliation

        void set_action(Stack_Action action) { _action = action; };
        Stack_Action get_action() { return _action; };

        std::string get_specialty()           { return hero_specialty_and_secondary_skills._hero_specialty_name; };
        Skill_level get_level_of_archery()    { return hero_specialty_and_secondary_skills._level_of_archery;    };
        Skill_level get_level_of_offence()    { return hero_specialty_and_secondary_skills._level_of_offence;    };
        Skill_level get_level_of_armorer()    { return hero_specialty_and_secondary_skills._level_of_armorer;    };
        Skill_level get_level_of_resistance() { return hero_specialty_and_secondary_skills._level_of_resistance; };

        void recieve_damage(uint32_t damage);
        

        void new_turn(); // called simultaiously for every creature on the battle field in the beggining of the new turn, in order to reset attributes, buffs and debuffs

        // On stack's turn:
        // 1. Roll for negative morale - if negative => skip
        // 2. Wait / Defend / Move / Attack (roll for luck, target = able to reach / shoot) / Cast creature spell
        // 3. Roll for positive morale - if positive => do 2 again
        void take_action(); // do any of the following functions

        bool roll_negative_morale(); // before initial action in turn
        bool roll_positive_morale(); // after initial action in turn
        int8_t roll_luck(); // before attack; returns -1/0/1 for unlucky/non-lucky/lucky strike

        void wait() { set_action(Stack_Action::Wait); }; // skip creature's turn and return to it later during the same turn
        void defend() { set_action(Stack_Action::Defend); };
        void move(uint8_t x, uint8_t y); // position stack on the battle field according to stack speed
        void attack(Stack& defender);

        bool can_shoot();
        bool target(Stack& stack);

        void retaliate(Stack& attacker);

        void print_full_info(); // full creature info + hp left + shots left + stack number, stack position, buffs and defbuffs
        // void print_full_info(Stack& stack); // for battle field
};

#endif