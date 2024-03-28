#ifndef SPELL_H
#define SPELL_H

#include <iostream>
#include "../utilities/types.h"
#include "Skill_level.h"

enum class School_of_magic
{
      Air = 1, // 1
      Water,   // 2
      Earth,   // 3
      Fire     // 4
};

enum class Spell_level
{
      None,   // 0 - for coding purposes
      First,  // 1
      Second, // 2
      Third,  // 3
      Fourth, // 4
      Fifth   // 5
};

enum Effect
{
      Defensive = 1, // 1
      Offensive,     // 2
      Deal_damage    // 3
};

class Spell
{
      private:
            std::string _name;
            School_of_magic _school_of_magic;
            Spell_level _spell_level;
            Skill_level _skill_level;
            std::string _mana_cost;
            Effect _effect;
            std::string _description;
            uint8_t _duration;

      public:
            Spell() {};

            ~Spell() {};
            
            std::string get_name() { return _name; };

            School_of_magic get_school_of_magic() { return _school_of_magic; };

            Spell_level get_spell_level() { return _spell_level; };

            Skill_level get_skill_level() { return _skill_level; };

            std::string get_mana_cost() { return _mana_cost; };

            Effect get_effect() { return _effect; }; 

            std::string get_description() { return _description; };

            uint8_t get_duration() { return _duration; };
};


#endif