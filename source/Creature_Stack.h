#ifndef CREATURE_STACK_H
#define CREATURE_STACK_H

#include <iostream>
#include "../utilities/types.h"
#include "Team.h"
#include "Creature.h"
#include "Position.h"

// get hero's special abilities form creature and place in creature_stack
// allow creature to hold up to 3 buffs/debuffs and reduce their duration on each turn with 1
// fix function new_turn
// add defend to attack function
// make creature a struct to be used as a library (could be added in a namespace) and leave only getters in it. all setters and modifiers should be in creature stack.
// Stack should be constructed with the help of a copy constructor when it comes to creatures

enum Stack_Action // Used on every turn of a stack during battle
{
    Attack,
    Defend,
    Wait,
    Skip
};

class Stack
{
    private:
        Team _team = Team::Neutral; // MUST BE INHERITED
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

        struct hero_secondary_skills
        {
            uint8_t _hero_level = 0;
            std::string _hero_specialty_name = "";
            Skill_level _hero_level_of_archery    = Skill_level::None;
            Skill_level _hero_level_of_offense    = Skill_level::None;
            Skill_level _hero_level_of_armorer    = Skill_level::None;
            Skill_level _hero_level_of_resistance = Skill_level::None;
            Skill_level _hero_level_of_leadership = Skill_level::None;
            Skill_level _hero_level_of_luck       = Skill_level::None;

            // Constructs a private structure containing data affecting battles.
            hero_secondary_skills( const uint8_t hero_level = 0,
                                   const std::string specialty_name = "",
                                   const Skill_level level_of_archery = Skill_level::None,
                                   const Skill_level level_of_offense = Skill_level::None,
                                   const Skill_level level_of_armorer = Skill_level::None,
                                   const Skill_level level_of_resistance = Skill_level::None,
                                   const Skill_level level_of_leadership = Skill_level::None,
                                   const Skill_level level_of_luck = Skill_level::None ) :
                                   _hero_level(hero_level),
                                   _hero_specialty_name(specialty_name),
                                   _hero_level_of_archery(level_of_archery),
                                   _hero_level_of_offense(level_of_offense),
                                   _hero_level_of_armorer(level_of_armorer),
                                   _hero_level_of_resistance(level_of_resistance),
                                   _hero_level_of_leadership(level_of_leadership),
                                   _hero_level_of_luck(level_of_luck)
                                   {};
        }hero_secondary_skills;

        uint32_t _number;
        Position _pos = Position(0, 0);
        uint8_t _distance_traveled = 0;
        bool _has_perished = false;
        uint8_t _retaliations_left = 1; // not applicable for special ability 'unlimited retaliations'
        Stack_Action _action = Stack_Action::Attack;

        // Each creature can hold up to 3 spell effects at the same time.
        // std::array< Spell - duration , 3 > _spell_slots; // Should work as LIFO but also be able to have spells removed regardless of the order - thus normal container with fixed lenght.

    public:
        // Parametrized constructor used during battle.
        Stack(const Creature creature, const uint32_t number, const uint8_t pos_x, const uint8_t pos_y, const Team team);
        
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
        
        // Used when stacks are removed from an army or move from one army to another;
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

        void set_number(uint32_t number) { _number = number; _has_perished = !number; set_action(Stack_Action::Skip); }; // when receiving damage
        uint32_t get_number() {return _number; };

        void set_position(Position position) { _pos = position; };
        void set_position(uint8_t x, uint8_t y) { _pos = {x, y}; };
        Position get_position() { return _pos; };

        uint8_t get_distance_traveled() { return _distance_traveled; };

        void set_has_perished(bool has_perished) { _has_perished = has_perished; }; // when a stack dies
        bool get_has_perished() { return _has_perished; }; // to skip turns during battle, forbid attacks and reduce retaliation

        void set_retaliations_left(uint8_t retaliations) { _retaliations_left = retaliations; };
        uint8_t get_retaliations_left() { return _retaliations_left; };

        void set_action(Stack_Action action) { _action = action; };
        Stack_Action get_action() { return _action; };

        void set_hero_level(const uint8_t level) { hero_secondary_skills._hero_level = level; };
        uint8_t get_hero_level()                 { return hero_secondary_skills._hero_level; };

        void set_hero_specialty_name(const std::string name) { hero_secondary_skills._hero_specialty_name = name; };
        std::string get_hero_specialty_name()                { return hero_secondary_skills._hero_specialty_name; };

        void set_hero_level_of_archery(const Skill_level level)    { hero_secondary_skills._hero_level_of_archery = level; };
        Skill_level get_hero_level_of_archery()                    { return hero_secondary_skills._hero_level_of_archery;  };

        void set_hero_level_of_offense(const Skill_level level)    { hero_secondary_skills._hero_level_of_offense = level; };
        Skill_level get_hero_level_of_offense()                    { return hero_secondary_skills._hero_level_of_offense;  };

        void set_hero_level_of_armorer(const Skill_level level)    { hero_secondary_skills._hero_level_of_armorer = level; };
        Skill_level get_hero_level_of_armorer()                    { return hero_secondary_skills._hero_level_of_armorer;  };

        void set_hero_level_of_resistance(const Skill_level level) { hero_secondary_skills._hero_level_of_resistance = level; };
        Skill_level get_hero_level_of_resistance()                 { return hero_secondary_skills._hero_level_of_resistance;  };

        // Stack's number and/or remaining health of last units get affected.
        void recieve_damage(uint32_t damage);
        
        // Updates attributes, buffs and debuffs in the beggning of each new turn.
        void new_turn(); // should be called simultaiously for every creature on the battle field

        // On stack's turn:
        // 1. Roll for negative morale - if negative => skip
        // 2. Wait / Defend / Move / Attack (roll for luck, target = able to reach / shoot) / Cast creature spell
        // 3. Roll for positive morale - if positive => do 2 again
        void take_action(); // do any of the following functions

        // Decides if stack will act upon its turn during battle.
        bool roll_negative_morale(); // before initial action in turn

        // Decides if stack will act again in the end its turn during battle.
        bool roll_positive_morale(); // after initial action in turn

        // Returns -1/0/1, refering to the type of attack (unlucky/non-lucky/lucky strike) a stack will perform on its turn.
        int8_t roll_luck();

        // Skip stack's action and return to it later during the same battle turn.
        void wait() { set_action(Stack_Action::Wait); };

        // Stack does nothing, but gains bonus defense skill during the battle turn. 
        void defend() { set_action(Stack_Action::Defend); };

        // Reposition stack on the battle field according to stack speed and objects.
        void move(uint8_t x, uint8_t y);

        // Stack attacks another stack (defender), causing the defender to take damage and occasionaly retaliate.
        void attack(Stack& defender, bool attack_is_retaliation = false);

        // Checks if a ranged stack can shoot = has ammo and is not obstructed by an active enemy.
        bool can_shoot();

        // Checks if target is reachable for melee attack.
        bool target(Stack& stack);

        uint8_t get_distance_to_target(Stack& stack) { return std::abs(stack.get_position().x - get_position().x) + std::abs(stack.get_position().y - get_position().y); };
        
        // Returns a unlucky/non-lucky/lucky strike to the initial attacker.
        void retaliate(Stack& attacker);

        // Prints information of the stack during battle = creature forming the stack + hp left + shots left + stack number, stack position, buffs and defbuffs
        void print_battle_info();

        // Prints information of the stack outide battle = creature forming the stack + hp left + shots left + stack number, stack position, buffs and defbuffs
        void print_full_info();
};

#endif