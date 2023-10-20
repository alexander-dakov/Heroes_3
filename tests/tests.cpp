#include <iostream>
#include "tests.h"

void print_before_testing_output()
{
    std::cout << std::endl << std::flush;
    std::cerr << std::endl << std::flush;
    printf( "=================== Welcome to the Heroes 3 testing grounds =================== \n" );
}

void print_some_special_abilities(Creature* c)
{
    printf( "\nLets see which of these special abilities the unit has.\n" );
    printf( "%s :\n", c->get_name().c_str() );
    printf( " - is undead : %s\n", c->get_is_undead() ? "true" : "false" );
    printf( " - is non-living : %s\n", c->get_is_bloodless() ? "true" : "false" );
    printf( " - is ranged : %s\n", c->get_is_ranged() ? "true" : "false" );
    printf( " - is flying : %s\n", c->get_is_flying() ? "true" : "false" );
    printf( " - has double attack : %s\n", c->get_has_double_attack() ? "true" : "false" );
    printf( c->get_ignore_enemy_defense() ? " - ignores enemy defense by : %d%\n"         : " - ignores enemy defense : false\n",         c->get_ignore_enemy_defense_by_percent() );
    printf( c->get_ignore_enemy_attack()  ? " - ignores enemy attack by : %d%\n"          : " - ignores enemy attack : false\n",          c->get_ignore_enemy_attack_by_percent()  );
    printf( c->get_reduce_magic_damage()  ? " - recieves reduced spell damage by : %d%\n" : " - recieves reduced spell damage : false\n", c->get_reduce_magic_damage_by_percent()  );
    printf( c->get_has_magic_resist()     ? " - chance to resist magic damage : %d%\n"    : " - chance to resist magic damage : false\n", c->get_has_magic_resist_by_percent()     );
    printf( " - is immune to magic arrow : %s\n", c->get_is_immune_to_magic_arrow() ? "true" : "false");
    printf( " - is immune to fire spells : %s\n", c->get_is_immune_to_fire_spells() ? "true" : "false");
    printf( " - number of casts : %d\n", c->get_number_of_casts());
    printf( " - spell power : %d\n", c->get_spell_power());
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

    print_some_special_abilities(&Skellies);

    Creature& ref = Skellies;
    Creature* ptr = &Skellies;

    Creature Boney_Bois(ref);
    if( Boney_Bois.get_name() != Skellies.get_name() )
    {
        std::cerr << "Constructing by reference does not work!"<< std::endl;
        abort();
    }

    Creature Calcium_Daddies(ptr);
    if( Calcium_Daddies.get_name() != Skellies.get_name() )
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
    print_some_special_abilities(army[0]->get_creature());
}

void test_creature_stack_vs_creature_stack()
{
    print_before_testing_output();

    // Stack attacker(Creature_List::Lich, 10, Team::Red);
    Stack attacker(Creature_List::Angel, 1, Team::Red);
    printf( "%s stack is comprised of : %d %s\n", attacker.get_team_as_string().c_str(), attacker.get_number(), attacker.get_creature()->get_name().c_str() );

    Stack defender(Creature_List::Skeleton, 50, Team::Blue);
    // Stack defender(Creature_List::Ghost_Dragon, 1, Team::Blue);
    printf( "%s stack is comprised of : %d %s\n", defender.get_team_as_string().c_str(), defender.get_number(), defender.get_creature()->get_name().c_str() );

    // TO DO : all special abilities have to be added in : attack(), defend(), recieve_damage()
    attacker.attack(defender);

    defender.attack(attacker);
}

void test_create_item()
{
    print_before_testing_output();

    std::string name = "BFG";
    Slot slot = Slot::Weapon;
    Type item_type = Type::Relic;
    uint32_t gold = 10000;
    uint32_t mercury = 0;
    uint32_t sulfur = 0; 
    uint32_t crystal = 0;
    uint32_t gems = 0;
    Resources resources = {gold, mercury, sulfur, crystal, gems};
    std::string effect = "Attack skill +12.";

    Item BFG(name, slot, item_type, resources, effect);

    BFG.print_full_info();
}

void test_create_hero()
{
    print_before_testing_output();

    std::string name = "Orrinman";
    Gender gender = Gender::Male;
    Role hero_role = Role::Might;
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

    Hero Orrinman( name, gender, hero_role, faction, team, level, experience, 
        attack, defense, power, knowledge,
        specialty,
        morale, luck,
        // secondary skills
        { has_first_aid, has_ammo_cart, has_ballista, has_catapult },
        has_spellbook );

    Orrinman.print_full_info();
}

void test_hero_item_bonuses()
{
    Hero& hero = Hero_List::Orrin; // second hero should modify army

    // Helmet
    hero.pick_up_item(&Item_List::Helm_of_Heavenly_Enlightenment);    // primary +6

    // Cape
    // hero.pick_up_item(&Item_List::Dragon_Wing_Tabard);                // power +2, knowledge +2

    // Necklace
    // hero.pick_up_item(&Item_List::Necklace_of_Dragonteeth);           // power +3, knowledge +3

    // Weapon
    hero.pick_up_item(&Item_List::Sword_of_Judgement);                // primary +5

    // Shield
    hero.pick_up_item(&Item_List::Sentinels_Shield);                  // defense +12, attack -3

    // Armor
    hero.pick_up_item(&Item_List::Titans_Cuirass);                    // power +10, knowledge -2

    // Hand
    // hero.pick_up_item(&Item_List::Quiet_Eye_of_the_Dragon);           // attack +1, defense +1
    // hero.pick_up_item(&Item_List::Equestrians_Gloves);                // movement points +200

    // Boots
    hero.pick_up_item(&Item_List::Sandals_of_the_Saint);              // primary +2

    // Pocket
    // hero.pick_up_item(&Item_List::Crest_of_Valor);                    // morale +1
    // hero.pick_up_item(&Item_List::Cards_of_Prophecy);                 // luck +1
    
    hero.print_full_info();

    hero.unequip_item(&Item_List::Helm_of_Heavenly_Enlightenment);    // primary +6

    hero.print_full_info();

    hero.print_equipped_items();
    hero.print_unequipped_items();

    hero.print_full_info();

    hero.add_experience(5000);
    
    hero.print_full_info();
}

void test_army_hero_bonuses()
{
    print_before_testing_output();

    Hero& first_hero  = Hero_List::None;  // should not modify army
    Hero& second_hero = Hero_List::Orrin; // should modify army

    first_hero.print_full_info();
    second_hero.print_full_info();

    // Helmet
    second_hero.pick_up_item(&Item_List::Helm_of_Heavenly_Enlightenment);    // primary +6

    // Cape
    second_hero.pick_up_item(&Item_List::Cape_of_Velocity);                  // unit speed +2

    // Necklace
    second_hero.pick_up_item(&Item_List::Necklace_of_Swiftness);             // unit speed +3

    // Weapon
    second_hero.pick_up_item(&Item_List::Sword_of_Judgement);                // primary +5

    // Shield
    second_hero.pick_up_item(&Item_List::Sentinels_Shield);                  // defense +12, attack -3

    // Armor
    second_hero.pick_up_item(&Item_List::Titans_Cuirass);                    // power +10, knowledge -2

    // Hand
    second_hero.pick_up_item(&Item_List::Ring_of_Wayfarer);                  // unit speed +1
    // second_hero.pick_up_item(&Item_List::Ring_of_Vitality);               // unit hp +1
    second_hero.pick_up_item(&Item_List::Ring_of_Life);                      // unit hp +1

    // Boots
    second_hero.pick_up_item(&Item_List::Sandals_of_the_Saint);              // primary +2

    // Pocket
    second_hero.pick_up_item(&Item_List::Vial_of_Lifeblood);                 // unit hp +2
    // second_hero.pick_up_item(&Item_List::Elixir_of_Life); // unit hp + 4 + 25% of base hp + regeneration per round

    second_hero.unequip_item(&Item_List::Helm_of_Heavenly_Enlightenment);    // primary +6
    
    second_hero.print_full_info();

    // fill an army with the same units
    Stack* army[ARMY_SLOTS] = {nullptr};

    for(int i = 0; i < ARMY_SLOTS; i++)
    {
        army[i] = new Stack(Creature_List::Marksman, i + 1);
        printf( "Stack %d is comprised of : %d %s\n", i + 1, army[i]->get_number(), army[i]->get_creature()->get_name().c_str() );
    }
    // Print stats of part of the army
    printf( "\nFirst and last stacks of army without hero :\n" );
    army[0]->print_full_info();
    printf("\n");
    army[ARMY_SLOTS - 1]->print_full_info();
   
    // Assign the army to second hero
    for(int i = 0; i < ARMY_SLOTS; i++)
        second_hero.add_stack_to_slot(army[i], i);
    // Print stats of part of the army
    printf( "\nFirst and last stacks of army lead by hero %s :\n", second_hero.get_name().c_str() );
    army[0]->print_full_info();
    printf("\n");
    army[ARMY_SLOTS - 1]->print_full_info();

    // Hero equips an item to boost army
    second_hero.equip_item_from_chest(&Item_List::Helm_of_Heavenly_Enlightenment);    // primary +6
    // Print stats of part of the army
    printf( "\nFirst and last stacks of army lead by hero %s :\n", second_hero.get_name().c_str() );
    army[0]->print_full_info();
    printf("\n");
    army[ARMY_SLOTS - 1]->print_full_info();

    // Remove army from hero
    for(int i = 0; i < ARMY_SLOTS; i++)
        second_hero.remove_stack_from_position(i);
    // Print stats of part of the army
    printf( "\nFirst and last stacks of army without hero :\n" );
    army[0]->print_full_info();
    printf("\n");
    army[ARMY_SLOTS - 1]->print_full_info();

    // Assign army to first hero
    for(int i = 0; i < ARMY_SLOTS; i++)
        first_hero.add_stack_to_slot(army[i], i);
    // Print stats of part of the army
    printf( "\nFirst and last stacks of army lead by hero %s :\n", first_hero.get_name().c_str() );
    army[0]->print_full_info();
    printf("\n");
    army[ARMY_SLOTS - 1]->print_full_info();
}

void test_hero_vs_creature_stack()
{
    print_before_testing_output();

    Hero& hero = Hero_List::Crag_Hack; // should modify army
    
    hero.set_attack(5);
    hero.set_defense(5);

    // hero.equip_item(&Item_List::Ring_of_Vitality);  // unit hp +1
    // hero.equip_item(&Item_List::Ring_of_Life);      // unit hp +1
    // hero.equip_item(&Item_List::Vial_of_Lifeblood); // unit hp +2

    // hero.equip_item(&Item_List::Elixir_of_Life); // unit hp + 4 + 25% of base hp + regeneration per round

    hero.print_full_info();

    // Stack attacker(Creature_List::Lich, 10, Team::Red);
    Stack attacker(Creature_List::Angel, 1, Team::Red);
    hero.add_stack_to_army(&attacker);
    printf( "Hero %s is leading the %s stack, comprised of : %d %s\n", hero.get_name().c_str(), attacker.get_team_as_string().c_str(), attacker.get_number(), attacker.get_creature()->get_name().c_str() );
    attacker.print_full_info();

    printf("\n");

    // Stack defender(Creature_List::Skeleton, 20, Team::Blue);
    Stack defender(Creature_List::Ghost_Dragon, 1, Team::Blue);
    printf( "%s stack is comprised of : %d %s\n", defender.get_team_as_string().c_str(), defender.get_number(), defender.get_creature()->get_name().c_str() );
    defender.print_full_info();

    // TO DO : all special abilities have to be added in : attack(), defend(), recieve_damage()

    // to imitate a battle field, the troops must have positions
    attacker.set_position(0, 0);
    defender.set_position(1, 0);

    attacker.attack(defender);

    defender.attack(attacker);
}