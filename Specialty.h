#ifndef SPECIALTY_H
#define SPECIALTY_H

#include <iostream>
#include "types.h"


struct Specialty
{
      private:
            std::string _name;
            std::string _effect;

      public:
            Specialty(std::string name, std::string effect) : _name(name), _effect(effect) {};

            std::string get_name()   { return _name;   };
            std::string get_effect() { return _effect; };
};

#endif