#include "Creature_Stack.h"

Stack::Stack(const Creature creature, const uint32_t number, const uint8_t pos_x, const uint8_t pos_y, const char battlefield_symbol, const Team team = Team::Neutral) :
             _creature(creature), _number(number), _pos(pos_x, pos_y), _battlefield_symbol(battlefield_symbol), _team(team),
             battle_stats(creature)
             {};

Stack::Stack(const Creature creature, const uint32_t number, const Team team = Team::Neutral) :
             _creature(creature), _number(number), _team(team),
             battle_stats(creature)
             {};

Stack::Stack(const Stack& stack, const uint32_t number) :
             _creature(stack._creature), _number(std::min(stack._number, number)), _team(stack._team),
             battle_stats(stack._creature)
             {};

Stack::Stack(const Stack* stack, const uint32_t number) :
             _creature(stack->_creature), _number(std::min(stack->_number, number)), _team(stack->_team),
             battle_stats(stack->_creature)
             {};

Stack::~Stack()
{
    // printf( "Stack %s destroyed!\n", get_creature().get_name().c_str() );
}

std::string Stack::get_team_as_string()
{
      std::string team;

      switch(get_team())
      {
            case Team::Neutral : team = "Neutral";  break;
            case Team::Red     : team = "Red";      break;
            case Team::Blue    : team = "Blue";     break;
            case Team::Tan     : team = "Tan";      break;
            case Team::Green   : team = "Green";    break;
            case Team::Orange  : team = "Orange";   break;
            case Team::Purple  : team = "Purple";   break;
            case Team::Teal    : team = "Teal";     break;
            case Team::Pink    : team = "Pink";     break;
      }
      return team;
}

void Stack::reset_stats()
{
    battle_stats._att        = get_creature()->get_att();
    battle_stats._def        = get_creature()->get_def();
    battle_stats._shots_left = get_creature()->get_shots();
    battle_stats._hp         = get_creature()->get_hp();
    battle_stats._hp_left    = battle_stats._hp;
    battle_stats._speed      = get_creature()->get_speed();
    battle_stats._morale     = get_creature()->get_morale();
    battle_stats._luck       = get_creature()->get_luck();
    battle_stats._number_of_casts_left = get_creature()->get_number_of_casts();
}

void Stack::set_morale(const Morale morale) 
{ 
    if( ( !get_creature()->get_is_undead() && !get_creature()->get_is_bloodless() ) || ( *get_creature() == Creature_List::Stone_Gargoyle || *get_creature() == Creature_List::Obsidian_Gargoyle ) ) 
        battle_stats._morale = morale; 
}

void Stack::add_morale(const Morale morale) 
{ 
    if( ( !get_creature()->get_is_undead() && !get_creature()->get_is_bloodless() ) || ( *get_creature() == Creature_List::Stone_Gargoyle || *get_creature() == Creature_List::Obsidian_Gargoyle ) ) 
        battle_stats._morale = static_cast<Morale>( std::min( std::max( static_cast<int8_t>(battle_stats._morale) + static_cast<int8_t>(morale), -3), 3) ); 
}

void Stack::recieve_damage(const uint32_t damage)
{
    const uint16_t hp = get_hp();              // hp per unit
    const uint16_t hp_last = get_hp_left();    // hp of last unit
    const uint32_t initial_num = get_number(); // amount of creatures in stack

    uint64_t capacity = hp*(initial_num - 1) + hp_last;

    if( damage >= capacity )
    {
        set_number(0);
        set_has_perished(true);
        printf( "The whole %s stack has perished!\n", get_creature_name().c_str() );

        set_action(Action::Skip);
        return;
    }
    else
    {
        set_hp_left( static_cast<uint16_t>( (capacity - damage) % hp ) );
        uint32_t new_num = static_cast<uint32_t>( (capacity - damage) / hp ) + 1 * ( get_hp_left() != 0 );

        uint32_t delta_num = initial_num - new_num;

        if(delta_num)
        {
            set_number(new_num);
            printf( "%d %s perished!\n", delta_num, get_creature_name().c_str() );
        }

        #if SHOW_DAMAGE_INFO == 1
            printf( "Last %s in stack has %d hp left.\n", get_creature_name().c_str(), get_hp_left() + hp*( get_hp_left() == 0 ) );
        #endif
    }
}

void Stack::print_battle_info()
{
    auto const c = get_creature();
    printf("Name : %s\n",    c->get_name().c_str());
    printf("Faction : %s\n", c->get_faction_as_string().c_str());
    printf("Level : %d\n",   c->get_level());
    printf("Upgrade level : %d\n", c->get_upgrade());
    printf("Attack : %d(%d)\n",    c->get_att(), get_att());
    printf("Defense : %d(%d)\n",   c->get_def(), get_def());

    if( c->get_is_ranged() )
        printf("Shots : %d(%d)\n", c->get_shots(), get_shots_left());
    
    printf("Damage : %d - %d\n", c->get_min_dmg(), c->get_max_dmg());
    printf("Health : %d(%d)\n",  c->get_hp(), get_hp_left());
    printf("Speed : %d(%d)\n",   c->get_speed(), get_speed() );
    printf("Morale : %d\n", get_morale());
    printf("Luck : %d\n",   get_luck());

    if( c->get_special_abilities().length() != 0 )
        printf("Special abilities : %s\n", c->get_special_abilities().c_str());
}

void Stack::print_full_info()
{
    auto const c = get_creature();
    printf( "\n" );
    printf( "Number : %d\n",  get_number() );
    printf( "Name : %s\n",    c->get_name().c_str() );
    printf( "Faction : %s\n", c->get_faction_as_string().c_str() );
    printf( "Level : %d\n",   c->get_level() );
    printf( "Upgrade level : %d\n",   c->get_upgrade() );
    printf( "Growth per week : %d\n", c->get_growth()  );
    printf( "Attack : %d(%d)\n",  c->get_att(), get_att() );
    printf( "Defense : %d(%d)\n", c->get_def(), get_def() );

    if( c->get_is_ranged() )
        printf( "Shots : %d\n", c->get_shots() );
    
    if( c->get_min_dmg() != c->get_max_dmg() )
        printf( "Damage : %d - %d\n", c->get_min_dmg(), c->get_max_dmg() );
    else
        printf( "Damage : %d\n", c->get_min_dmg() );

    printf("Health : %d(%d)\n",  get_hp_left(), get_hp() );
    printf("Speed : %d(%d)\n",   c->get_speed(), get_speed() );
    printf("Morale : %d\n",      get_morale() );
    printf("Luck : %d\n",        get_luck() );
    printf("Fight value : %d\n", c->get_fight_value() );
    printf("AI value : %d\n",    c->get_ai_value() );
    printf("%s", c->get_cost().c_str());

    if( c->get_special_abilities().length() != 0 )
        printf( "Special abilities : %s\n", c->get_special_abilities().c_str() );
}