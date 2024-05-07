#include "Battle.h"

Battle::Battle( Hero& attacker, Hero& defender, const Battle_Format format, const Terrain terrain ) : _attacker(attacker), _defender(defender), _format(format), _terrain(terrain)
{
      if( get_attacker()->get_team() == get_defender()->get_team() )
      {
            std::cerr << "Two heroes of the same team cannot go to war with each other!" << std::endl;
            abort();
      }

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

      // Set the global moral and luck buffs and debuffs.
      set_global_buffs_and_debuffs();

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
            
            // Iterate through the stacks in the normal turn
            for( uint8_t i = 0; i < get_turns()->size(); i++ )
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
            
            // Iterate through stacks which decided to wait
            auto const wait_turns = get_wait_turns();
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
      // Reverse the reduction of power skill
      auto attacker = get_attacker();
      auto defender = get_defender();
      
      attacker->add_power( ( attacker->get_power() * defender->get_reduce_enemy_power_skill() ) / 100 );
      defender->add_power( ( defender->get_power() * attacker->get_reduce_enemy_power_skill() ) / 100 );

      // Reverse the reduction of morale and luck
      // TO DO : do it only for the winner
      attacker->add_morale( defender->get_reduce_enemy_morale() );
      attacker->add_luck( defender->get_reduce_enemy_luck() );
      attacker->update_army_stats();

      defender->add_morale( attacker->get_reduce_enemy_morale() );
      defender->add_luck( attacker->get_reduce_enemy_luck() );
      defender->update_army_stats();

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

bool Battle::get_has_angel_ally(Stack* const stack)
{
      if( get_angel_present() )
            for( uint8_t i = 0; i < get_turns()->size(); i++ )
            {
                  auto const s = get_stack_turn(i);
                  if( s->get_team() == stack->get_team() && !s->get_has_perished() )
                        if( s->get_creature()->get_increases_alias_morale_1() ) // Angel & Archangel
                              return true;
            }

      return false;
}

bool Battle::get_has_necro_dragon_enemy(Stack* const stack)
{
      if( get_necro_dragon_present() )
            for( uint8_t i = 0; i < get_turns()->size(); i++ )
            {
                  auto const s = get_stack_turn(i);
                  if( s->get_team() != stack->get_team() && !s->get_has_perished() )
                        if( s->get_creature()->get_decreases_enemy_morale_1() ) // Bone Dragon & Ghost Dragon
                              return true;
            }

      return false;
}

bool Battle::get_has_devil_enemy(Stack* const stack)
{
      if( get_devil_present() )
            for( uint8_t i = 0; i < get_turns()->size(); i++ )
            {
                  auto const s = get_stack_turn(i);
                  if( s->get_team() != stack->get_team() && !s->get_has_perished() )
                        if( s->get_creature()->get_decreases_enemy_luck_1() ) // Devil
                              return true;
            }
      return false;
}

bool Battle::get_has_archdevil_enemy(Stack* const stack)
{
      if( get_archdevil_present() )
            for( uint8_t i = 0; i < get_turns()->size(); i++ )
            {
                  auto const s = get_stack_turn(i);
                  if( s->get_team() != stack->get_team() && !s->get_has_perished() )
                        if( s->get_creature()->get_decreases_enemy_luck_2() ) // Archdevil
                              return true;
            }

      return false;
}

bool Battle::get_has_leprechaun_ally(Stack* const stack)
{
      if( get_leprechaun_present() )
            for( uint8_t i = 0; i < get_turns()->size(); i++ )
                  if( get_stack_turn(i)->get_creature()->get_doubles_luck_chance() && get_stack_turn(i)->get_team() == stack->get_team() )
                        return true;

      return false;
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

void Battle::print_battlefield(Stack* const current_stack)
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
            auto const attacking_stack = get_attacker()->get_army_stack(i);
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
            auto const defending_stack = get_defender()->get_army_stack(i);
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
            
            case Terrain::Fields_of_Glory : stack->add_luck(Luck::Awful); break;
      }
}

void Battle::set_up_next_round()
{
      _round += 1;

      new_turn();

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
      auto const turns = get_turns();
      if( !turns->empty() )
      {
            printf( "\nStack turns : ");
            for( uint8_t i = 0; i < turns->size(); i++ )
            {
                  auto const stack = get_stack_turn(i);   
                  print_colored_string( stack->get_battlefield_symbol(), stack->get_team() );
                  printf( " -> ");
            }
      }

      auto const wait_turns = get_wait_turns();
      if( !wait_turns->empty() )
      {
            printf( " Waiting stack turns : ");
            for( uint8_t i = 0; i < wait_turns->size(); i++ )
            {
                  auto const stack = get_stack_wait_turn(i);   
                  print_colored_string( stack->get_battlefield_symbol(), stack->get_team() );
                  printf( " -> ");
            }
      }

      printf( "Round %d\n", get_round() + 1);
}

void Battle::new_turn()
{
      for( uint8_t i = 0; i < get_turns()->size(); i++ )
      {
            Stack* stack = get_stack_turn(i);

            if( stack->get_has_perished() )
            {
                  stack->set_action(Stack_Action::Skip);
                  return;
            }

            if( true ) // if stack is not blinded its status should be returned to the default value (Attack)
                  stack->set_action(Stack_Action::Attack); // default value for normal turns
            else
                  stack->set_action(Stack_Action::Skip);

            // reduce the duration of spells acting on the stack
      }
}


void Battle::on_stack_turn(Stack* stack, bool morale_rolled)
{
      // Check if stack is able to act = not perished / not blinded
      if( stack->get_action() == Stack_Action::Skip)
            return;

      // Roll for negative morale - to see if an action will be taken
      if( !morale_rolled )
            if( roll_negative_morale(stack) )    
            {
                  printf("\nStack ");
                  print_colored_string(stack->get_battlefield_symbol(), stack->get_team());
                  printf(" rolled negative morale and takes no action this turn.\n");

                  stack->set_action(Stack_Action::Skip);
                  return;
            }

      // Print the battlefield with the movement for the current stack after it rolls a good enough morale to act.
      print_battlefield(stack);

      // TO DO : if( 'Berserk' ) - find the closest REACHABLE (walls may be in the way) stack and attack it
      // else - code below

      const std::string action = select_action_for_stack( stack->get_action() != Stack_Action::Wait );

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
            if( (stack->get_creature()->get_has_fireball_attack() || stack->get_creature()->get_has_cloud_attack()) && stack_can_shoot(stack) ) // Magogs and Power Liches can shoot at positions
            {
                  printf("\nDo you wish the stack to target another stack (S) or a position on the battlefield (P) %s : (S/P)\n");
                  std::string target;
                  std::cin >> target;

                  while( action.size() > 1 || ( target != "S" && target != "P" ) )
                  {
                        printf("\n'%s' is an invalid input! Choose one of the options : S / P\nTarget : ", target.c_str());
                        std::cin >> target;
                  }

                  if( target == "P")
                  {
                        Position pos = enter_battlefield_coordinates();
                        auto const adjacent_stacks = adjacent_stacks_to_pos(pos); // intentionally gives the ability to attack its own position
                        
                        for( auto a : adjacent_stacks )
                              inflict_damage(stack, a, false);

                        return;
                  }
            }

            printf("\nEnter the symbol of the stack to be attacked : ");
            std::string symbol;
            std::cin >> symbol;

            Stack* enemy_stack = nullptr;

            while(true)
            {
                  enemy_stack = find_existing_enemy_stack_via_symbol( symbol[0], stack->get_team() );

                  while( symbol.size() > 1 || enemy_stack == nullptr )
                  {
                        printf("\nInvalid input! Enter the symbol of the stack to be attacked : ");
                        std::cin >> symbol;

                        enemy_stack = find_existing_enemy_stack_via_symbol( symbol[0], stack->get_team() );
                  }
                  printf("\n");

                  if( !stack_can_shoot(stack, enemy_stack) ) // needs to be checked every time because of 'Force Field'
                  {
                        if( !enemy_is_reachable(stack, enemy_stack) )
                        {
                              printf("This enemy stack is not reachable. Please select a different enemy. Symbol = ");
                              std::cin >> symbol;
                              printf("\n");

                        }
                        else
                              break;
                  }
                  else
                        break;
            }   

            attack_stack( stack, enemy_stack );
      }
      else if(action == "D")
            defend_stack(stack);
      else if(action == "W")
            wait_stack(stack);

      // Roll for positive morale - to act again
      if( stack->get_action() != Stack_Action::Defend && !morale_rolled )
            if( !get_spirit_of_oppression_present() )
                  if( roll_positive_morale(stack) )
                  {
                        printf("\nStack ");
                        print_colored_string(stack->get_battlefield_symbol(), stack->get_team());
                        printf(" rolled positive morale and takes a second action during this turn.\n");

                        on_stack_turn( stack, true );
                  }
}

bool Battle::roll_negative_morale(Stack* const stack)
{
      uint16_t probability = 0;

      const Morale morale = static_cast<Morale>( static_cast<int8_t>(stack->get_morale()) + 1*get_has_angel_ally(stack) + (-1)*get_has_necro_dragon_enemy(stack) ); // should be done every time

      switch(morale)
      {
            case Morale::Terrible : probability = 250; break;
            case Morale::Awful    : probability = 167; break;
            case Morale::Bad      : probability =  83; break;
            case Morale::Neutral  : probability =   0; break; // written because of compiler warnings (I prefer not to silence them as errors might be missed)
            case Morale::Good     : probability =   0; break; // written because of compiler warnings (I prefer not to silence them as errors might be missed)
            case Morale::Great    : probability =   0; break; // written because of compiler warnings (I prefer not to silence them as errors might be missed)
            case Morale::Superb   : probability =   0; break; // written because of compiler warnings (I prefer not to silence them as errors might be missed)
      }
      return rand() % 1000 < probability; // intentionaly not used with 'new', so battles can be replayed with the same rolls
}

bool Battle::roll_positive_morale(Stack* const stack)
{
      uint16_t probability = 0;

      const Morale morale = static_cast<Morale>( static_cast<int8_t>(stack->get_morale()) + 1*get_has_angel_ally(stack) + (-1)*get_has_necro_dragon_enemy(stack) ); // should be done every time

      switch(morale)
      {
            case Morale::Terrible : probability =   0; break; // written because of compiler warnings (I prefer not to silence them as errors might be missed)
            case Morale::Awful    : probability =   0; break; // written because of compiler warnings (I prefer not to silence them as errors might be missed)
            case Morale::Bad      : probability =   0; break; // written because of compiler warnings (I prefer not to silence them as errors might be missed)
            case Morale::Neutral  : probability =   0; break; // written because of compiler warnings (I prefer not to silence them as errors might be missed)
            case Morale::Good     : probability =  42; break;
            case Morale::Great    : probability =  83; break;
            case Morale::Superb   : probability = 125; break;
      }
      return rand() % 1000 < probability; // intentionaly not used with 'new', so battles can be replayed with the same rolls
}

int8_t Battle::roll_luck(Stack* const stack)
{
      // Leprechauns double the luck chance.
      // Item 'Hourglass of the Evil Hour' negates all positive luck effects.
      uint16_t probability;
      int8_t sign;

      const Luck luck = static_cast<Luck>( static_cast<int8_t>(stack->get_luck()) + std::min( (-1)*get_has_devil_enemy(stack), (-2)*get_has_archdevil_enemy(stack) ) ); // should be done every time

      const bool leprechauns_in_army = get_has_leprechaun_ally(stack);

      switch(luck)
      {
            case Luck::Terrible : probability = 250*(1 + leprechauns_in_army); sign = -1; break;
            case Luck::Awful    : probability = 167*(1 + leprechauns_in_army); sign = -1; break;
            case Luck::Bad      : probability =  83*(1 + leprechauns_in_army); sign = -1; break;
            case Luck::Neutral  : probability =   0*(1 + leprechauns_in_army); sign =  0; break;
            case Luck::Good     : probability =  42*(1 + leprechauns_in_army); sign =  1; break;
            case Luck::Great    : probability =  83*(1 + leprechauns_in_army); sign =  1; break;
            case Luck::Superb   : probability = 125*(1 + leprechauns_in_army); sign =  1; break;
      }
      return sign*(rand() % 1000 < probability); // intentionaly not used with 'new', so battles can be replayed with the same rolls
}

std::string Battle::select_action_for_stack(const bool stack_can_wait)
{
      std::string action;

      if( stack_can_wait ) // first time stack can act during this turn
      {
            // Select an action for the stack - Move / Attack / Defend / Wait
            printf("\nOrder an action to the stack : M (move) / A (attack) / D (defend) / W (wait)\nAction : ");

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
            printf("\nOrder an action to the stack : M (move) / A (attack) / D (defend)\nAction : ");

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

void Battle::set_global_buffs_and_debuffs()
{
      // Update Battle's private fields responsible for global debuffs
      const Slot slot = Slot::Pocket;
      const std::string item_1 = "Spirit of Oppression";
      const std::string item_2 = "Hourglass of the Evil Hour";

      _spirit_of_oppression_present   = get_attacker()->check_eqipped_item(item_1, slot) + get_defender()->check_eqipped_item(item_1, slot);
      _hourglass_of_evil_hour_present = get_attacker()->check_eqipped_item(item_2, slot) + get_defender()->check_eqipped_item(item_2, slot);

      // Update hero's power skills according to enemy's items reducing enemy power skill
      auto attacker = get_attacker();
      auto defender = get_defender();

      attacker->add_power( -( attacker->get_power() * defender->get_reduce_enemy_power_skill() ) / 100 );
      defender->add_power( -( defender->get_power() * attacker->get_reduce_enemy_power_skill() ) / 100 );
      
      // Update armies according to hero's items reducing enemy's morale/luck
      attacker->add_morale( -defender->get_reduce_enemy_morale() );
      attacker->add_luck( -defender->get_reduce_enemy_luck() );
      attacker->update_army_stats();

      defender->add_morale( -attacker->get_reduce_enemy_morale() );
      defender->add_luck( -attacker->get_reduce_enemy_luck() );
      defender->update_army_stats();

      // TO DO : check for items which affect enemy's Power Skill

      // Set up conditions for bonuses according to creatures' special abilities
      std::array<Hero*, 2> heroes = { attacker, defender };
      for( auto hero : heroes)
            for( uint8_t i = 0; i < ARMY_SLOTS; i++ )
            {
                  auto const c = hero->get_army_stack(i)->get_creature();

                  _angel_present        += c->get_increases_alias_morale_1();
                  _necro_dragon_present += c->get_decreases_enemy_morale_1();
                  _devil_present        += c->get_decreases_enemy_luck_1();
                  _archdevil_present    += c->get_decreases_enemy_luck_2();
                  _leprechaun_present   += c->get_doubles_luck_chance();
            }
}

bool Battle::tile_is_reachable(const uint8_t x, const uint8_t y, Stack* const stack)
{
      return battlefield[y][x].is_reachable() && ( std::abs(x - stack->get_position().x) + std::abs(y - stack->get_position().y) <= stack->get_speed() );
}

bool Battle::enemy_is_reachable(Stack* const stack, Stack* const enemy_stack)
{
      // Search for locations from which to attack the defending stack
      const uint8_t ex = enemy_stack->get_position().x;
      const uint8_t ey = enemy_stack->get_position().y;

      for( int8_t i = std::max(0, ey - 1); i <= std::min(BATTLEFIELD_WIDTH - 1, ey + 1); i++ )
            for( int8_t j = std::max(0, ex - 1); j <= std::min(BATTLEFIELD_LENGTH - 1, ex + 1); j++ )
                  if( tile_is_reachable(j, i, stack) )
                        return true;
      
      return false;
}

uint8_t Battle::get_distance_between_stacks(Stack* const stack, Stack* const enemy_stack)
{
      return std::abs(stack->get_position().x - enemy_stack->get_position().x) + std::abs(stack->get_position().y - enemy_stack->get_position().y);
}

Position* Battle::select_location_around_enemy_stack(Stack* const stack, Stack* const enemy_stack)
{
      // Search for locations from which to attack the defending stack
      const uint8_t ex = enemy_stack->get_position().x;
      const uint8_t ey = enemy_stack->get_position().y;

      std::map< uint8_t, std::unique_ptr<Position> > positions;
      uint8_t counter = 1;

      for( int8_t i = std::max(0, ey - 1); i <= std::min(BATTLEFIELD_WIDTH - 1, ey + 1); i++ )
            for( int8_t j = std::max(0, ex - 1); j <= std::min(BATTLEFIELD_LENGTH - 1, ex + 1); j++ )
                  if( tile_is_reachable(j, i, stack) )
                  {
                        positions[counter] = std::unique_ptr<Position>(new Position(j, i));
                        counter++;
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
            return positions[1].get(); // counter starts from 1
}

Stack* Battle::find_existing_enemy_stack_via_symbol(const char ch, const Team team)
{
      for( uint8_t i = 0; i < get_turns()->size(); i++ )
            if( get_stack_turn(i)->get_team() != team ) // search only through the enemy team stacks
                  if( !get_stack_turn(i)->get_has_perished() ) // search only through existing stacks
                        if( get_stack_turn(i)->get_battlefield_symbol() == ch)
                              return get_stack_turn(i);
      
      return nullptr;
}

Stack* Battle::find_existing_stack_via_position(const Position pos)
{
      for( uint8_t i = 0; i < get_turns()->size(); i++ )
      {
            auto const stack = get_stack_turn(i);
            if( !stack->get_has_perished() ) // search only through existing stacks
                  if( stack->get_position() == pos )
                        return stack;
      }
      
      return nullptr;
}

bool Battle::has_adjacent_enemy(Stack* const stack)
{
      for( uint8_t i = 0; i < get_turns()->size(); i++)
      {
            auto const enemy_stack = get_stack_turn(i);

            if( enemy_stack->get_team() != stack->get_team() && !enemy_stack->get_has_perished() )
                  if( stacks_are_adjacent(stack, enemy_stack) )
                        return true;
      }

      return false;
}

std::vector<Stack*> Battle::adjacent_stacks(Stack* const stack)
{
      return adjacent_stacks_to_pos( stack->get_position(), false );
}

std::vector<Stack*> Battle::adjacent_stacks_to_pos(Position pos, bool include_position)
{
      std::vector<Stack*> adjacents;

      for( uint8_t i = 0; i < get_turns()->size(); i++)
      {
            auto const enemy_stack = get_stack_turn(i);

            if( !enemy_stack->get_has_perished() )
                  if( stack_is_adjacent_to_pos(pos, enemy_stack, include_position) )
                  {
                  #ifdef ENABLE_DOUBLE_TILE_STACKS
                        for( auto a : adjacents )
                              if( a == enemy_stack )
                                    break;
                  #endif
                        adjacents.push_back(enemy_stack);
                  }
      }

      return adjacents;
}

bool Battle::stacks_are_adjacent(Stack* const stack, Stack* const enemy_stack)
{
      return stack_is_adjacent_to_pos(stack->get_position(), enemy_stack, false);
}

bool Battle::stack_is_adjacent_to_pos(Position pos, Stack* const enemy_stack, bool include_position)
{
      const uint8_t ex = enemy_stack->get_position().x;
      const uint8_t ey = enemy_stack->get_position().y;
      
      if( pos.x == ex && pos.y == ey )
            return include_position;

      return ( std::abs(pos.x - ex) <= 1 ) && ( std::abs(pos.y - ey) <= 1 );
}

void Battle::move_stack(Stack* stack, const uint8_t x, const uint8_t y)
{
      stack->set_action(Stack_Action::Attack);

      Position pos = stack->get_position(); // get current position

      battlefield[pos.y][pos.x].reset_tile(); // set the tile of the current position of the stack to 'Normal'
      #if ENABLE_DOUBLE_TILE_STACKS == 1
      if( stack->get_team() == get_attacker()->get_team() )
            battlefield[pos.y][pos.x + 1].reset_tile(); // set the tile of the current position of the stack to 'Normal'
      else
            battlefield[pos.y][pos.x - 1].reset_tile(); // set the tile of the current position of the stack to 'Normal'
      #endif

      if( stack->get_creature()->get_is_flying() ) // true for both flying and teleporting creatures
            stack->set_position(x, y);
      else
      {
            // TO DO : implement walking through every tile on the battle field for on-tile effects - quicksand and siege wall bombs, rivers, spikes, etc.
            uint8_t distance = std::abs(x - pos.x) + std::abs(y - pos.y);
            uint8_t distance_traveled = 0;
            uint8_t current_x = x; // this should be = pos.x and suffer changes step by step
            uint8_t current_y = y; // this should be = pos.y and suffer changes step by step
            
            while( distance )
            {  
                  // TO DO : implement movement patterns - current_x and current_y change step by step according to the patterns
                  if( battlefield[current_y][current_x].get_tile() != Tile::Quicksand ) // TO DO : implement team immunity to quicksands
                  {
                        distance_traveled++;
                        distance--;
                  }
                  else
                        break;
            }

            stack->set_distance_traveled( distance_traveled*( stack->get_creature()->get_has_jousting() ) );
            stack->set_position(current_x, current_y); // this acts like flying / teleporting and it should not
      }


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

            if( answer == 'Y' )
            {
                  Position* pos = select_location_around_enemy_stack(attacking_stack, defending_stack);
                  move_stack(attacking_stack, pos->x, pos->y);
            }
      }
      else
            if( !stack_can_shoot(attacking_stack, defending_stack) )
            {
                  Position* pos = select_location_around_enemy_stack(attacking_stack, defending_stack);
                  move_stack(attacking_stack, pos->x, pos->y);
            }
      
      target_and_inflict_damage(attacking_stack, defending_stack);
}

void Battle::defend_stack(Stack* stack)
{ 
      stack->set_action(Stack_Action::Defend); 
}

void Battle::wait_stack(Stack* stack)
{ 
      stack->set_action(Stack_Action::Wait); 
      get_wait_turns()->push_back(stack); 
}

void Battle::target_and_inflict_damage(Stack* attacking_stack, Stack* defending_stack, bool const attack_is_retaliation)
{
      auto const c = attacking_stack->get_creature();

      if( c->get_has_attack_adjacent_hexes() || c->get_has_attack_adjacent_enemies() )
      {
            auto const stacks = adjacent_stacks(attacking_stack);
            for( auto s : stacks )
                  inflict_damage(attacking_stack, s, s == defending_stack, attack_is_retaliation); // if attacking_stack can attack only enemies and is not under the influence of 'Berserk' inflict_damage() will be exited
      }
      else if( c->get_has_3_headed_attack() )
      {
            // A slower approach
            // auto const stacks = adjacent_stacks(attacking_stack);
            // for( auto s : stacks )
            //       if( stack_is_adjacent_to_pos(defending_stack->get_position(), s, true) ) // found stacks are enemy
            //             inflict_damage(attacking_stack, s, s == defending_stack, attack_is_retaliation);

            // A faster approach
            // Coordinates of the attacking stack
            const uint8_t ax = attacking_stack->get_position().x;
            const uint8_t ay = attacking_stack->get_position().y;
            
            // Coordinates of the defending stack
            const uint8_t dx = defending_stack->get_position().x;
            const uint8_t dy = defending_stack->get_position().y;

            if( ax == dx ) // horizontally aligned
            {
                  for( int8_t i = std::max(0, dy - 1); i <= std::min(BATTLEFIELD_WIDTH - 1, dy + 1); i++ )
                        if( battlefield[i][dx].get_tile() == Tile::Army )
                        {
                              auto stack = find_existing_enemy_stack_via_symbol( battlefield[i][dx].get_symbol(), battlefield[i][dx].get_team() );
                              inflict_damage(attacking_stack, stack, stack == defending_stack, attack_is_retaliation);
                        }
            }
            else if( ay == dy ) // vertically aligned
            {
                  for( int8_t j = std::max(0, dx - 1); j <= std::min(BATTLEFIELD_LENGTH - 1, dx + 1); j++ )
                        if( battlefield[dy][j].get_tile() == Tile::Army )
                        {
                              auto stack = find_existing_enemy_stack_via_symbol( battlefield[dy][j].get_symbol(), battlefield[dy][j].get_team() );
                              inflict_damage(attacking_stack, stack, stack == defending_stack, attack_is_retaliation);
                        }
            }
            else // diagonally aligned
            {
                  if( battlefield[dy][ax].get_tile() == Tile::Army )
                  {
                        auto stack = find_existing_enemy_stack_via_symbol( battlefield[dy][ax].get_symbol(), battlefield[dy][ax].get_team() );
                        inflict_damage(attacking_stack, stack, false, attack_is_retaliation);
                  }

                  if( battlefield[ay][dx].get_tile() == Tile::Army )
                  {
                        auto stack = find_existing_enemy_stack_via_symbol( battlefield[ay][dx].get_symbol(), battlefield[ay][dx].get_team() );
                        inflict_damage(attacking_stack, stack, false, attack_is_retaliation);
                  }
            }
      }
      else // only one target
            inflict_damage(attacking_stack, defending_stack, true, attack_is_retaliation);
}

void Battle::inflict_damage(Stack* const attacking_stack, Stack* const defending_stack, bool const defender_is_targeted, bool const attack_is_retaliation, bool const attack_is_second_attack)
{
      attacking_stack->set_action(Stack_Action::Attack);

      if( attacking_stack->get_team() == defending_stack->get_team() && !attacking_stack->get_creature()->get_has_attack_adjacent_hexes() && !attacking_stack->get_creature()->get_has_breath_attack() /* && TO DO : not 'Berserk'*/ )
            return;

      if( defending_stack == nullptr ) // check is should not be needed but is here, just in case
            return;

      if( defending_stack->get_has_perished() ) // check is should not be needed but is here, just in case
            return;
      
      uint32_t final_damage = 0;
      uint32_t base_damage  = 0;

      float I1(0.f), I2(0.f), I3(0.f), I4(0.f), I5(0.f); // increase damage
      float R1(0.f), R2(0.f), R3(0.f), R4(0.f), R5(0.f), R6(0.f), R7(0.f), R8(0.f); // reduce damage

      // Get the heroes of the two stack
      auto const attacking_hero = get_hero_of_stack(attacking_stack);
      auto const defending_hero = get_hero_of_stack(defending_stack);

      // attacking_stack's attributes
      auto const        attacking_creature        = attacking_stack->get_creature();
      const std::string attacking_stack_name      = attacking_stack->get_creature_name();
      const uint32_t    attacking_stack_number    = attacking_stack->get_number();
      uint8_t           attacking_stack_attack    = attacking_stack->get_att();
      const bool        attacking_stack_is_ranged = attacking_creature->get_is_ranged();
      const uint8_t     attacking_stack_max_dmg   = attacking_creature->get_max_dmg();
      const uint8_t     attacking_stack_min_dmg   = attacking_creature->get_min_dmg();

      const bool can_shoot = stack_can_shoot(attacking_stack, defending_stack);
      
      // penalties for shooting attacking_stack
      const bool melee_penalty    = attacking_stack_is_ranged && !can_shoot;
      const bool range_penalty    = attacking_stack_is_ranged && can_shoot && get_distance_between_stacks(attacking_stack, defending_stack) > 10 && !attacking_creature->get_no_range_penalty() /*&& !get_no_range_penalty() - stack method due to artifacts*/;
      const bool obstacle_penalty = attacking_stack_is_ranged && can_shoot && /* there's a wall between attacking_stack and defending_stack &&*/ !attacking_creature->get_no_obstacle_penalty() /*&& !get_no_obstacle_penalty() - stack method due to artifacts*/; // TO DO : implement

      // defending_stack's attributes
      auto const        defending_creature      = defending_stack->get_creature();
      const std::string defending_stack_name    = defending_stack->get_creature_name();
      uint8_t           defending_stack_defense = defending_stack->get_def();

      if( defending_stack->get_action() == Stack_Action::Defend ) 
            defending_stack_defense += defending_stack_defense/5;

      // special abilities which modify stack attributes
      if( defending_creature->get_ignore_enemy_attack() )
            attacking_stack_attack = attacking_stack_attack * (100 - defending_creature->get_ignore_enemy_attack_by_percent() ) / 100;

      if( attacking_creature->get_ignore_enemy_defense() )
            defending_stack_defense = defending_stack_defense * (100 - attacking_creature->get_ignore_enemy_defense_by_percent() ) / 100;

      // calculate I1 - Attack > Defense bonus
      if( attacking_stack_attack >= defending_stack_defense )
            I1 = 0.05 * (attacking_stack_attack - defending_stack_defense);

      // calculate I2 and I3 - secondary skill and specialty in Archery / Offense bonus
      if( attacking_stack_is_ranged && can_shoot )
      {
            switch( attacking_hero->get_secondary_skill_level("Archery") )
            {
                  case Skill_level::None :     I2 = 0.00f; break;
                  case Skill_level::Basic :    I2 = 0.10f; break;
                  case Skill_level::Advanced : I2 = 0.25f; break;
                  case Skill_level::Expert :   I2 = 0.50f; break;
            }

            if( attacking_hero->get_specialty().get_name() == "Archery" )
                  I3 = 0.05 * I2 * attacking_hero->get_level();
      }
      else // is ranged but has melee penalty or is not ranged
      {
            switch( attacking_hero->get_secondary_skill_level("Offense") )
            {
                  case Skill_level::None :     I2 = 0.00f; break;
                  case Skill_level::Basic :    I2 = 0.10f; break;
                  case Skill_level::Advanced : I2 = 0.20f; break;
                  case Skill_level::Expert :   I2 = 0.30f; break;
            }

            if( attacking_hero->get_specialty().get_name() == "Offense")
                  I3 = 0.05 * I2 * attacking_hero->get_level();
      }

      // calculate I4 - luck bonus
      const int8_t rolled_luck = roll_luck(attacking_stack);
      I4 = -0.5*(rolled_luck <  0) + /*  0.0*( rolled_luck == 0) + */  1.0*(rolled_luck >  0) * (1 - get_hourglass_of_evil_hour_present());

      // calculate I5 - special ability bonus
      // death blow bonus
      if( attacking_creature->get_may_cast_death_blow() )
            I5 = ( (rand() % 100) < CHANCE_TO_CAST_DEATH_BLOW ) * 1.00f;

      // hate bonus
      if     ( attacking_creature->get_hates_efreeti()       && ( defending_stack_name == "Efreet" || defending_stack_name == "Efreet Sultan" ) ) I5 = 0.50f;
      else if( attacking_creature->get_hates_genies()        && ( defending_stack_name == "Genie"  || defending_stack_name == "Master Genie" )  ) I5 = 0.50f;
      else if( attacking_creature->get_hates_devils()        && ( defending_stack_name == "Devil"  || defending_stack_name == "Arch Devil" )    ) I5 = 0.50f;
      else if( attacking_creature->get_hates_angels()        && ( defending_stack_name == "Angel"  || defending_stack_name == "Archangel" )     ) I5 = 0.50f;
      else if( attacking_creature->get_hates_black_dragons() &&   defending_stack_name == "Black Dragon" ) I5 = 0.50f;
      else if( attacking_creature->get_hates_titans()        &&   defending_stack_name == "Titan"        ) I5 = 0.50f;

      // elementals bonus
      if     ( ( attacking_stack_name == "Air Elemental"   || attacking_stack_name == "Storm Elemental"  ) && ( defending_stack_name == "Earth Elemental" || defending_stack_name == "Magma Elemental"  ) ) I5 = 1.00f;
      else if( ( attacking_stack_name == "Water Elemental" || attacking_stack_name == "Ice Elemental"    ) && ( defending_stack_name == "Fire Elemental"  || defending_stack_name == "Energy Elemental" ) ) I5 = 1.00f;
      else if( ( attacking_stack_name == "Fire Elemental"  || attacking_stack_name == "Energy Elemental" ) && ( defending_stack_name == "Water Elemental" || defending_stack_name == "Ice Elemental"    ) ) I5 = 1.00f;
      else if( ( attacking_stack_name == "Earth Elemental" || attacking_stack_name == "Magma Elemental"  ) && ( defending_stack_name == "Air Elemental"   || defending_stack_name == "Storm Elemental"  ) ) I5 = 1.00f;

      // jousting bonus
      if( !defending_creature->get_is_immune_to_jousting() ) 
            if( attacking_creature->get_has_jousting() ) 
            I5 = 0.05 * attacking_stack->get_distance_traveled();


      // calculate R1 - Defense > Attack penalty
      if( defending_stack_defense >= attacking_stack_attack && ( !attacking_stack_is_ranged || melee_penalty ) )
            R1 = 0.025 * (defending_stack_defense - attacking_stack_attack);

      // calculate R2 - Armorer penalty
      switch( defending_hero->get_secondary_skill_level("Armorer") )
      {
            case Skill_level::None :     R2 = 0.00f; break;
            case Skill_level::Basic :    R2 = 0.05f; break;
            case Skill_level::Advanced : R2 = 0.10f; break;
            case Skill_level::Expert :   R2 = 0.15f; break;
      }

      // calculate R3 - specialty Armorer penalty
      if( defending_hero->get_specialty().get_name() == "Armorer")
            R3 = 0.05 * R2 * defending_hero->get_level();

      // calculate R4 - spells Shield and Air Shield bonus
      // TO DO : if spells

      // calculate R5 - range or melee penalties
      if     ( range_penalty ) R5 = 0.50f;
      else if( melee_penalty ) R5 = 0.50f;

      // calculate R6 - obstacle penalty
      // TO DO : if obstacle penalties - siege wall between shooter and defending_stack
      if( obstacle_penalty ) R6 = 0.50f; // range penalty

      // calculate R7 - spells Blind and Forgetfulness penalty
      // TO DO : if retaliation or attack after spell

      // calculate R8 - special abilities penalty
      if     ( attacking_stack_name == "Psychic Elemental" && defending_creature->get_is_immune_to_mind_spells() ) R8 = 0.50f;
      else if( attacking_stack_name == "Magic Elemental"   && defending_creature->get_is_immune_to_all_spells()  ) R8 = 0.50f;
      // TO DO : implement retaliation after Stone Gaze and Paralyzing Venom


      if( attacking_stack_min_dmg == attacking_stack_max_dmg )
            base_damage = attacking_stack_min_dmg * attacking_stack_number;
      else
      {
            const uint8_t range = attacking_stack_max_dmg - attacking_stack_min_dmg + 1;
            
            if( attacking_stack_number <= min_num_for_stack_to_count_as_group_to_calc_rand_dmg )
                  for(int i = 0; i < attacking_stack_number; i++)
                        base_damage += rand() % range + attacking_stack_min_dmg;
            else
            {
                  for(int i = 0; i < min_num_for_stack_to_count_as_group_to_calc_rand_dmg; i++)
                        base_damage += rand() % range + attacking_stack_min_dmg;
                  
                  base_damage = base_damage * attacking_stack_number/min_num_for_stack_to_count_as_group_to_calc_rand_dmg;
            }
      }

      #if SHOW_DAMAGE_INFO == 1
      printf( "\nDamage parameters:\n" );
      printf( "\t- I1 = %.3f\n\t- I2 = %.3f\n\t- I3 = %.3f\n\t- I4 = %.3f\n\t- I5 = %.3f\n", I1, I2, I3, I4, I5 );
      printf( "\t- R1 = %.3f\n\t- R2 = %.3f\n\t- R3 = %.3f\n\t- R4 = %.3f\n\t- R5 = %.3f\n\t- R6 = %.3f\n\t- R7 = %.3f\n\t- R8 = %.3f\n\n", R1, R2, R3, R4, R5, R6, R7, R8 );
      #endif

      final_damage = static_cast<int32_t>( base_damage * (1 + I1 + I2 + I3 + I4 + I5) * (1 - R1) * (1 - R2 - R3) * (1 - R4) * (1 - R5) * (1 - R6) * (1 - R7) * (1 - R8) );
      
      if     ( !attack_is_retaliation && !attack_is_second_attack ) printf( "Stack of %d %s attacks and does %d damage to %s.\n",                   attacking_stack_number, attacking_stack_name.c_str(), final_damage, defending_stack_name.c_str() );
      else if(  attack_is_retaliation && !attack_is_second_attack ) printf( "Stack of %d %s retaliates and does %d damage to %s.\n",                attacking_stack_number, attacking_stack_name.c_str(), final_damage, defending_stack_name.c_str() );
      else if( !attack_is_retaliation &&  attack_is_second_attack ) printf( "Stack of %d %s attacks for a second time and does %d damage to %s.\n", attacking_stack_number, attacking_stack_name.c_str(), final_damage, defending_stack_name.c_str() );
      else if(  attack_is_retaliation &&  attack_is_second_attack ) { std::cerr << "\nRetaliation cannot be a double attack!" << std::endl; abort(); }
      
      // TO DO : apply special abilities with pre-hit effects

      defending_stack->recieve_damage(final_damage);

      // TO DO : apply special abilities with hit-on effects

      // If attacking stack has breath attack, an additional stack, situated behind the defending stack will suffer from the attack.
      if( attacking_creature->get_has_breath_attack() && defender_is_targeted )
      {
            // Coordinates of the attacking stack
            const uint8_t ax = attacking_stack->get_position().x;
            const uint8_t ay = attacking_stack->get_position().y;
            
            // Coordinates of the defending stack
            const uint8_t dx = defending_stack->get_position().x;
            const uint8_t dy = defending_stack->get_position().y;

            // Coordinates of field 'behind' defending stack, from attacking stack's point of view.
            const uint8_t x = std::max<int8_t>( 0, std::min<int8_t>( dx + (dx - ax), BATTLEFIELD_LENGTH ) );
            const uint8_t y = std::max<int8_t>( 0, std::min<int8_t>( dy + (dy - ay), BATTLEFIELD_WIDTH  ) );
            
            if( battlefield[y][x].get_tile() == Tile::Army && battlefield[y][x].get_symbol() != defending_stack->get_battlefield_symbol() )
            {
                  auto stack = find_existing_stack_via_position( Position(x, y) );
                  if( stack != nullptr )
                        inflict_damage(attacking_stack, stack, false);
            }
      }
      
      // TO DO : if defending_stack is Efreet Sultan or has spell fire shield attacker and attacker is not immuned - attacker should recieve dmg

      if( !defending_stack->get_has_perished() )
      {
            if( defender_is_targeted && !attack_is_retaliation && ( get_distance_between_stacks(attacking_stack, defending_stack) == 1 ) )
                  if( !attacking_creature->get_no_enemy_retaliation() )
                        retaliate( defending_stack, attacking_stack );

            if( !attack_is_retaliation && ( attacking_creature->get_has_double_attack() || attacking_creature->get_has_ferocity() ) && !attack_is_second_attack )
                  inflict_damage( attacking_stack, defending_stack, true, false, true );
      }
}

void Battle::retaliate(Stack* attacking_stack, Stack* defending_stack)
{
    if( attacking_stack->get_retaliations_left() || attacking_stack->get_creature()->get_has_unlimited_retaliations() )
        {
            if( !attacking_stack->get_creature()->get_has_unlimited_retaliations() )
                attacking_stack->set_retaliations_left( attacking_stack->get_retaliations_left() - 1 );
            
            target_and_inflict_damage(attacking_stack, defending_stack, true);
        }
}


bool Battle::stack_can_shoot(Stack* const attacking_stack, Stack* const defending_stack)
{
      // TO DO : add 'Force Field'
      if( attacking_stack->get_creature()->get_is_ranged() && attacking_stack->get_shots_left() ) // is a shooter with enough ammo
      {
            if( defending_stack != nullptr)
                  if( stacks_are_adjacent(attacking_stack, defending_stack) )
                        return attacking_stack->get_creature()->get_no_melee_penalty();
            if( has_adjacent_enemy(attacking_stack) /* TO DO : && hero has not equipped 'Bow of the Sharpshooter' */ )
                  return false;
            return true;
      }
      
      return false;
}

Hero* Battle::get_hero_of_stack(Stack* const stack)
{
      if( stack->get_team() == get_attacker()->get_team() )
            return get_attacker();
      
      return get_defender();
}

bool Battle::check_battle_finished()
{
      // First, check to see if any of the armies has perished
      auto const turns = get_turns();
      if( turns->size() > 1 ) // at least one stack
      {
            bool has_attacker_stack = false; // shows if there is at least one attacker stack on the battlefield 
            bool has_defender_stack = false; // shows if there is at least one defender stack on the battlefield
            
            for( uint8_t i = 0; i < turns->size(); i++ )
            {
                  if     ( turns->at(i)->get_team() == _attacker.get_team() ) { has_attacker_stack = true; }
                  else if( turns->at(i)->get_team() == _defender.get_team() ) { has_defender_stack = true; }
                  
                  if( has_attacker_stack && has_defender_stack ) // returns false on the first indication of two seperate teams on the battlefield
                        return false;
            }
            
            if( has_attacker_stack != has_defender_stack ) 
                  return true;
      }
      else
            return true;
      
      return false; // cannot be reached, but placed against compiler warnings
}