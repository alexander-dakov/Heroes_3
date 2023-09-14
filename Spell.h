#ifndef SPELL_H
#define SPELL_H

#include <iostream>
#include "types.h"
#include "Skill_level.h"

enum School_of_magic
{
      Air = 1, // 1
      Water,   // 2
      Earth,   // 3
      Fire     // 4
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
            Skill_level _level;
            std::string _mana_cost;
            Effect _effect;
            std::string _definition;
            uint8_t _duration;

      public:
            Spell();

            ~Spell();
            
            std::string get_name() { return _name; };

            School_of_magic get_school_of_magic() { return _school_of_magic; };

            Skill_level get_level() { return _level; };

            std::string get_mana_cost() { return _mana_cost; };

            Effect get_effect() { return _effect; }; 

            std::string get_definition() { return _definition; };

            uint8_t get_duration() { return _duration; };
};


#endif