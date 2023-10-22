#ifndef CREATURE_STACK_CPP
#define CREATURE_STACK_CPP

#include "Creature_Stack.h"

Stack::Stack(const Creature creature, const uint32_t number, const uint8_t pos_x, const uint8_t pos_y, const Team team = Team::Neutral) :
             _creature(creature), _number(number), _pos(pos_x, pos_y), _team(team),
             battle_stats(creature), 
             hero_secondary_skills()
             {};

Stack::Stack(const Creature creature, const uint32_t number, const Team team = Team::Neutral) :
             _creature(creature), _number(number), _team(team),
             battle_stats(creature),
             hero_secondary_skills()
             {};

Stack::Stack(const Stack& stack, const uint32_t number) :
             _creature(stack._creature), _number(std::min(stack._number, number)), _team(stack._team),
             battle_stats(stack._creature),
             hero_secondary_skills(stack.hero_secondary_skills)
             {};

Stack::Stack(const Stack* stack, const uint32_t number) :
             _creature(stack->_creature), _number(std::min(stack->_number, number)), _team(stack->_team),
             battle_stats(stack->_creature),
             hero_secondary_skills(stack->hero_secondary_skills)
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
    if( ( !get_creature()->get_is_undead() && !get_creature()->get_is_bloodless() ) || (  get_creature()->get_name() == "Stone Gargoyle" || get_creature()->get_name() == "Obsidian Gargoyle" ) ) 
        battle_stats._morale = morale; 
}

void Stack::add_morale(const Morale morale) 
{ 
    if( ( !get_creature()->get_is_undead() && !get_creature()->get_is_bloodless() ) || ( get_creature()->get_name() == "Stone Gargoyle" || get_creature()->get_name() == "Obsidian Gargoyle" ) ) 
        battle_stats._morale = static_cast<Morale>( std::min( std::max( static_cast<int8_t>(battle_stats._morale) + static_cast<int8_t>(morale), -3), 3) ); 
}


void Stack::new_turn()
{
    if( _has_perished )
    {
        set_action(Stack_Action::Skip);
        return;
    }
    
    if( true ) // if creature is not blinded its status should be returned to default
        set_action(Stack_Action::Skip); // default value for normal turns
    else
        set_action(Stack_Action::Attack); // default value for normal turns

    // reduce spell duration acting on stacks
}

void Stack::take_action()
{
    // call the functions in the correct order
}


void Stack::recieve_damage(uint32_t damage)
{
    uint16_t hp = get_hp();           // hp per unit
    uint16_t hp_last = get_hp_left(); // hp of last unit
    uint32_t initial_num = get_number();      // amount of creatures in stack

    uint64_t capacity = hp*(initial_num - 1) + hp_last;

    if( damage >= capacity )
    {
        set_number(0);
        set_has_perished(true);
        printf( "The whole %s stack has perished!\n", get_creature()->get_name().c_str() );

        set_action(Stack_Action::Skip);
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
            printf( "%d %s perished!\n", delta_num, get_creature()->get_name().c_str() );
        }

        #if SHOW_DEBUG_INFO == 1
            printf( "Last %s in stack has %d hp left.\n", get_creature()->get_name().c_str(), get_hp_left() );
        #endif
    }
}

bool Stack::roll_negative_morale()
{
    uint16_t probability;

    switch(get_morale())
    {
        case Morale::Terrible : probability = 250; break;
        case Morale::Awful    : probability = 167; break;
        case Morale::Bad      : probability =  83; break;
        case Morale::Neutral  : probability =   0; break; // written because of compiler warnings (I prefer not to silence them as errors might be missed)
        case Morale::Good     : probability =   0; break; // written because of compiler warnings (I prefer not to silence them as errors might be missed)
        case Morale::Great    : probability =   0; break; // written because of compiler warnings (I prefer not to silence them as errors might be missed)
        case Morale::Superb   : probability =   0; break; // written because of compiler warnings (I prefer not to silence them as errors might be missed)
    }
    return rand() % 1000 < probability;
}

bool Stack::roll_positive_morale()
{
    uint16_t probability;

    switch(get_morale())
    {
        case Morale::Terrible : probability =   0; break; // written because of compiler warnings (I prefer not to silence them as errors might be missed)
        case Morale::Awful    : probability =   0; break; // written because of compiler warnings (I prefer not to silence them as errors might be missed)
        case Morale::Bad      : probability =   0; break; // written because of compiler warnings (I prefer not to silence them as errors might be missed)
        case Morale::Neutral  : probability =   0; break; // written because of compiler warnings (I prefer not to silence them as errors might be missed)
        case Morale::Good     : probability =  42; break;
        case Morale::Great    : probability =  83; break;
        case Morale::Superb   : probability = 125; break;
    }
    return rand() % 1000 < probability;
}

int8_t Stack::roll_luck(bool leprechauns_in_army, bool hero_has_equipped_hourglass_of_the_evil_hour)
{
    // Leprechauns double the luck chance.
    // Item 'Hourglass of the Evil Hour' negates all positive luck effects.
    uint16_t probability;
    int8_t sign;

    switch(get_luck())
    {
        case Luck::Terrible : probability = 250*(1 + leprechauns_in_army);                                                    sign = -1; break;
        case Luck::Awful    : probability = 167*(1 + leprechauns_in_army);                                                    sign = -1; break;
        case Luck::Bad      : probability =  83*(1 + leprechauns_in_army);                                                    sign = -1; break;
        case Luck::Neutral  : probability =   0*(1 + leprechauns_in_army);                                                    sign =  0; break;
        case Luck::Good     : probability =  42*(1 + leprechauns_in_army)*(1 - hero_has_equipped_hourglass_of_the_evil_hour); sign =  1; break;
        case Luck::Great    : probability =  83*(1 + leprechauns_in_army)*(1 - hero_has_equipped_hourglass_of_the_evil_hour); sign =  1; break;
        case Luck::Superb   : probability = 125*(1 + leprechauns_in_army)*(1 - hero_has_equipped_hourglass_of_the_evil_hour); sign =  1; break;
    }
    return sign*(rand() % 1000 < probability);
}

// void Stack::wait(){}

// void Stack::defend(){}

void Stack::move(uint8_t x, uint8_t y)
{
    uint8_t distance = std::abs(x - _pos.x) + std::abs(y - _pos.y);
    while(get_creature()->get_speed() < distance)
    {
        printf("%s have only %i speed and can't move that far. Pick a new position!", get_creature()->get_name());
    }

    if(get_creature()->get_is_flying()) // true for both flying and teleporting creatures
    {
        _pos.x = x;
        _pos.y = y;
    }
    else
    {
        // TO DO : implement walking through every tile on the battle field for on-tile effects - quicksand and siege wall bombs, rivers, spikes, etc.
        /*_distance_traveled = 0;
        while( distance )
        {  
            // TO DO : implement movement patterns
            _distance_traveled++;
        }*/
        if( get_creature()->get_has_jousting() )
            _distance_traveled = std::abs(_pos.x - x) + std::abs(_pos.y - y);
        _pos.x = x; // this acts like flying teleporting and it should not
        _pos.y = y; // this acts like flying teleporting and it should not
    }

}

void Stack::attack(Stack& defender, bool attack_is_retaliation, bool attack_is_second_attack, bool leprechauns_in_army, bool hero_has_equipped_hourglass_of_the_evil_hour)
{
    if( get_team() == defender.get_team() /* && TO DO : not berserk*/ )
        return;

    if( defender.get_has_perished() )
        return;

    if(!target(defender))
        return;

    uint32_t final_damage = 0;
    uint32_t base_damage = 0;

    float I1(0.f), I2(0.f), I3(0.f), I4(0.f), I5(0.f); // increase damage
    float R1(0.f), R2(0.f), R3(0.f), R4(0.f), R5(0.f), R6(0.f), R7(0.f), R8(0.f); // reduce damage

    // attacker's attributes
    std::string attacker_name      = get_creature()->get_name();
    uint32_t    attacker_number    = get_number();
    uint8_t     attacker_attack    = get_att();
    bool        attacker_is_ranged = get_creature()->get_is_ranged();
    uint8_t     attacker_max_dmg   = get_creature()->get_max_dmg();
    uint8_t     attacker_min_dmg   = get_creature()->get_min_dmg();

    // penalties for shooting attacker
    bool melee_penalty    = attacker_is_ranged && !can_shoot();
    bool range_penalty    = attacker_is_ranged && can_shoot() && get_distance_to_target(defender) > 10 && !get_creature()->get_no_range_penalty() /*&& !get_no_range_penalty() - stack method due to artifacts*/;
    bool obstacle_penalty = attacker_is_ranged && can_shoot() && /* there's a wall between attacker and defender &&*/ !get_creature()->get_no_obstacle_penalty() /*&& !get_no_obstacle_penalty() - stack method due to artifacts*/; // TO DO : implement

    // defender's attributes
    std::string defender_name      = defender.get_creature()->get_name();
    uint8_t     defender_defense   = defender.get_def();

    if( defender.get_action() == Stack_Action::Defend ) 
        defender_defense += defender_defense/5;

    // special abilities which modify stack attributes
    if( defender.get_creature()->get_ignore_enemy_attack() )
        attacker_attack = attacker_attack * (100 - defender.get_creature()->get_ignore_enemy_attack_by_percent() ) / 100;

    if( get_creature()->get_ignore_enemy_defense() )
        defender_defense = defender_defense * (100 - get_creature()->get_ignore_enemy_defense_by_percent() ) / 100;

    // calculate I1 - Attack > Defense bonus
    if( attacker_attack >= defender_defense )
        I1 = 0.05 * (attacker_attack - defender_defense);

    // calculate I2 and I3 - secondary skill and specialty in Archery / Offense bonus
    if( attacker_is_ranged && can_shoot() )
    {
        switch(get_hero_level_of_archery())
        {
                case Skill_level::None :     I2 = 0.00f; break;
                case Skill_level::Basic :    I2 = 0.10f; break;
                case Skill_level::Advanced : I2 = 0.25f; break;
                case Skill_level::Expert :   I2 = 0.50f; break;
        }

        if( get_hero_specialty_name() == "Archery")
            I3 = 0.05 * I2 * get_hero_level();
    }
    else // is ranged but has melee penalty or is not ranged
    {
        switch(get_hero_level_of_offense())
        {
                case Skill_level::None :     I2 = 0.00f; break;
                case Skill_level::Basic :    I2 = 0.10f; break;
                case Skill_level::Advanced : I2 = 0.20f; break;
                case Skill_level::Expert :   I2 = 0.30f; break;
        }

        if( get_hero_specialty_name() == "Offense")
            I3 = 0.05 * I2 * get_hero_level();
    }

    // calculate I4 - luck bonus
    int8_t rolled_luck = roll_luck(leprechauns_in_army, hero_has_equipped_hourglass_of_the_evil_hour);
    I4 = -0.5*(rolled_luck <  0) + /*  0.0*( rolled_luck == 0) + */  1.0*(rolled_luck >  0);
    
    // calculate I5 - special ability bonus
    // death blow bonus
    if( get_creature()->get_may_cast_death_blow() ) I5 = ((rand() % 100) < CHANCE_TO_CAST_DEATH_BLOW)*1.00f;

    // hate bonus
    if     ( get_creature()->get_hates_efreeti()       && ( defender_name == "Efreet" || defender_name == "Efreet Sultan" ) ) I5 = 0.50f;
    else if( get_creature()->get_hates_genies()        && ( defender_name == "Genie"  || defender_name == "Master Genie" )  ) I5 = 0.50f;
    else if( get_creature()->get_hates_devils()        && ( defender_name == "Devil"  || defender_name == "Arch Devil" )    ) I5 = 0.50f;
    else if( get_creature()->get_hates_angels()        && ( defender_name == "Angel"  || defender_name == "Archangel" )     ) I5 = 0.50f;
    else if( get_creature()->get_hates_black_dragons() &&   defender_name == "Black Dragon" ) I5 = 0.50f;
    else if( get_creature()->get_hates_titans()        &&   defender_name == "Titan"        ) I5 = 0.50f;

    // elementals bonus
    if     ( ( attacker_name == "Air Elemental"   || attacker_name == "Storm Elemental"  ) && ( defender_name == "Earth Elemental" || defender_name == "Magma Elemental"  ) ) I5 = 1.00f;
    else if( ( attacker_name == "Water Elemental" || attacker_name == "Ice Elemental"    ) && ( defender_name == "Fire Elemental"  || defender_name == "Energy Elemental" ) ) I5 = 1.00f;
    else if( ( attacker_name == "Fire Elemental"  || attacker_name == "Energy Elemental" ) && ( defender_name == "Water Elemental" || defender_name == "Ice Elemental"    ) ) I5 = 1.00f;
    else if( ( attacker_name == "Earth Elemental" || attacker_name == "Magma Elemental"  ) && ( defender_name == "Air Elemental"   || defender_name == "Storm Elemental"  ) ) I5 = 1.00f;

    // jousting bonus
    if( !defender.get_creature()->get_is_immune_to_jousting() ) 
        if( get_creature()->get_has_jousting() ) 
            I5 = 0.05 * get_distance_traveled();


    // calculate R1 - Defense > Attack penalty
    if( defender_defense >= attacker_attack && ( !attacker_is_ranged || melee_penalty ) )
        R1 = 0.025 * (defender_defense - attacker_attack);

    // calculate R2 - Armorer penalty
    switch(defender.get_hero_level_of_armorer())
    {
            case Skill_level::None :     R2 = 0.00f; break;
            case Skill_level::Basic :    R2 = 0.05f; break;
            case Skill_level::Advanced : R2 = 0.10f; break;
            case Skill_level::Expert :   R2 = 0.15f; break;
    }

    // calculate R3 - specialty Armorer penalty
    if( get_hero_specialty_name() == "Armorer")
        R3 = 0.05 * R2 * get_hero_level();

    // calculate R4 - spells Shield and Air Shield bonus
    // TO DO : if spells
    
    // calculate R5 - range or melee penalties
    if     ( range_penalty ) R5 = 0.50f;
    else if( melee_penalty ) R5 = 0.50f;

    // calculate R6 - obstacle penalty
    // TO DO : if obstacle penalties - siege wall between shooter and defender
    if( obstacle_penalty ) R6 = 0.50f; // range penalty
    
    // calculate R7 - spells Blind and Forgetfulness penalty
    // TO DO : if retaliation or attack after spell
    
    // calculate R8 - special abilities penalty
    if     ( attacker_name == "Psychic Elemental" && defender.get_creature()->get_is_immune_to_mind_spells() ) R8 = 0.50f;
    else if( attacker_name == "Magic Elemental"   && defender.get_creature()->get_is_immune_to_all_spells()  ) R8 = 0.50f;
    // TO DO : implement retaliation after Stone Gaze and Paralyzing Venom


    if( attacker_min_dmg == attacker_max_dmg )
        base_damage = attacker_min_dmg * attacker_number;
    else
    {
        uint8_t range = attacker_max_dmg - attacker_min_dmg + 1;
        
        if( attacker_number <= min_num_for_stack_to_count_as_group_to_calc_rand_dmg )
            for(int i = 0; i < attacker_number; i++)
                base_damage += rand() % range + attacker_min_dmg;
        else
        {
            for(int i = 0; i < min_num_for_stack_to_count_as_group_to_calc_rand_dmg; i++)
                base_damage += rand() % range + attacker_min_dmg;
            
            base_damage = base_damage * attacker_number/min_num_for_stack_to_count_as_group_to_calc_rand_dmg;
        }
    }

#if SHOW_DEBUG_INFO == 1
    printf( "\nDamage parameters:\n" );
    printf( "\t- I1 = %.3f\n\t- I2 = %.3f\n\t- I3 = %.3f\n\t- I4 = %.3f\n\t- I5 = %.3f\n", I1, I2, I3, I4, I5 );
    printf( "\t- R1 = %.3f\n\t- R2 = %.3f\n\t- R3 = %.3f\n\t- R4 = %.3f\n\t- R5 = %.3f\n\t- R6 = %.3f\n\t- R7 = %.3f\n\t- R8 = %.3f\n\n", R1, R2, R3, R4, R5, R6, R7, R8 );
#endif

    final_damage = static_cast<int32_t>( base_damage * (1 + I1 + I2 + I3 + I4 + I5) * (1 - R1) * (1 - R2 - R3) * (1 - R4) * (1 - R5) * (1 - R6) * (1 - R7) * (1 - R8) );
    
    if     ( !attack_is_retaliation && !attack_is_second_attack ) printf( "Stack of %d %s attacks and does %d damage to %s.\n", attacker_number, attacker_name.c_str(), final_damage, defender_name.c_str() );
    else if(  attack_is_retaliation && !attack_is_second_attack ) printf( "Stack of %d %s retaliates and does %d damage to %s.\n", attacker_number, attacker_name.c_str(), final_damage, defender_name.c_str() );
    else if( !attack_is_retaliation &&  attack_is_second_attack ) printf( "Stack of %d %s attacks for a second time and does %d damage to %s.\n", attacker_number, attacker_name.c_str(), final_damage, defender_name.c_str() );
    else if(  attack_is_retaliation &&  attack_is_second_attack ) { std::cerr << "\nRetaliation cannot be a double attack!\n"; abort(); }
    
    // TO DO : apply special abilities with pre-hit effects

    // TO DO : if creature can attack surrounding enemies - they should recieve dmg
    defender.recieve_damage(final_damage);

    // TO DO : apply special abilities with hit-on effects

    // TO DO : if defender is efreet sultan or has spell fire shield attacker and attacker is not immuned - attacker should recieve dmg

    if( !attack_is_retaliation && get_distance_to_target(defender) == 1  )
        if( !get_creature()->get_no_enemy_retaliation() )
            defender.retaliate(*this);

    if( !attack_is_retaliation && ( get_creature()->get_has_double_attack() || get_creature()->get_has_ferocity() ) && !attack_is_second_attack )
        attack(defender, false, true);
}

bool Stack::can_shoot()
{
    // TO DO : if archer has arrows and no active enemy is in the way
    /*
    if( get_shots_left() )
        if( has_enemy_in_surroundings() && !get_creature()->get_has_no_melee_penalty() ) // if enemy is blinded/petrified, can shooters shoot?
            return true;

    return false;
    */

    return true;
}

bool Stack::target(Stack& stack)
{
    // TO DO : if attacker can reach defender
    return true;
}

void Stack::retaliate(Stack& attacker)
{
    if( get_retaliations_left() || get_creature()->get_has_unlimited_retaliations() )
        {
            if( !get_creature()->get_has_unlimited_retaliations() )
                set_retaliations_left( get_retaliations_left() - 1 );
            attack(attacker, true, false);
        }
}

void Stack::print_battle_info()
{
    auto c = get_creature();
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
    printf("Morale : %d\n", c->get_morale());
    printf("Luck : %d\n",   c->get_luck());

    if( c->get_special_abilities().length() != 0 )
        printf("Special abilities : %s\n", c->get_special_abilities().c_str());
}

void Stack::print_full_info()
{
    auto c = get_creature();
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
    printf("Morale : %d\n",      c->get_morale() );
    printf("Luck : %d\n",        c->get_luck() );
    printf("Fight value : %d\n", c->get_fight_value() );
    printf("AI value : %d\n",    c->get_ai_value() );
    printf("%s", c->get_cost().c_str());

    if( c->get_special_abilities().length() != 0 )
        printf( "Special abilities : %s\n", c->get_special_abilities().c_str() );
}

#endif