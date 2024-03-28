#include "Battle.h"

Battle::Battle( Hero& attacker, Hero& defender, const Battle_Format format, const Terrain terrain ) : _attacker(attacker), _defender(defender), _format(format), _terrain(terrain)
{
      set_up_battlefield();

      if( get_terrain() == Terrain::Dunes )
      {
            // TO DO : implement invisible quicksands on battlefield
      }
      else
            for( uint8_t i = 0; i < ARMY_SLOTS; i++ )
            {
                  if( _attacker.get_army_stack(i) != nullptr )
                        apply_terrain_bonuses_to_stack( _attacker.get_army_stack(i) );
                  if( _defender.get_army_stack(i) != nullptr )
                        apply_terrain_bonuses_to_stack( _defender.get_army_stack(i) );
            }

      { // formatted like this for ease of reading
            printf( "\nA battle between " );
            print_colored_string( attacker.get_name().c_str(), attacker.get_team() );
            printf( " and " );
            print_colored_string( defender.get_name().c_str(), defender.get_team() );
            printf( " has begun!\n" );
      }

      // set a queue of turns
      // while cycle - until an army dies or a hero decides to retreat
      {
            print_battlefield();
      }
}

Battle::~Battle()
{
      for( uint8_t i = 0; i < BATTLEFIELD_WIDTH; i++ )
            for( uint8_t j = 0; j < BATTLEFIELD_LENGTH; j++ )
                  battlefield[i][j].~Battlefield_Tile();

      printf( "The battlefield was destroyed!\n" );

      printf( "The battle has ended!\n" );
}

void Battle::check_valid_battlefield_pos(const uint8_t x, const uint8_t y)
{
      if( x < 0 || x >= BATTLEFIELD_LENGTH)
      {
            std::cerr << "Coordinate "<< x << " must be in the range [0;"<< BATTLEFIELD_LENGTH - 1 << "]!" << std::endl;
            abort();
      }

      if( y < 0 || y >= BATTLEFIELD_WIDTH)
      {
            std::cerr << "Coordinate "<< y << " must be in the range [0;"<< BATTLEFIELD_WIDTH - 1 << "]!" << std::endl;
            abort();
      }
}

void Battle::set_battlefield_pos(const uint8_t x, const uint8_t y, const Tile tile, const Team team, const char ch)
{
      check_valid_battlefield_pos(x, y);
      battlefield[y][x].setup_tile(tile, team, ch);
}

char Battle::get_battlefield_pos(const uint8_t x, const uint8_t y)
{
      check_valid_battlefield_pos(x, y);
      return battlefield[y][x].get_symbol();
}

void Battle::set_battlefield_pos(const Position pos, const Tile tile, const Team team, const char ch)
{
      check_valid_battlefield_pos(pos.x, pos.y);
      battlefield[pos.y][pos.x].setup_tile(tile, team, ch);
}

char Battle::get_battlefield_pos(const Position pos)
{
      check_valid_battlefield_pos(pos.x, pos.y);
      return battlefield[pos.y][pos.x].get_symbol();
}

void Battle::place_stack_on_battlefield(Stack* stack, const char ch)
{
      Position pos = stack->get_position();
      check_valid_battlefield_pos(pos.x, pos.y);

      if( !( battlefield[pos.y][pos.x].is_reachable() ) )
      {
            std::cerr << "Position on battlefield with coordinates [" << pos.x << ";" << pos.y <<"] is unreachable!"<< std::endl;
            abort();
      }
      set_battlefield_pos(stack->get_position(), Tile::Army, stack->get_team(), ch);
}

void Battle::set_up_battlefield()
{
      // Populate the battlefield
      {
            for( uint8_t i = 0; i < BATTLEFIELD_WIDTH; i++ )
                  for( uint8_t j = 0; j < BATTLEFIELD_LENGTH; j++ )
                        battlefield[i][j] = Battlefield_Tile();
      }
      
      // Set up the unreachable spots
      if( get_battle_format() == Battle_Format::Ships )
      {
            // TO DO : implement unreachable spots
      }
      else
      {
            if( get_battle_format() == Battle_Format::Siege )
            {
                  // TO DO : implement town walls
            }
      }

      // Position the armies
      position_armies();
}

void Battle::print_battlefield()
{
      printf("\n========================================");
      printf("\n________________________________________\n");
      printf(  "|                                      |\n");

      for( uint8_t i = 0; i < BATTLEFIELD_WIDTH; i++ )
      {
            printf("|    ");
            for( uint8_t j = 0; j < BATTLEFIELD_LENGTH; j++ )
            {
                  print_colored_string( battlefield[i][j].get_symbol(), battlefield[i][j].get_team() );
                  printf(" ");
            }
            printf("    |\n");
      }
      printf("|                                      |\n");
      printf("|______________________________________|\n");
      printf("\n");


      printf( "The army led by ");
      print_colored_string( get_attacker()->get_name().c_str(), get_attacker()->get_team() );
      printf( " :\n");
      for( uint8_t i = 0; i < ARMY_SLOTS; i++)
      {
            auto attacking_stack = get_attacker()->get_army_stack(i);
                  if( attacking_stack != nullptr )
                  {
                        print_colored_string(std::to_string(i + 1).c_str(), attacking_stack->get_team() );
                        printf( " = %d %s\n", attacking_stack->get_number(), attacking_stack->get_creature_name().c_str() );
                  }
      }

      printf("\n");

      printf( "The army led by ");
      print_colored_string( get_defender()->get_name().c_str(), get_defender()->get_team() );
      printf( " :\n");
      for( uint8_t i = 0; i < ARMY_SLOTS; i++)
      {
            auto defending_stack = get_defender()->get_army_stack(i);
                  if( defending_stack != nullptr )
                  {
                        print_colored_string(std::to_string(i + 1).c_str(), defending_stack->get_team() );
                        printf( " = %d %s\n", defending_stack->get_number(), defending_stack->get_creature_name().c_str() );
                  }
      }

      printf("\n========================================\n");
}

void Battle::apply_terrain_bonuses_to_stack( Stack* stack )
{
      if( get_terrain() == stack->get_native_terrain() ) // for normal terrains
      {
            stack->set_att( stack->get_att() + 1 ); 
            stack->set_def( stack->get_def() + 1 ); 
            stack->set_speed( stack->get_speed() + 1 );
            return;
      }

      switch ( get_terrain() ) // for magical terrains
      {
            case Terrain::Cursed_Ground : std::cerr << "TO DO : implement luck and morale bonuses ignore!" << std::endl; abort(); break;
            
            case Terrain::Holy_Ground : 
                  if     ( stack->get_faction() == Faction::Castle  || stack->get_faction() == Faction::Rampart    || stack->get_faction() == Faction::Tower   )
                        stack->add_morale(Morale::Good);
                  else if( stack->get_faction() == Faction::Inferno || stack->get_faction() == Faction::Necropolis || stack->get_faction() == Faction::Dungeon )
                        stack->add_morale(Morale::Bad);
                  break;
            
            case Terrain::Evil_Fog :
                  if     ( stack->get_faction() == Faction::Inferno || stack->get_faction() == Faction::Necropolis || stack->get_faction() == Faction::Dungeon )
                        stack->add_morale(Morale::Good);
                  else if( stack->get_faction() == Faction::Castle  || stack->get_faction() == Faction::Rampart    || stack->get_faction() == Faction::Tower   )
                        stack->add_morale(Morale::Bad);
                  break;
            
            case Terrain::Clover_Field : 
                  if( stack->get_faction() == Faction::Stronghold || stack->get_faction() == Faction::Fortress || stack->get_faction() == Faction::Conflux || stack->get_faction() == Faction::Cove )
                        stack->add_luck(Luck::Great);
                  break;
            
            case Terrain::Cracked_Ice : stack->set_def( std::max( stack->get_def() - 5, 0 ) ); break;
            
            case Terrain::Fields_of_Glory : stack->add_luck( Luck::Awful ); break;
      }
}

void Battle::position_armies()
{
      if( ARMY_SLOTS != 7 ) 
      { 
            std::cerr << "Positioning is made for 7 slots in a hero's army! If you'd like to use different number of slots you need to change the positioning and the battle map width and length." << std::endl;
            abort(); 
      }

      if( get_battle_format() == Battle_Format::Surrounded)
      {
            // TO DO : implement
      }
      else // Normal, Siege, Ships
      {
            // TO DO: implement Tactics and different gathered/scattered army setting
            for( uint8_t i = 0; i < ARMY_SLOTS; i++)
            {
                  uint8_t y_pos = 0;
                  if     ( i < 3  ) { y_pos = 2*i; }
                  else if( i == 3 ) { y_pos = (BATTLEFIELD_WIDTH - 1) / 2; }
                  else if( i > 3  ) { y_pos = 2*(i - 1); }

                  auto attacking_stack = get_attacker()->get_army_stack(i);
                  if( attacking_stack != nullptr )
                  {
                        if( attacking_stack->get_creature()->get_needs_2_hexes_in_battle() )
                        {
                              attacking_stack->set_position( 1, y_pos ); // attacker on the left
                              place_stack_on_battlefield(attacking_stack, *std::to_string(i + 1).c_str()); // represent each attacking stack by a number
                        }

                        attacking_stack->set_position( 0, y_pos ); // attacker on the left
                        place_stack_on_battlefield(attacking_stack, *std::to_string(i + 1).c_str()); // represent each attacking stack by a number
                  }

                  auto defending_stack = get_defender()->get_army_stack(i);
                  if( defending_stack != nullptr )
                  { 
                        if( defending_stack->get_creature()->get_needs_2_hexes_in_battle() )
                        {
                              defending_stack->set_position( BATTLEFIELD_LENGTH - 2, y_pos ); // defender on the right
                              place_stack_on_battlefield(defending_stack, *std::to_string(i + 1).c_str()); // represent each attacking stack by a number
                        }

                        defending_stack->set_position( BATTLEFIELD_LENGTH - 1, y_pos ); // defender on the right
                        place_stack_on_battlefield(defending_stack, *std::to_string(i + 1).c_str()); // represent each attacking stack by a number
                  }
            }
      }
}