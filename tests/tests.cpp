#include <iostream>
#include "utilities/types.h"
#include "Creatures/Creature_Stack.h"
#include "Creatures/Creature_List.h"
#include "Heroes/Hero_List.h"

void print_before_testing_output()
{
    std::cout << std::endl;
    std::cout << "============================== Welcome to the Heroes 3 testing grounds ==============================" << std::endl;
}

void test_create_creature()
{
    std::string name = "Skellies";
    Faction faction = Faction::Necropolis;
    uint8_t level = 1;
    bool is_upgraded = false;
    uint8_t growth = 12;
    Morale morale = Morale::Neutral;
    Luck luck = Luck::Neutral;
    bool needs_2_hexes_in_battle = false;
    uint8_t att = 5;
    uint8_t def = 4;
    uint8_t shots = 20;
    uint8_t min_dmg = 1;
    uint8_t max_dmg = 3;
    uint8_t hp = 6;
    uint8_t speed = 4;
    uint8_t fight_value = 75;
    uint8_t ai_value = 60;
    uint8_t gold = 60;
    uint8_t mercury = 0;
    uint8_t sulfur = 0; 
    uint8_t crystal = 0;
    uint8_t gems = 0;
    bool is_undead = true;  
    bool is_unliving = false;
    bool is_flying = false;
    bool is_ranged = false;
    bool has_dragon_breath = false;
    bool has_attack_adjacent = false;
    
    Creature Skellies ( name, faction, level, is_upgraded, growth, morale, luck, needs_2_hexes_in_battle,
                        att, def, shots, min_dmg, max_dmg, hp, speed, fight_value, ai_value, 
                        { gold, mercury, sulfur, crystal, gems },
                        is_undead, is_unliving, is_flying, is_ranged, has_dragon_breath, has_attack_adjacent );

    print_before_testing_output();
    Skellies.print_full_info();

    Creature& ref = Skellies;
    Creature* ptr = &Skellies;

    Creature Bonie_Bois(ref);
    if(Bonie_Bois.get_name() != Skellies.get_name())
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

    #define CONCAT(id1, id2) id1##id2

    for(int i = 0; i < 8; i++)
    {
        Stack CONCAT(stack_, i)(Creature_List::Skeleton_Warrior, 50 + i);
        CONCAT(stack_, i).get_number();
        std::cout << std::endl;
    }
}