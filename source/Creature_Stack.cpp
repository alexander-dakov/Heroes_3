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

void Stack::new_turn()
{
    if(_has_perished)
    {
        set_action(Stack_Action::Skip);
        return;
    }
    
    if(true) // if creature is not blinded its status should be returned to default
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
    uint32_t num = get_number();     // amount of creatures in stack

    if(damage < hp_last)
    {
        set_hp_left(static_cast<uint16_t>(hp_last - damage));

        #if SHOW_DEBUG_INFO == 1
            printf( "%s has %d hp left.\n", _creature.get_name().c_str(), get_hp_left() );
        #endif

        return;
    }
    else if(damage == hp_last)
    {
        set_number(num - 1);
        if(get_number() == 0)
        {
            set_has_perished(true);
            printf( "%s has perished!\n", _creature.get_name().c_str() );

            set_action(Stack_Action::Skip);
            return;
        }
        set_hp_left(hp);
        printf( "One %s has perished!\n", _creature.get_name().c_str() );
        return;
    }
    else
    {
        uint64_t capacity = hp*(num - 1) + hp_last;

        if(damage >= capacity)
        {
            set_number(0);
            set_has_perished(true);
            printf( "The whole %s stack has perished!\n", _creature.get_name().c_str() );

            set_action(Stack_Action::Skip);
            return;
        }
        else
        {
            uint32_t initial_num = get_number();
            uint32_t new_num = static_cast<uint32_t>( (capacity - damage) / hp );

            set_hp_left( static_cast<uint16_t>( (capacity - damage) % hp ) );
            set_number(new_num);

            printf( "%d %s has perished!\n", initial_num - new_num, _creature.get_name().c_str() );

            #if SHOW_DEBUG_INFO == 1
                printf( "%s has %d hp left.\n", _creature.get_name().c_str(), get_hp_left() );
            #endif

            return;
        }
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

int8_t Stack::roll_luck()
{
    uint16_t probability;
    int8_t sign;

    switch(get_morale())
    {
        case Morale::Terrible : probability = 250; sign = -1; break;
        case Morale::Awful    : probability = 167; sign = -1; break;
        case Morale::Bad      : probability =  83; sign = -1; break;
        case Morale::Neutral  : probability =   0; sign =  0; break;
        case Morale::Good     : probability =  42; sign =  1; break;
        case Morale::Great    : probability =  83; sign =  1; break;
        case Morale::Superb   : probability = 125; sign =  1; break;
    }
    return sign*(rand() % 1000 < probability);
}

// void Stack::wait(){}

// void Stack::defend(){}

void Stack::move(uint8_t x, uint8_t y)
{
    uint8_t distance = std::abs(x - _pos.x) + std::abs(y - _pos.y);
    while(_creature.get_speed() < distance)
    {
        printf("%s have only %i speed and can't move that far. Pick a new position!", _creature.get_name());
    }
    _pos.x = x;
    _pos.y = y;
}

void Stack::attack(Stack& defender)
{
    if(get_team() == defender.get_team() /* && not berserk*/)
        return;

    if(defender.get_has_perished())
        return;

    if(!target(defender))
        return;
    
    uint8_t max_dmg = _creature.get_max_dmg();
    uint8_t min_dmg = _creature.get_min_dmg();
    
    uint32_t final_damage = 0;
    uint32_t base_damage = 0;

    bool melee_penalty = false;
    bool ranged_penalty = false;
    bool obstacle_penalty = false;

    float I1(0.f), I2(0.f), I3(0.f), I4(0.f), I5(0.f); // increase damage
    float R1(0.f), R2(0.f), R3(0.f), R4(0.f), R5(0.f), R6(0.f), R7(0.f), R8(0.f); // reduce damage

    // calculate I1
    if(get_att() >= defender.get_def())
        I1 = 0.05 * (get_att() - defender.get_def());

    // calculate I2 and I3
    if(_creature.get_is_ranged() && can_shoot())
    {
        // implement positioning, distance to target and adjacency
        switch(get_hero_level_of_archery())
        {
                case Skill_level::None :     I2 = 0.00f; break;
                case Skill_level::Basic :    I2 = 0.10f; break;
                case Skill_level::Advanced : I2 = 0.25f; break;
                case Skill_level::Expert :   I2 = 0.50f; break;
        }

        I3 = 0.05 * I2 * static_cast<int8_t>(get_hero_level_of_archery());
    }
    else // is ranged but has melee penalty or is not ranged
    {
        if(_creature.get_is_ranged() && !can_shoot())
            melee_penalty = true;
            
        switch(get_hero_level_of_offence())
        {
                case Skill_level::None :     I2 = 0.0f; break;
                case Skill_level::Basic :    I2 = 0.1f; break;
                case Skill_level::Advanced : I2 = 0.2f; break;
                case Skill_level::Expert :   I2 = 0.3f; break;
        }

        I3 = 0.05 * I2 * static_cast<int8_t>(get_hero_level_of_offence());
    }

    // calculate I4
    if     ( roll_luck() <  0 ) I4 = -0.5;
    else if( roll_luck() == 0 ) I4 =  0.0;
    else if( roll_luck() >  0 ) I4 =  1.0;
    
    // calculate I5
    // if death blow / hate / elements / jousting


    // calculate R1
    if( defender.get_def() >= get_att() && ( !_creature.get_is_ranged() || (_creature.get_is_ranged() && !can_shoot()) ) )
        R1 = 0.025 * (defender.get_def() - get_att());

    // calculate R2
    // if secondary skills

    // calculate R3
    // if secondary skills

    // calculate R4
    // if spells
    
    // calculate R5
    // if melee (half the damage from shooting) or ranged penalties (half the damage for shooting at distance greater than 10 hexes)

    // calculate R6
    // if obstacle penalties

    // calculate R7
    // if retaliation or attack after spell
    
    // calculate R8
    // if special abilities

    if(min_dmg == max_dmg)
        base_damage = min_dmg * get_number();
    else
    {
        uint8_t range = max_dmg - min_dmg + 1;
        
        if(get_number() <= 10)
            for(int i = 0; i < get_number(); i++)
                base_damage += rand() % range + min_dmg;
        else
        {
            for(int i = 0; i < 10; i++)
                base_damage += rand() % range + min_dmg;
            
            base_damage = base_damage * get_number()/10;
        }
    }

#if SHOW_DEBUG_INFO == 1
    printf( "\nDamage parameters:\n" );
    printf( "\t- I1 = %.3f\n\t- I2 = %.3f\n\t- I3 = %.3f\n\t- I4 = %.3f\n\t- I5 = %.3f\n", I1, I2, I3, I4, I5 );
    printf( "\t- R1 = %.3f\n\t- R2 = %.3f\n\t- R3 = %.3f\n\t- R4 = %.3f\n\t- R5 = %.3f\n\t- R6 = %.3f\n\t- R7 = %.3f\n\t- R8 = %.3f\n\n", R1, R2, R3, R4, R5, R6, R7, R8 );
#endif

    final_damage = static_cast<int32_t>( base_damage * (1 + I1 + I2 + I3 + I4 + I5) * (1 - R1) * (1 - R2 - R3) * (1 - R4) * (1 - R5) * (1 - R6) * (1 - R7) * (1 - R8) );
    
    printf("%s does %d damage to %s.\n", _creature.get_name().c_str(), final_damage, defender._creature.get_name().c_str());
    
    defender.recieve_damage(final_damage);

    //if defender is efreet sultan or has pell fire shield attacker and attacker is not immuned - attacker should recieve dmg
}

bool Stack::can_shoot()
{
    // if archer has arrows and no active enemy is in the way
    return true;
}

bool Stack::target(Stack& stack)
{
    // if attacker can reach defender
    return true;
}

void Stack::retaliate(Stack& attacker)
{
    // if not endless retaliation or spell check if already retaliated
}

void Stack::print_battle_info()
{
    auto c = _creature;
    printf("Name : %s\n", c.get_name().c_str());
    printf("Faction : %s\n", c.get_faction_as_string().c_str());
    printf("Level : %d\n", c.get_level());
    printf("Upgrade level : %d\n", c.get_upgrade());
    printf("Attack : %d(%d)\n", c.get_att(), get_att());
    printf("Defense : %d(%d)\n", c.get_def(), get_def());

    if(c.get_is_ranged())
        printf("Shots : %d(%d)\n", c.get_shots(), get_shots_left());
    
    printf("Damage : %d - %d\n", c.get_min_dmg(), c.get_max_dmg());
    printf("Health : %d(%d)\n", c.get_hp(), get_hp_left());
    printf("Morale : %d\n", c.get_morale());
    printf("Luck : %d\n", c.get_luck());

    if(c.get_special_abilities().length() != 0)
        printf("Special abilities : %s\n", c.get_special_abilities().c_str());
}

void Stack::print_full_info()
{
    auto c = _creature;
    printf("Name : %s\n", c.get_name().c_str());
    printf("Faction : %s\n", c.get_faction_as_string().c_str());
    printf("Level : %d\n", c.get_level());
    printf("Upgrade level : %d\n", c.get_upgrade());
    printf("Growth per week : %d\n", c.get_growth());
    printf("Attack : %d(%d)\n", c.get_att(), get_att());
    printf("Defense : %d(%d)\n", c.get_def(), get_def());

    if(c.get_is_ranged())
        printf("Shots : %d\n", c.get_shots());
    
    if(c.get_min_dmg() != c.get_max_dmg())
        printf("Damage : %d - %d\n", c.get_min_dmg(), c.get_max_dmg());
    else
        printf("Damage : %d\n", c.get_min_dmg());

    printf("Health : %d(%d)\n", get_hp_left(), get_hp());
    printf("Speed : %d(%d)\n", c.get_speed(), get_speed());
    printf("Morale : %d\n", c.get_morale());
    printf("Luck : %d\n", c.get_luck());
    printf("Fight value : %d\n", c.get_fight_value());
    printf("AI value : %d\n", c.get_ai_value());
    printf("%s", c.get_cost().c_str());

    if(c.get_special_abilities().length() != 0)
        printf("Special abilities : %s\n", c.get_special_abilities().c_str());
}

#endif