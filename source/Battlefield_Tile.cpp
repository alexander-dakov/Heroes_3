#include "Battlefield_Tile.h"

Battlefield_Tile::Battlefield_Tile( const Tile tile, const Team team ) : _tile(tile)
{
      update_symbol(team);
}

Battlefield_Tile::~Battlefield_Tile()
{
      // printf( "A tile of the battlefield was destroyed!\n" );
}

bool Battlefield_Tile::is_reachable()
{
      auto t = get_tile();
      return (t == Tile::Normal) + (t == Tile::Fortification) + (t == Tile::Land_Mine) + (t == Tile::Quicksand);
}

void Battlefield_Tile::update_symbol(const Team team, const char ch)
{
      switch( get_tile() )
      {
            case Tile::Normal        : _symbol = '_'; _team = Team::Neutral; break;
            case Tile::Unreachable   : _symbol = 'X'; _team = Team::Neutral; break;
            case Tile::Tower         : _symbol = 'T'; _team = team;          break;
            case Tile::Wall          : _symbol = 'W'; _team = team;          break;
            case Tile::Fortification : _symbol = 'F'; _team = team;          break;
            case Tile::Obstacle      : _symbol = 'O'; _team = Team::Neutral; break;
            case Tile::Land_Mine     : _symbol = 'M'; _team = team;          break;
            case Tile::Quicksand     : _symbol = 'Q'; _team = team;          break;
            case Tile::Army          : _symbol = ch;  _team = team;          break;
      }
}

void Battlefield_Tile::setup_tile(const Tile tile, const Team team, const char ch)
{
      _tile = tile;
      update_symbol(team, ch);
}

void Battlefield_Tile::reset_tile()
{
      _tile = Tile::Normal;
      update_symbol();
}