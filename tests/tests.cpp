#include <iostream>
#include <vector>
#include "tests.h"
#include "../utilities/types.h"
#include "../source/Creature_Stack.cpp"
#include "../source/Creature_List.cpp"
#include "../source/Hero_List.cpp"

void print_before_testing_output()
{
    std::cout << std::endl;
    std::cout << "=================== Welcome to the Heroes 3 testing grounds =================== " << std::endl;
}

void test_create_creature()
{
    std::string name = "Skellies";
    Faction faction = Faction::Necropolis;
    uint8_t level = 1;
    bool is_upgraded = false;
    uint8_t growth = 12;
    bool needs_2_hexes_in_battle = false;
    uint8_t att = 5;
    uint8_t def = 4;
    uint8_t shots = 20;
    uint8_t min_dmg = 1;
    uint8_t max_dmg = 3;
    uint16_t hp = 6;
    uint8_t speed = 4;
    Morale morale = Morale::Neutral;
    Luck luck = Luck::Neutral;
    uint16_t fight_value = 75;
    uint16_t ai_value = 60;
    uint32_t gold = 60;
    uint32_t mercury = 0;
    uint32_t sulfur = 0; 
    uint32_t crystal = 0;
    uint32_t gems = 0;
    bool is_undead = true;  
    bool is_unliving = false;
    bool is_flying = false;
    bool is_ranged = false;
    bool has_dragon_breath = false;
    bool has_attack_adjacent = false;
    
    Creature Skellies ( name, faction, level, is_upgraded, growth, needs_2_hexes_in_battle,
                        att, def, shots, min_dmg, max_dmg, hp, speed, morale, luck, fight_value, ai_value, 
                        { gold, mercury, sulfur, crystal, gems },
                        is_undead, is_unliving, is_flying, is_ranged, has_dragon_breath, has_attack_adjacent );

    print_before_testing_output();
    Skellies.print_full_info();

    Creature& ref = Skellies;
    Creature* ptr = &Skellies;

    Creature Boney_Bois(ref);
    if(Boney_Bois.get_name() != Skellies.get_name())
    {
        std::cout << "Constructing by reference does not work!"<< std::endl;
        abort();
    }

    Creature Calcium_Daddies(ptr);
    if(Calcium_Daddies.get_name() != Skellies.get_name())
    {
        std::cout << "Constructing by pointer does not work!"<< std::endl;
        abort();
    }
}

void test_create_creature_stack()
{
    print_before_testing_output();

    Stack* army[ARMY_SLOTS] = {nullptr};

    for(int i = 0; i < ARMY_SLOTS; i++)
    {
        army[i] = new Stack(Creature_List::Skeleton_Warrior, 50 + i);
        std::cout << "Stack " << i << " name is : " << army[i]->get_creature().get_name() << std::endl;
        std::cout << "Stack " << i << " number is : " << army[i]->get_number() << std::endl;
    }
}

void test_creature_stack_vs_creature_stack()
{
    print_before_testing_output();

    Stack attacker(Creature_List::Lich, 10, Team::Red);
    // Stack attacker(Creature_List::Ghost_Dragon, 1, Team::Red);
    std::cout << attacker.get_team_as_string() << " stack is comprised of : " << attacker.get_number() << " " << attacker.get_creature().get_name() << std::endl;

    // Stack defender(Creature_List::Skeleton, 1, Team::Blue);
    Stack defender(Creature_List::Ghost_Dragon, 1, Team::Blue);
    std::cout << defender.get_team_as_string() << " stack is comprised of : " << defender.get_number() << " " << defender.get_creature().get_name() << std::endl;

    attacker.attack(defender);
}