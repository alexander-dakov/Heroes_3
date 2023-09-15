#ifndef SECONDARY_SKILL_H
#define SECONDARY_SKILL_H

#include <iostream>
#include "utilities/types.h"
#include "Skill_level.h"


struct Secondary_Skill
{
      private:
            Skill_level _level;
            std::string _name;
            std::string _effect;

      public:
            Secondary_Skill(Skill_level level, std::string name, std::string effect) : _level(level), _name(name), _effect(effect) {};

            Skill_level get_level()  { return _level;  };
            std::string get_name()   { return _name;   };
            std::string get_effect() { return _effect; };
};

#endif