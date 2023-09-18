#ifndef BATTLE_H
#define BATTLE_H

#include <iostream>
#include "../utilities/types.h"
#include "Adventure_Map/Terrains.h" 
#include "Heroes/Hero.h"


class Battle
{
    private:
    
        Terrain terrain;
        uint8_t length = 15;
        uint8_t width = 11;
        Hero& attacker; // left side
        Hero& defender; // right side

    public:

        Battle();

        ~Battle();

        Terrain get_terrain();
        uint8_t get_length();
        uint8_t get_width();
};


#endif