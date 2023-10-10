#include <iostream>
#include "tests.h"
#include "../utilities/types.h"
#include "../source/Creature_Stack.cpp"
#include "../source/Creature_List.cpp"
#include "../source/Hero_List.cpp"
#include "../source/Item_List.cpp"

void print_before_testing_output()
{
    std::cout << std::endl << std::flush;
    std::cerr << std::endl << std::flush;
    std::cout << std::endl << "=================== Welcome to the Heroes 3 testing grounds =================== " << std::endl;
}

void test_create_creature()
{
    print_before_testing_output();

    std::string name = "Skellies";
    Faction faction = Faction::Necropolis;
    uint8_t level = 1;
    Upgrade_level upgrade = Upgrade_level::None;
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
    std::string special_abilities = "Undead.";
    
    Creature Skellies ( name, faction, level, upgrade, growth, needs_2_hexes_in_battle,
                        att, def, shots, min_dmg, max_dmg, hp, speed, morale, luck, fight_value, ai_value, 
                        { gold, mercury, sulfur, crystal, gems }, 
                        special_abilities );

    Skellies.print_full_info();

    printf( "\nLets see only some of the many special abilities\n" );
    printf( "%s :\n", Skellies.get_name().c_str() );
    printf( " - is undead : %s\n", Skellies.get_is_undead() ? "true" : "false" );
    printf( " - is non-living : %s\n", Skellies.get_is_bloodless() ? "true" : "false" );
    printf( " - is ranged : %s\n", Skellies.get_is_ranged() ? "true" : "false" );
    printf( " - is flying : %s\n", Skellies.get_is_flying() ? "true" : "false" );
    printf( " - has double attack : %s\n", Skellies.get_has_double_attack() ? "true" : "false" );
    printf( " - is immune to magic arrow : %s\n", Skellies.get_is_immune_to_magic_arrow() ? "true" : "false");
    printf( " - is immune to fire spells : %s\n", Skellies.get_is_immune_to_fire_spells() ? "true" : "false");
    printf( " - number of casts : %d\n", Skellies.get_number_of_casts());
    printf( " - spell power : %d\n", Skellies.get_spell_power());

    Creature& ref = Skellies;
    Creature* ptr = &Skellies;

    Creature Boney_Bois(ref);
    if(Boney_Bois.get_name() != Skellies.get_name())
    {
        std::cerr << "Constructing by reference does not work!"<< std::endl;
        abort();
    }

    Creature Calcium_Daddies(ptr);
    if(Calcium_Daddies.get_name() != Skellies.get_name())
    {
        std::cerr << "Constructing by pointer does not work!"<< std::endl;
        abort();
    }
}

void test_create_creature_stack()
{
    print_before_testing_output();

    Stack* army[ARMY_SLOTS] = {nullptr};

    for(int i = 0; i < ARMY_SLOTS; i++)
    {
        army[i] = new Stack(Creature_List::Master_Genie, 50 + i);
        printf( "Stack %d is comprised of : %d %s\n", i + 1, army[i]->get_number(), army[i]->get_creature()->get_name().c_str() );
    }
    printf( "\n" );
    army[0]->print_full_info();
    printf( "\nLets see only some of the many special abilities\n" );
    auto c = army[0]->get_creature();
    printf( "%s :\n", c->get_name().c_str() );
    printf( " - is undead : %s\n", c->get_is_undead() ? "true" : "false" );
    printf( " - is non-living : %s\n", c->get_is_bloodless() ? "true" : "false" );
    printf( " - is ranged : %s\n", c->get_is_ranged() ? "true" : "false" );
    printf( " - is flying : %s\n", c->get_is_flying() ? "true" : "false" );
    printf( " - has double attack : %s\n", c->get_has_double_attack() ? "true" : "false" );
    printf( " - is immune to magic arrow : %s\n", c->get_is_immune_to_magic_arrow() ? "true" : "false");
    printf( " - is immune to fire spells : %s\n", c->get_is_immune_to_fire_spells() ? "true" : "false");
    printf( " - number of casts : %d\n", c->get_number_of_casts());
    printf( " - spell power : %d\n", c->get_spell_power());
}

void test_creature_stack_vs_creature_stack()
{
    print_before_testing_output();

    // Stack attacker(Creature_List::Lich, 10, Team::Red);
    Stack attacker(Creature_List::Angel, 1, Team::Red);
    printf( "%s stack is comprised of : %d %s\n", attacker.get_team_as_string().c_str(), attacker.get_number(), attacker.get_creature()->get_name().c_str() );

    // Stack defender(Creature_List::Skeleton, 20, Team::Blue);
    Stack defender(Creature_List::Ghost_Dragon, 1, Team::Blue);
    printf( "%s stack is comprised of : %d %s\n", defender.get_team_as_string().c_str(), defender.get_number(), defender.get_creature()->get_name().c_str() );

    // all special abilities have to be added in : attack(), defend(), recieve_damage()
    attacker.attack(defender);
}

void test_create_hero()
{
    print_before_testing_output();

    std::string name = "Orrinman";
    Gender gender = Gender::Male;
    Class hero_class = Class::Might;
    Faction faction = Faction::Castle;
    Team team = Team::Red;
    uint8_t level = 1;
    uint32_t experience = 0;
    uint8_t attack = 2;
    uint8_t defense = 2;
    uint8_t power = 1;
    uint8_t knowledge = 1;
    Specialty& specialty = Specialty_List::Archery;
    Morale morale = Morale::Neutral;
    Luck luck = Luck::Neutral;
    bool has_first_aid = false;
    bool has_ammo_cart = false;
    bool has_ballista = false;
    bool has_catapult = false;
    bool has_spellbook = false;

    Hero Orrinman( name, gender, hero_class, faction, team, level, experience, 
        attack, defense, power, knowledge,
        specialty,
        morale, luck,
        // secondary skills
        { has_first_aid, has_ammo_cart, has_ballista, has_catapult },
        has_spellbook );

    Orrinman.print_full_info();
}


void test_hero_army_bonuses()
{
    print_before_testing_output();

    Hero& Someone = Hero_List::Someone; // should not modify army
    Hero& Orrin = Hero_List::Orrin; // should modify army
    
    Orrin.set_attack(5);
    Orrin.set_defense(5);

    // Someone.equip_item(Item_List::Ring_of_Wayfarer);  // unit speed +1
    // Someone.equip_item(Item_List::Ring_of_Life);      // unit hp +1
    // Someone.equip_item(Item_List::Vial_of_Lifeblood); // unit hp +2

    // Orrin.equip_item(Item_List::Ring_of_Vitality);  // unit hp +1
    // Orrin.equip_item(Item_List::Ring_of_Life);      // unit hp +1
    // Orrin.equip_item(Item_List::Vial_of_Lifeblood); // unit hp +2

    // Orrin.equip_item(Item_List::Elixir_of_Life); // unit hp + 4 + 25% of base hp + regeneration per round

    // fill an army with the same units
    Stack* army[ARMY_SLOTS] = {nullptr};

    for(int i = 0; i < ARMY_SLOTS; i++)
    {
        army[i] = new Stack(Creature_List::Marksman, i + 1);
        printf( "Stack %d is comprised of : %d %s\n", i + 1, army[i]->get_number(), army[i]->get_creature()->get_name().c_str() );
    }
    printf( "\nFirst and last stacks of army without hero :\n" );
    army[0]->print_full_info();
    printf("\n");
    army[ARMY_SLOTS - 1]->print_full_info();
   
    for(int i = 0; i < ARMY_SLOTS; i++)
        Someone.add_stack_to_slot(army[i], i);

    printf( "\nFirst and last stacks of army lead by hero %s :\n", Someone.get_name().c_str() );
    army[0]->print_full_info();
    printf("\n");
    army[ARMY_SLOTS - 1]->print_full_info();

    for(int i = 0; i < ARMY_SLOTS; i++)
        Orrin.add_stack_to_slot(army[i], i);
        
    printf( "\nFirst and last stacks of army lead by hero %s :\n", Orrin.get_name().c_str() );
    army[0]->print_full_info();
    printf("\n");
    army[ARMY_SLOTS - 1]->print_full_info();
}

void test_hero_vs_creature_stack()
{
    print_before_testing_output();

    Hero& Orrin = Hero_List::Orrin; // should modify army
    
    Orrin.set_attack(5);
    Orrin.set_defense(5);

    // Orrin.equip_item(Item_List::Ring_of_Vitality);  // unit hp +1
    // Orrin.equip_item(Item_List::Ring_of_Life);      // unit hp +1
    // Orrin.equip_item(Item_List::Vial_of_Lifeblood); // unit hp +2

    // Orrin.equip_item(Item_List::Elixir_of_Life); // unit hp + 4 + 25% of base hp + regeneration per round

    // Stack attacker(Creature_List::Lich, 10, Team::Red);
    Stack attacker(Creature_List::Angel, 1, Team::Red);
    Orrin.add_stack_to_army(&attacker);
    printf( "Hero %s is leading the %s stack, comprised of : %d %s\n", Orrin.get_name().c_str(), attacker.get_team_as_string().c_str(), attacker.get_number(), attacker.get_creature()->get_name().c_str() );
    attacker.print_full_info();

    printf("\n");

    // Stack defender(Creature_List::Skeleton, 20, Team::Blue);
    Stack defender(Creature_List::Ghost_Dragon, 1, Team::Blue);
    printf( "%s stack is comprised of : %d %s\n", defender.get_team_as_string().c_str(), defender.get_number(), defender.get_creature()->get_name().c_str() );
    defender.print_full_info();

    // all special abilities have to be added in : attack(), defend(), recieve_damage()
    attacker.attack(defender);
}