#ifndef BATTLEFIELD_TILE_H
#define BATTLEFIELD_TILE_H

#include <iostream>
#include <vector>
#include "../utilities/types.h"
#include "Team.h"
#include "Creature_Stack.h"


namespace Battlefield
{
    constexpr uint8_t LENGTH = 15;
    constexpr uint8_t WIDTH  = 11;
    constexpr char ARMY_CHAR = '+'; // used for default army character in function arguments
};


struct Battlefield_Tile
{
    public:
        enum Tile
        {
            Normal,
            Unreachable,   // according to objects and Format
            Tower,         // can be destroyed by catapults, Cyclopses and Cyclops Kings
            Wall,          // can be destroyed by catapults, Cyclopses and Cyclops Kings
            Fortification, // river, lava, etc.
            Obstacle,      // removable with magic
            Land_Mine,     // can be casted TO DO : add visibility
            Quicksand,     // can be casted TO DO : add visibility
            Army
        };
        
    private:
        char _symbol = '_';
        Tile _tile = Tile::Normal;
        Team _team = Team::Neutral; // for representation purposes
    
    public:
        Battlefield_Tile( const Tile tile = Tile::Normal, const Team team = Team::Neutral );

        ~Battlefield_Tile();
        
        char get_symbol() { return _symbol; }

        Tile get_tile() { return _tile; }

        Team get_team() { return _team; }

        // Returns 'true' if the tile can be reached by a creature stack.
        bool is_reachable();

        // Used to update the symbol and team of a tile accordingly.
        void update_symbol(const Team team = Team::Neutral, const char ch = Battlefield::ARMY_CHAR);

        // Sets the tile, symbol and team accordingly.
        void setup_tile(const Tile tile = Tile::Normal, const Team team = Team::Neutral, const char ch = Battlefield::ARMY_CHAR);

        // Set tile to 'Normal' and team to 'Neutral'. Used when a creature stack moves from a tile / dies or a structure/obstacle gets destroyed.
        void reset_tile();
};

#endif