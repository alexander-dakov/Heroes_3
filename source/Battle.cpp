#include "Battle.h"

Battle::Battle( Hero& attacker, Hero& defender, const Battle_Format format, const Terrain terrain ) : _attacker(attacker), _defender(defender), _format(format), _terrain(terrain)
{
      // First create and fill the battlefield.
      set_up_battlefield();

      // Give armies terrain bonuses.
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

      // After the battlefield is set and all initial bonuses are given accordingly, create the turn order.
      set_up_initial_turns();

      // Set the global moral and luck restrictions.
      set_global_moral_and_luck_debuffs();

      // All the preparations are done - time to start the battle
      { // formatted like this for ease of reading
            printf( "\nA battle between " );
            print_colored_string( _attacker.get_name().c_str(), _attacker.get_team() );
            printf( " and " );
            print_colored_string( _defender.get_name().c_str(), _defender.get_team() );
            printf( " has begun!\n" );
      }

      // Start the battle
      while( !check_battle_finished()  )
      {
            // Updates stacks' action, buffs/debuffs and reset the turn order accordingly.
            set_up_next_round();
            
            auto turns = get_turns();
            for( uint8_t i = 0; i < turns->size(); i++ )
            {
                  auto stack = get_stack_turn(i);

                  if( !get_wait_turns()->empty() )
                        set_up_wait_turns();
                  
                  print_turns();

                  printf("Current stack : ");
                  print_colored_string(stack->get_battlefield_symbol(), stack->get_team());
                  printf("\n");

                  on_stack_turn(stack);
            }

            auto wait_turns = get_wait_turns();
            if( !wait_turns->empty() )
                  for( uint8_t i = 0; i < wait_turns->size(); i++ )
                  {
                        auto stack = get_stack_wait_turn(i);

                        print_turns();
                        
                        printf("Current stack : ");
                        print_colored_string(stack->get_battlefield_symbol(), stack->get_team());
                        printf("\n");

                        on_stack_turn(stack);
                  }
      }
}

Battle::~Battle()
{     
      // Reset battle symbols of the stacks of the battle winner (whoever it is)
      for( uint8_t i = 0; i < ARMY_SLOTS; i++ )
      {
            if(get_attacker()->get_army_stack(i) != nullptr)
                  get_attacker()->get_army_stack(i)->reset_battlefield_symbol();
            
            if(get_defender()->get_army_stack(i) != nullptr)
                  get_defender()->get_army_stack(i)->reset_battlefield_symbol();
      }

      // Destroy the battlefield tile by tile
      for( uint8_t i = 0; i < BATTLEFIELD_WIDTH; i++ )
            for( uint8_t j = 0; j < BATTLEFIELD_LENGTH; j++ )
                  battlefield[i][j].~Battlefield_Tile();

      printf( "The battlefield was destroyed!\n" );

      printf( "The battle has ended!\n" );
}

Position Battle::enter_battlefield_coordinates()
{
      uint16_t x, y; // uint16_t instead of uint8_t, because otherwise it gets read as char (ascii code)

      while ( ( printf("\nx = ") ) && ( !( std::cin >> x ) || x < 0 || x > BATTLEFIELD_LENGTH - 1) )
      {
            printf("\nCoordinate 'x' must be in the range [0;%d]!", BATTLEFIELD_LENGTH - 1);
            std::cin.clear(); // clear bad input flag
            std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' ); // discard bad input
      }

      while ( ( printf("y = ") ) && ( !( std::cin >> y ) || y < 0 || y > BATTLEFIELD_WIDTH - 1 ) )
      {
            printf("\nCoordinate 'y' must be in the range [0;%d]!", BATTLEFIELD_WIDTH - 1);
            std::cin.clear(); // clear bad input flag
            std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' ); // discard bad input
      }

      return Position(x, y);
}

void Battle::check_valid_battlefield_pos(const uint8_t x, const uint8_t y)
{
      if( x >= BATTLEFIELD_LENGTH )
      {
            std::cerr << "Coordinate "<< x << " must be in the range [0;"<< BATTLEFIELD_LENGTH - 1 << "]!" << std::endl;
            abort();
      }

      if( y >= BATTLEFIELD_WIDTH )
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
                        attacking_stack->set_battlefield_symbol( *std::to_string(i + 1).c_str() );
                  
                        #if ENABLE_DOUBLE_TILE_STACKS == 1
                        if( attacking_stack->get_creature()->get_needs_2_tiles_in_battle() )
                        {
                              attacking_stack->set_position( 1, y_pos ); // attacker on the left
                              place_stack_on_battlefield( attacking_stack, attacking_stack->get_battlefield_symbol() ); // represent each attacking stack by a number
                        }
                        #endif

                        attacking_stack->set_position( 0, y_pos ); // attacker on the left
                        place_stack_on_battlefield( attacking_stack, attacking_stack->get_battlefield_symbol() ); // represent each attacking stack by a number
                  }

                  auto defending_stack = get_defender()->get_army_stack(i);
                  if( defending_stack != nullptr )
                  {
                        defending_stack->set_battlefield_symbol( *std::to_string(i + 1).c_str() );

                        #if ENABLE_DOUBLE_TILE_STACKS == 1
                        if( defending_stack->get_creature()->get_needs_2_tiles_in_battle() )
                        {
                              defending_stack->set_position( BATTLEFIELD_LENGTH - 2, y_pos ); // defender on the right
                              place_stack_on_battlefield( defending_stack, defending_stack->get_battlefield_symbol() ); // represent each attacking stack by a number
                        }
                        #endif

                        defending_stack->set_position( BATTLEFIELD_LENGTH - 1, y_pos ); // defender on the right
                        place_stack_on_battlefield( defending_stack, defending_stack->get_battlefield_symbol() ); // represent each attacking stack by a number
                  }
            }
      }
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

void Battle::print_battlefield(Stack* current_stack)
{
      printf("\n========================================");
      printf("\n________________________________________\n");
      printf(  "|                                      |\n");

      for( uint8_t i = 0; i < BATTLEFIELD_WIDTH; i++ )
      {
            printf("|    ");
            for( uint8_t j = 0; j < BATTLEFIELD_LENGTH; j++ )
            {
                  if( tile_is_reachable(j, i, current_stack) ) // ensure the tile is free and is within stack's reach
                              print_colored_string( battlefield[i][j].get_symbol(), current_stack->get_team() );
                  else
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

void Battle::apply_terrain_bonuses_to_stack(Stack* stack)
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

void Battle::set_up_next_round()
{
      _round += 1;

      for( uint8_t i = 0; i < get_turns()->size(); i++ )
            get_stack_turn(i)->new_turn();

      set_up_normal_turns();

      // Clear the wait turns
      get_wait_turns()->clear();

      printf("\n++++++++++++++++++++++++++++++++++++++++\n");
      printf("Round %d has started!\n", get_round());
}

void Battle::set_up_initial_turns()
{
      auto turns = get_turns();

      turns->clear();            // ensure an empty vector
      get_wait_turns()->clear(); // ensure an empty vector

      // Fill the vector of normal turns
      for( uint8_t i = 0; i < ARMY_SLOTS; i++ )
      {
            if( _attacker.get_army_stack(i) != nullptr )
                  turns->push_back( _attacker.get_army_stack(i) );
            if( _defender.get_army_stack(i) != nullptr )
                  turns->push_back( _defender.get_army_stack(i) );
      }

      set_up_normal_turns();
}

void Battle::set_up_normal_turns()
{
      auto turns = get_turns();

      // order the turns of the stacks according to their speed - from fast to slow, and if the speeds match, then the attcker gets to move first
      auto compare_speeds = [&](Stack* a, Stack* b){ return ( a->get_speed() > b->get_speed() ) + ( a->get_speed() == b->get_speed() )*( a->get_team() == get_attacker()->get_team() ); }; // lambda function to use in the sort
      std::sort( turns->begin(), turns->end(), compare_speeds );
}

void Battle::set_up_wait_turns()
{
      auto wait_turns = get_wait_turns();

      // order the turns of the stacks according to their speed - from slow to fast, and if the speeds match, then the defender gets to move first
      auto compare_speeds = [&](Stack* a, Stack* b){ return ( a->get_speed() < b->get_speed() ) + ( a->get_speed() == b->get_speed() )*( b->get_team() == get_defender()->get_team() ); }; // lambda function to use in the sort
      std::sort( wait_turns->begin(), wait_turns->end(), compare_speeds );
}

void Battle::print_turns()
{     
      auto turns = get_turns();
      if( !turns->empty() )
      {
            printf( "\nStack turns : ");
            for( uint8_t i = 0; i < turns->size(); i++ )
            {
                  auto stack = get_stack_turn(i);   
                  print_colored_string( stack->get_battlefield_symbol(), stack->get_team() );
                  printf( " -> ");
            }
      }

      auto wait_turns = get_wait_turns();
      if( !wait_turns->empty() )
      {
            printf( " Waiting stack turns : ");
            for( uint8_t i = 0; i < wait_turns->size(); i++ )
            {
                  auto stack = get_stack_wait_turn(i);   
                  print_colored_string( stack->get_battlefield_symbol(), stack->get_team() );
                  printf( " -> ");
            }
      }

      printf( "Round %d\n", get_round() + 1);
}


void Battle::on_stack_turn(Stack* stack, bool morale_rolled)
{
      // Check if stack is able to act = not perished / not blinded
      if( stack->get_action() == Stack_Action::Skip)
            return;

      // Roll for negative morale - to see if an action will be taken
      if( !morale_rolled )
            if( stack->roll_negative_morale() )    
            {
                  printf("\nStack ");
                  print_colored_string(stack->get_battlefield_symbol(), stack->get_team());
                  printf(" rolled negative morale and take no action this turn.\n");

                  stack->set_action(Stack_Action::Skip);
                  return;
            }

      // Print the battlefield with the movement for the current stack after it rolls a good enough morale to act.
      print_battlefield(stack);

      std::string action = select_action_for_stack( stack->get_action() != Stack_Action::Wait );

      if(action == "M")
      {
            printf("\nEnter coordinates to desired location :");
            // uint16_t x, y; // uint16_t instead of uint8_t, because otherwise it gets read as char (ascii code)

            Position pos = enter_battlefield_coordinates();
            uint8_t x = pos.x;
            uint8_t y = pos.y;

            while( !tile_is_reachable(x, y, stack) )
            {

                  if( std::abs(x - stack->get_position().x) + std::abs(y - stack->get_position().y) > stack->get_speed() )
                        printf("\nStack does not have enough speed to reach the tile at [%d;%d]! Select a tile within stack's reach :", x, y);
                  else // = else if( !battlefield[y][x].is_reachable() )
                  {
                        printf("\nTile at [%d;%d] is already taken by ", x, y);
                        print_colored_string(battlefield[y][x].get_symbol(), battlefield[y][x].get_team());
                  }
                  printf("\n");
                  
                  pos = enter_battlefield_coordinates();
                  x = pos.x;
                  y = pos.y;
            }

            move_stack(stack, x, y);
      }
      else if(action == "A") 
      {
            printf("\nEnter the symbol of the stack to be attacked : \n");
            std::string symbol;
            std::cin >> symbol;

            Stack* enemy_stack = nullptr;

            while(true)
            {
                  enemy_stack = find_existing_enemy_stack_via_symbol( &symbol[0], stack->get_team() );

                  while( symbol.size() > 1 || enemy_stack == nullptr )
                  {
                        printf("\nInvalid input! Enter the symbol of the stack to be attacked : \n");
                        std::cin >> symbol;

                        enemy_stack = find_existing_enemy_stack_via_symbol( &symbol[0], stack->get_team() );
                  }
                  printf("\n");

                  if( !stack_can_shoot(stack, enemy_stack) ) // needs to be checked every time because of 'Force Field'
                        if( !enemy_is_reachable(stack, enemy_stack) )
                        {
                              printf("This enemy stack is not reachable. Please select a different enemy. Symbol = \n");
                              std::cin >> symbol;
                        }
                        else
                              break;
            }   

            attack_stack( stack, enemy_stack );
      }
      else if(action == "D")
            stack->defend();
      else if(action == "W")
      {
            stack->wait();
            get_wait_turns()->push_back(stack);
      }

      // Roll for positive morale - to act again
      if( !morale_rolled )
            if( !get_spirit_of_oppression_present() )
                  if( stack->roll_positive_morale() )
                  {
                        printf("\nStack ");
                        print_colored_string(stack->get_battlefield_symbol(), stack->get_team());
                        printf(" rolled positive morale and takes a second action during this turn.\n");

                        on_stack_turn( stack, true );
                  }
}

std::string Battle::select_action_for_stack(const bool stack_can_wait)
{
      std::string action;

      if( stack_can_wait ) // first time stack can act during this turn
      {
            // Select an action for the stack - Move / Attack / Defend / Wait
            printf("\nOrder an action to the stack : M (move) / A (attack) / D (defend) / W (wait)\n Action : ");

            std::cin >> action;

            // TO DO : add restrictions to stack actions when rooted or when stack suffers from Forgetfulness

            while( action.size() > 1 || ( action != "M" && action != "A" && action != "D" && action != "W" ) )
            {
                  printf("\n'%s' is an invalid input! Choose one of the options : M / A / D / W\nAction : ", action.c_str());
                  std::cin >> action;
            }
      }
      else // stack already waited in this round so, now it should act
      {
            // Select an action for the stack - Move / Attack / Defend
            printf("\nOrder an action to the stack : M (move) / A (attack) / D (defend)\n Action : ");

            std::cin >> action;

            // TO DO : add restrictions to stack actions when rooted or when stack suffers from Forgetfulness

            while( action.size() > 1 || ( action != "M" && action != "A" && action != "D" ) )
            {
                  printf("\n'%s' is an invalid input! Choose one of the options : M / A / D\nAction : ", action.c_str());
                  std::cin >> action;
            }
      }

      return action;
}

void Battle::set_global_moral_and_luck_debuffs()
{
      Slot slot = Slot::Pocket;
      std::string item_1 = "Spirit of Oppression";
      std::string item_2 = "Hourglass of the Evil Hour";

      _spirit_of_oppression_present   = get_attacker()->check_eqipped_item(item_1, slot) + get_defender()->check_eqipped_item(item_1, slot);
      _hourglass_of_evil_hour_present = get_attacker()->check_eqipped_item(item_2, slot) + get_defender()->check_eqipped_item(item_2, slot);
}

bool Battle::tile_is_reachable(const uint8_t x, const uint8_t y, Stack* stack)
{
      return battlefield[y][x].is_reachable() && ( std::abs(x - stack->get_position().x) + std::abs(y - stack->get_position().y) <= stack->get_speed() && true );
}

bool Battle::enemy_is_reachable(Stack* stack, Stack* enemy_stack)
{
      // Search for locations from which to attack the defending stack
      uint8_t ex = enemy_stack->get_position().x;
      uint8_t ey = enemy_stack->get_position().y;

      for( int8_t i = std::max(0, ey - 1); i <= std::min(BATTLEFIELD_WIDTH - 1, ey + 1); i++ )
            for( int8_t j = std::max(0, ex - 1); j <= std::min(BATTLEFIELD_LENGTH - 1, ex + 1); j++ )
                  if( tile_is_reachable(j, i, stack) )
                        return true;
      
      return false;
}


Position* Battle::select_location_around_enemy_stack(Stack* stack, Stack* enemy_stack)
{
      // Search for locations from which to attack the defending stack
      uint8_t ex = enemy_stack->get_position().x;
      uint8_t ey = enemy_stack->get_position().y;

      std::map< uint8_t, std::unique_ptr<Position> > positions;
      uint8_t counter = 0;

      for( int8_t i = std::max(0, ey - 1); i <= std::min(BATTLEFIELD_WIDTH - 1, ey + 1); i++ )
            for( int8_t j = std::max(0, ex - 1); j <= std::min(BATTLEFIELD_LENGTH - 1, ex + 1); j++ )
                  if( tile_is_reachable(j, i, stack) )
                  {
                        counter++;
                        positions[counter] = std::unique_ptr<Position>(new Position(j, i));
                  }

      if( positions.size() > 1 )
      {
            printf("Possible locations to attack from :\n");
            for( auto & p : positions)
                  printf("Location %d = [%d;%d]\n", p.first, p.second->x, p.second->y);

            printf("Select a locations to attack from. Location = ");

            uint16_t location = 0;
            std::cin >> location;
            while( location < 0 || location > counter )
            {
                  printf("\nLocation = ");
                  std::cin >> location;
            }
            printf("\n");
            
            return positions[location].get();
      }
      else // if no other positions are available
            return positions[0].get();
}

Stack* Battle::find_existing_enemy_stack_via_symbol(const char* ch, const Team team)
{
      for( uint8_t i = 0; i < get_turns()->size(); i++ )
            if( get_stack_turn(i)->get_team() != team ) // search only through the enemy team stacks
                  if( !get_stack_turn(i)->get_has_perished() ) // search only through existing stacks
                        if( get_stack_turn(i)->get_battlefield_symbol() == *ch)
                              return get_stack_turn(i);
      
      return nullptr;
}

bool Battle::has_adjacent_enemy(Stack* stack)
{
      for( uint8_t i = 0; i < get_turns()->size(); i++)
      {
            auto enemy_stack = get_stack_turn(i);

            if( enemy_stack->get_team() != stack->get_team() && !enemy_stack->get_has_perished() )
                  if( stacks_are_adjacent(stack, enemy_stack) )
                        return true;
      }

      return false;
}

bool Battle::stacks_are_adjacent(Stack* stack, Stack* enemy_stack)
{
      return ( std::abs(stack->get_position().x - enemy_stack->get_position().x) <= 1 ) && ( std::abs(stack->get_position().y - enemy_stack->get_position().y) <= 1 );
}

void Battle::move_stack(Stack* stack, const uint8_t x, const uint8_t y)
{
      Position pos = stack->get_position(); // get current position

      battlefield[pos.y][pos.x].reset_tile(); // set the tile of the current position of the stack to 'Normal'
      #if ENABLE_DOUBLE_TILE_STACKS == 1
      if( stack->get_team() == get_attacker()->get_team() )
            battlefield[pos.y][pos.x + 1].reset_tile(); // set the tile of the current position of the stack to 'Normal'
      else
            battlefield[pos.y][pos.x - 1].reset_tile(); // set the tile of the current position of the stack to 'Normal'
      #endif

      stack->move(x, y); // try to move the stack to the desired location

      pos = stack->get_position(); // get the new location - might be different from desired if the stack stumbled upon a quicksand

      battlefield[pos.y][pos.x].setup_tile( Tile::Army, stack->get_team(), stack->get_battlefield_symbol() );
      #if ENABLE_DOUBLE_TILE_STACKS == 1
      if( stack->get_team() == get_attacker()->get_team() )
            battlefield[pos.y][pos.x + 1].setup_tile( Tile::Army, stack->get_team(), stack->get_battlefield_symbol() );
      else
            battlefield[pos.y][pos.x - 1].setup_tile( Tile::Army, stack->get_team(), stack->get_battlefield_symbol() );
      #endif
}

void Battle::attack_stack(Stack* attacking_stack, Stack* defending_stack)
{
      // Lets check the potential bonuses to the attack, that come from the army itself
      bool attacker_has_leprechaun = false; // this is done every time as Leprechauns bring bonus only while they are alive on the battlefield
      bool defender_has_leprechaun = false; // this is done every time as Leprechauns bring bonus only while they are alive on the battlefield
      for( uint8_t i = 0; i < get_turns()->size(); i++ )
            if( get_stack_turn(i)->get_creature_name() == "Leprechaun" )
            {
                  attacker_has_leprechaun += get_stack_turn(i)->get_team() == get_attacker()->get_team();
                  defender_has_leprechaun += get_stack_turn(i)->get_team() == get_defender()->get_team();
            }
      
      bool can_shoot = stack_can_shoot(attacking_stack, defending_stack);

      if( stacks_are_adjacent(attacking_stack, defending_stack) ) // if the enemy is adjacent, the stack will always be able to attack it, so only repositioning matters
      {
            printf("\nWould you like to reposition the stack? (Y/N)\n");
            printf("Answer : ");
            char answer;
            std::cin >> answer;

            while( answer != 'Y' && answer != 'N' )
            {
                  printf("\n'%c' is an invalid input! Choose one of the options : Y / N\nAnswer : ", answer);
                  std::cin >> answer;
            }
            printf("\n");

            if( answer == 'N' )
                  attacking_stack->attack( defending_stack, can_shoot, false, false, get_hourglass_of_evil_hour_present(), attacker_has_leprechaun, defender_has_leprechaun );
            else
            {
                  Position* pos = select_location_around_enemy_stack(attacking_stack, defending_stack);
                  move_stack(attacking_stack, pos->x, pos->y);
                  
                  attacking_stack->attack( defending_stack, can_shoot, false, false, get_hourglass_of_evil_hour_present(), attacker_has_leprechaun, defender_has_leprechaun );
            }
      }
      else
      {
            if( can_shoot )
                  attacking_stack->attack( defending_stack, can_shoot, false, false, get_hourglass_of_evil_hour_present(), attacker_has_leprechaun, defender_has_leprechaun );
            else
            {
                  Position* pos = select_location_around_enemy_stack(attacking_stack, defending_stack);
                  move_stack(attacking_stack, pos->x, pos->y);
                  
                  attacking_stack->attack( defending_stack, can_shoot, false, false, get_hourglass_of_evil_hour_present(), attacker_has_leprechaun, defender_has_leprechaun );
            }
      }
}

bool Battle::stack_can_shoot(Stack* attacking_stack, Stack* defending_stack)
{
      // TO DO : add 'Force Field'
      if( attacking_stack->get_creature()->get_is_ranged() && attacking_stack->get_shots_left() && true ) // is a shooter with enough ammo
      {
            if( stacks_are_adjacent(attacking_stack, defending_stack) )
                  return attacking_stack->get_creature()->get_no_melee_penalty();
            if( has_adjacent_enemy(attacking_stack) )
                  return false;
            return true;
      }
      
      return false;
}

bool Battle::check_battle_finished()
{
      // First, check to see if any of the armies has perished
      auto turns = get_turns();
      if( turns->size() > 1 ) // at least one stack
      {
            bool has_attacker_stack = false; // shows if there is at least one attacker stack on the battlefield 
            bool has_defender_stack = false; // shows if there is at least one defender stack on the battlefield
            
            for( uint8_t i = 0; i < turns->size(); i++ )
            {
                  if     ( turns->at(i)->get_team() == _attacker.get_team() ) { has_attacker_stack = true; }
                  else if( turns->at(i)->get_team() == _defender.get_team() ) { has_defender_stack = true; }
                  
                  if( (has_attacker_stack && has_defender_stack) && true == true ) // returns false on the first indication of two seperate teams on the battlefield
                        return false;
            }
            
            if( has_attacker_stack != has_defender_stack ) 
                  return true;
      }
      else
            return true;
      
      return false; // cannot be reached, but placed against compiler warnings
}