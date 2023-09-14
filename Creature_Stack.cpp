#include "Creature_Stack.h"

Stack::Stack(const Hero& hero, const Creature creature, const uint32_t number, const uint8_t pos_x, const uint8_t pos_y) :
             _hero(hero), _creature(creature), _number(number), _pos(pos_x, pos_y),
             battle_stats(creature, hero),
             hero_specialty_and_secondary_skills(hero)
             {
                _team = _hero.get_team();
             };

Stack::Stack(const Creature creature, const uint32_t number, const uint8_t pos_x, const uint8_t pos_y) :
             _creature(creature), _number(number), _pos(pos_x, pos_y),
             battle_stats(creature), 
             hero_specialty_and_secondary_skills()
             {};

Stack::Stack(const Creature creature, const uint32_t number) :
             _creature(creature), _number(number),
             battle_stats(creature),
             hero_specialty_and_secondary_skills()
             {};

Stack::~Stack()
{
    // std::cout << "Stack destroyed!" << std::endl;
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

}

void Stack::recieve_damage(uint32_t damage)
{
    uint8_t hp = get_hp(); // hp per unit
    uint8_t hp_last = get_hp_left(); // hp of last unit
    uint32_t num = get_number(); // amount of creatures in stack

    if(damage < hp_last)
    {
        set_hp_left(hp_last - damage);
        return;
    }
    else if(damage == hp_last)
    {
        set_number(num - 1);
        if(get_number() == 0)
        {
            set_has_perished(true);
            set_action(Stack_Action::Skip);
            return;
        }
        set_hp_left(hp);
        return;
    }
    else
    {
        uint64_t capacity = hp*(num - 1) + hp_last;

        if(damage >= capacity)
        {
            set_number(0);
            set_has_perished(true);
            set_action(Stack_Action::Skip);
            return;
        }
        else
        {
            set_hp_left(capacity % damage);
            set_number(capacity / damage);
            return;
        }
    }
}

bool Stack::roll_negative_morale()
{
    uint16_t probability;

    switch (get_morale())
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

    switch (get_morale())
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

    switch (get_morale())
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
    
    uint32_t final_damage;
    uint32_t base_damage;

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
        switch (get_level_of_archery())
        {
                case Skill_level::None :     I2 = 0.00f; break;
                case Skill_level::Basic :    I2 = 0.10f; break;
                case Skill_level::Advanced : I2 = 0.25f; break;
                case Skill_level::Expert :   I2 = 0.50f; break;
        }

        I3 = 0.05 * I2 * static_cast<int8_t>(get_level_of_archery());
    }
    else // is ranged but has melee penalty or is not ranged
    {
        if(_creature.get_is_ranged() && !can_shoot())
            melee_penalty = true;
        switch (get_level_of_offence())
        {
                case Skill_level::None :     I2 = 0.0f; break;
                case Skill_level::Basic :    I2 = 0.1f; break;
                case Skill_level::Advanced : I2 = 0.2f; break;
                case Skill_level::Expert :   I2 = 0.3f; break;
        }

        I3 = 0.05 * I2 * static_cast<int8_t>(get_level_of_offence());
    }

    // calculate I4
    if     ( roll_luck() <  0 ) I4 = -0.5;
    else if( roll_luck() == 0 ) I4 =  0.0;
    else if( roll_luck() >  0 ) I4 =  1.0;
    
    // calculate I5
    // if death blow / hate / elements / jousting


    // calculate R1
    if(defender.get_def() >= get_att())
        R1 = 0.25 * (defender.get_def() - get_att());

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

    final_damage = static_cast<int32_t>( base_damage * (1 + I1 + I2 + I3 + I4 + I5) * (1 - R1) * (1 - R2 - R3) * (1 - R4) * (1 - R5) * (1 - R6) * (1 - R7) * (1 - R8) );

    defender.recieve_damage(final_damage);
}

void Stack::print_full_info()
{
    auto c = _creature;
    printf("Name : %s\n", c.get_name().c_str());
    printf("Faction : %s\n", c.get_faction_as_string().c_str());
    printf("Level : %d\n", c.get_level());
    printf("Upgraded : %d\n", c.get_is_upgraded());
    printf("Growth per week : %d\n", c.get_growth());
    printf("Attack : %d(%d)\n", c.get_att());
    printf("Defence : %d(%d)\n", c.get_def());

    if(c.get_is_ranged())
        printf("Shots : %d(%d)\n", c.get_shots(), get_shots_left());
    
    printf("Damage : %d - %d\n", c.get_min_dmg(), c.get_max_dmg());
    printf("Health : %d(%d)\n", c.get_hp(), get_hp_left());
    printf("Morale : %d\n", c.get_morale());
    printf("Luck : %d\n", c.get_luck());
    printf("Fight value : %d\n", c.get_fight_value());
    printf("AI value : %d\n", c.get_ai_value());
    printf("%s", c.get_cost().c_str());

    if(c.get_special_abilities().length() != 0)
        printf("Special abilities : %s\n", c.get_special_abilities().c_str());
}

// void Stack::print_full_info(Stack& stack)
// {
//     auto s = stack._creature;
//     printf("Name : %s\n", s.get_name().c_str());
//     printf("Faction : %s\n", s.get_faction_as_string().c_str());
//     printf("Level : %d\n", s.get_level());
//     printf("Upgraded : %d\n", s.get_is_upgraded());
//     printf("Growth per week : %d\n", s.get_growth());
//     printf("Attack : %d(%d)\n", s.get_att());
//     printf("Defence : %d(%d)\n", s.get_def());

//     if(s.get_is_ranged())
//         printf("Shots : %d(%d)\n", s.get_shots(), stack.get_shots_left());
    
//     printf("Damage : %d - %d\n", s.get_min_dmg(), s.get_max_dmg());
//     printf("Health : %d(%d)\n", s.get_hp(), stack.get_hp_left());
//     printf("Morale : %d\n", s.get_morale());
//     printf("Luck : %d\n", s.get_luck());
//     printf("Fight value : %d\n", s.get_fight_value());
//     printf("AI value : %d\n", s.get_ai_value());
//     printf("%s", s.get_cost().c_str());

//     if(s.get_special_abilities().length() != 0)
//         printf("Special abilities : %s\n", s.get_special_abilities().c_str());
// }