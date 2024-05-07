#include "Hero.h"

Hero::Hero( const std::string name, const Gender gender, const Role hero_role, const Faction faction, const Team team, const uint8_t level, const uint32_t experience, 
            const uint8_t attack, const uint8_t defense, const uint8_t power, const uint8_t knowledge,
            const Specialty& specialty,
            const Morale morale, const Luck luck,
            // secondary skills
            const struct war_machines war_machinery,
            const bool has_spellbook ) :
            _name(name), _gender(gender), _role(hero_role), _faction(faction), _team(team), _level(level), _experience(experience), 
            primary_skills(attack, defense, power, knowledge),
            _specialty(specialty),
            _morale(morale), _luck(luck),
            // {"None", ...} write them in some way and change field in Hero.h,
            war_machines(war_machinery),
            _has_spellbook(has_spellbook)
{
      switch(_faction)
      {
            case Faction::Castle     : get_role() ? _class = Class::Cleric       : _class = Class::Knight;       break;
            case Faction::Rampart    : get_role() ? _class = Class::Druid        : _class = Class::Ranger;       break;
            case Faction::Tower      : get_role() ? _class = Class::Wizard       : _class = Class::Alchemist;    break;
            case Faction::Inferno    : get_role() ? _class = Class::Heretic      : _class = Class::Demoniac;     break;
            case Faction::Necropolis : get_role() ? _class = Class::Necromancer  : _class = Class::Death_Knight; break;
            case Faction::Dungeon    : get_role() ? _class = Class::Warlock      : _class = Class::Overlord;     break;
            case Faction::Stronghold : get_role() ? _class = Class::Battle_Mage  : _class = Class::Barbarian;    break;
            case Faction::Fortress   : get_role() ? _class = Class::Witch        : _class = Class::Beastmaster;  break;
            case Faction::Conflux    : get_role() ? _class = Class::Elementalist : _class = Class::Planeswalker; break;
            case Faction::Cove       : get_role() ? _class = Class::Navigator    : _class = Class::Captain;      break;
      }
      _mana = knowledge*10;
      _mana_left = _mana;
      _movement_points = 1560; // TO DO : implement movement points according to army
}

Hero::~Hero()
{
      // printf( "Hero %s destroyed!\n", get_name().c_str() );
}

std::string Hero::get_gender_as_string()
{
      if( get_gender() == Gender::Male )  
            return "Male";
      return "Female";
}

std::string Hero::get_role_as_string()
{
      std::string hero_role;

      switch(get_role())
      {
            case Role::Might : hero_role = "Might"; break;
            case Role::Magic : hero_role = "Magic"; break;
      }

      return hero_role;
}

std::string Hero::get_class_as_string()
{
      std::string hero_class;

      switch(get_class())
      {
            case Class::Knight       : hero_class = "Knight";       break;
            case Class::Cleric       : hero_class = "Cleric";       break;
            case Class::Ranger       : hero_class = "Ranger";       break;
            case Class::Druid        : hero_class = "Druid";        break;
            case Class::Alchemist    : hero_class = "Alchemist";    break;
            case Class::Wizard       : hero_class = "Wizard";       break;
            case Class::Demoniac     : hero_class = "Demoniac";     break;
            case Class::Heretic      : hero_class = "Heretic";      break;
            case Class::Death_Knight : hero_class = "Death_Knight"; break;
            case Class::Necromancer  : hero_class = "Necromancer";  break;
            case Class::Overlord     : hero_class = "Overlord";     break;
            case Class::Warlock      : hero_class = "Warlock";      break;
            case Class::Barbarian    : hero_class = "Barbarian";    break;
            case Class::Battle_Mage  : hero_class = "Battle_Mage";  break;
            case Class::Beastmaster  : hero_class = "Beastmaster";  break;
            case Class::Witch        : hero_class = "Witch";        break;
            case Class::Planeswalker : hero_class = "Planeswalker"; break;
            case Class::Elementalist : hero_class = "Elementalist"; break;
            case Class::Captain      : hero_class = "Captain";      break;
            case Class::Navigator    : hero_class = "Navigator";    break;
      }

      return hero_class;
}

std::string Hero::get_faction_as_string()
{
      std::string faction;

      switch(get_faction())
      {
            case Faction::Neutral    : faction = "Neutral";    break;
            case Faction::Castle     : faction = "Castle";     break;
            case Faction::Rampart    : faction = "Rampart";    break;
            case Faction::Tower      : faction = "Tower";      break;
            case Faction::Inferno    : faction = "Inferno";    break;
            case Faction::Necropolis : faction = "Necropolis"; break;
            case Faction::Dungeon    : faction = "Dungeon";    break;
            case Faction::Stronghold : faction = "Stronghold"; break;
            case Faction::Fortress   : faction = "Fortress";   break;
            case Faction::Conflux    : faction = "Conflux";    break;
            case Faction::Cove       : faction = "Cove";       break;
      }

      return faction;
}

std::string Hero::get_team_as_string()
{
      std::string team;

      switch(get_team())
      {
            case Team::Neutral : team = "Neutral"; break;
            case Team::Red     : team = "Red";     break;
            case Team::Blue    : team = "Blue";    break;
            case Team::Tan     : team = "Tan";     break;
            case Team::Green   : team = "Green";   break;
            case Team::Orange  : team = "Orange";  break;
            case Team::Purple  : team = "Purple";  break;
            case Team::Teal    : team = "Teal";    break;
            case Team::Pink    : team = "Pink";    break;
      }

      return team;
}

void Hero::add_level(const uint8_t level)
{
      if( get_level() == 75 )
      {
            printf( "\n%s has reached max level!\n", get_name() );
            return;
      }

      set_level( get_level() + level );

      // leveling up brings experience of the hero to the min experience for the level
      set_experience( level_experience.at( get_level() ) );

      uint8_t probability = rand() % 100;

      bool x = get_level() > 10;

      switch( get_class() )
      {
            case Class::Knight       : add_to_primary_on_level_up( probability, &p_s_knight[x][0] );       break;
            case Class::Cleric       : add_to_primary_on_level_up( probability, &p_s_cleric[x][0] );       break;
            case Class::Ranger       : add_to_primary_on_level_up( probability, &p_s_ranger[x][0] );       break;
            case Class::Druid        : add_to_primary_on_level_up( probability, &p_s_druid[x][0] );        break;
            case Class::Alchemist    : add_to_primary_on_level_up( probability, &p_s_alchemist[x][0] );    break;
            case Class::Wizard       : add_to_primary_on_level_up( probability, &p_s_wizard[x][0] );       break;
            case Class::Demoniac     : add_to_primary_on_level_up( probability, &p_s_demoniac[x][0] );     break;
            case Class::Heretic      : add_to_primary_on_level_up( probability, &p_s_heretic[x][0] );      break;
            case Class::Death_Knight : add_to_primary_on_level_up( probability, &p_s_death_knight[x][0] ); break;
            case Class::Necromancer  : add_to_primary_on_level_up( probability, &p_s_necromancer[x][0] );  break;
            case Class::Overlord     : add_to_primary_on_level_up( probability, &p_s_overlord[x][0] );     break;
            case Class::Warlock      : add_to_primary_on_level_up( probability, &p_s_warlock[x][0] );      break;
            case Class::Barbarian    : add_to_primary_on_level_up( probability, &p_s_barbarian[x][0] );    break;
            case Class::Battle_Mage  : add_to_primary_on_level_up( probability, &p_s_battle_mage[x][0] );  break;
            case Class::Beastmaster  : add_to_primary_on_level_up( probability, &p_s_beastmaster[x][0] );  break;
            case Class::Witch        : add_to_primary_on_level_up( probability, &p_s_witch[x][0] );        break;
            case Class::Planeswalker : add_to_primary_on_level_up( probability, &p_s_planeswalker[x][0] ); break;
            case Class::Elementalist : add_to_primary_on_level_up( probability, &p_s_elementalist[x][0] ); break;
            case Class::Captain      : add_to_primary_on_level_up( probability, &p_s_captain[x][0] );      break;
            case Class::Navigator    : add_to_primary_on_level_up( probability, &p_s_navigator[x][0] );    break;
      }

      // TO DO : upgrade a secondary skill
}

void Hero::add_to_primary_on_level_up(uint8_t probability, const uint8_t* array)
{
      // a = probability of attack skill
      // d = probability of defense skill
      // p = probability of power skill
      // k = probability of knowledge skill
      // Lets set the limits accordingly :
      uint8_t a = *array;
      uint8_t d = *(array + 1);
      uint8_t p = *(array + 2);
      uint8_t k = *(array + 3);
      d += a;
      p += d;
      k += p;

      if     ( probability < a ) { add_attack(1);    printf( "\n%s reaches level %d and recieves a bonus point in attack.\n", get_name().c_str(), get_level() );    }
      else if( probability < d ) { add_defense(1);   printf( "\n%s reaches level %d and recieves a bonus point in defense.\n", get_name().c_str(), get_level() );   }
      else if( probability < p ) { add_power(1);     printf( "\n%s reaches level %d and recieves a bonus point in power.\n", get_name().c_str(), get_level() );     }
      else if( probability < k ) { add_knowledge(1); printf( "\n%s reaches level %d and recieves a bonus point in knowledge.\n", get_name().c_str(), get_level() ); }
      else { std::cerr << "\nProbability = "<< probability <<". Such value is unacceptable! Check the primary skills level up coefficients in add_level()!" << std::endl; abort(); }
}

void Hero::add_experience(const uint32_t experience)
{
      const uint8_t current_level = get_level();

      if( current_level == 75 )
      {
            printf( "\n%s has reached max level, so %s cannot gain more experience!\n", get_name(), get_gender() ? "he" : "she" );
            return;
      }

      const uint32_t new_experience = get_experience() + experience;
      uint8_t levels_gained = 0;

      if( new_experience > MAX_EXPERIENCE )
      {
            set_experience( MAX_EXPERIENCE );
            levels_gained = 75 - current_level;
            printf( "\n%s has reached max experience!\n", get_name() );
      }
      else
      {
            set_experience( new_experience );

            if( new_experience >= level_experience.at(current_level + 1) )
                  for( auto lev_exp : level_experience )
                        if( new_experience < lev_exp.second )
                        {
                              levels_gained = lev_exp.first - 1 - current_level;
                              break;
                        }
      }

      for( uint8_t i = 0; i < levels_gained; i++)
            add_level(1);

}

Skill_level Hero::get_secondary_skill_level(const std::string skill_name)
{
      for( uint8_t i = 0; i < SECONDARY_SKILL_SLOTS; i++)
      {
            auto const skill = get_secondary_skill(i);

            if( skill != nullptr)
                  if( skill->get_name() == skill_name )
                        return skill->get_level();
      }

      return Skill_level::None;
}

void Hero::pick_up_item(Item* item)
{
      switch( item->get_slot() )
      {
            case Slot::Helmet   : if( items.helmet   != nullptr ) { add_item_to_chest( item ); } else { equip_item( item ); } break;
            case Slot::Cape     : if( items.cape     != nullptr ) { add_item_to_chest( item ); } else { equip_item( item ); } break;
            case Slot::Necklace : if( items.necklace != nullptr ) { add_item_to_chest( item ); } else { equip_item( item ); } break;
            case Slot::Weapon   : if( items.weapon   != nullptr ) { add_item_to_chest( item ); } else { equip_item( item ); } break;
            case Slot::Shield   : if( items.shield   != nullptr ) { add_item_to_chest( item ); } else { equip_item( item ); } break;
            case Slot::Armor    : if( items.armor    != nullptr ) { add_item_to_chest( item ); } else { equip_item( item ); } break;
            case Slot::Boots    : if( items.boots    != nullptr ) { add_item_to_chest( item ); } else { equip_item( item ); } break;
            case Slot::Hand     : for( uint8_t i = 0; i < HAND_SLOTS;   i++ ) { if( items.hand[i]   == nullptr ) { equip_item( item ); return; } } add_item_to_chest( item );  break;
            case Slot::Pocket   : for( uint8_t i = 0; i < POCKET_SLOTS; i++ ) { if( items.pocket[i] == nullptr ) { equip_item( item ); return; } } add_item_to_chest( item );  break;
      }
}

void Hero::equip_item_from_chest(Item* item)
{
      for( uint8_t i = 0; i < CHEST_SLOTS; i++ )
            if( chest[i] == item )
            {
                  switch( item->get_slot() )
                  {
                        case Slot::Helmet   : if( items.helmet   != nullptr ) { unequip_item( items.helmet   ); } equip_item( item ); break;
                        case Slot::Cape     : if( items.cape     != nullptr ) { unequip_item( items.cape     ); } equip_item( item ); break;
                        case Slot::Necklace : if( items.necklace != nullptr ) { unequip_item( items.necklace ); } equip_item( item ); break;
                        case Slot::Weapon   : if( items.weapon   != nullptr ) { unequip_item( items.weapon   ); } equip_item( item ); break;
                        case Slot::Shield   : if( items.shield   != nullptr ) { unequip_item( items.shield   ); } equip_item( item ); break;
                        case Slot::Armor    : if( items.armor    != nullptr ) { unequip_item( items.armor    ); } equip_item( item ); break;
                        case Slot::Boots    : if( items.boots    != nullptr ) { unequip_item( items.boots    ); } equip_item( item ); break;
                        case Slot::Hand     : for( uint8_t i = 0; i < HAND_SLOTS;   i++ ) { if( items.hand[i]   == nullptr ) { equip_item( item ); return; } } unequip_item( items.hand[0]  ); equip_item( item ); break;
                        case Slot::Pocket   : for( uint8_t i = 0; i < POCKET_SLOTS; i++ ) { if( items.pocket[i] == nullptr ) { equip_item( item ); return; } } unequip_item( items.pocket[0]); equip_item( item ); break;
                  }
                  return;
            }
      printf( "\nItem '%s' not found in treasure chest!\n", item->get_name().c_str() );
}

void Hero::equip_item(Item* item)
{
      switch( item->get_slot() )
      {
            case Slot::Helmet   : items.helmet   = item; break;
            case Slot::Cape     : items.cape     = item; break;
            case Slot::Necklace : items.necklace = item; break;
            case Slot::Weapon   : items.weapon   = item; break;
            case Slot::Shield   : items.shield   = item; break;
            case Slot::Armor    : items.armor    = item; break;
            case Slot::Boots    : items.boots    = item; break;
            case Slot::Hand     : for( uint8_t i = 0; i < HAND_SLOTS;   i++ ) { if( items.hand[i]   == nullptr ) { items.hand[i]   = item; break; } } break;
            case Slot::Pocket   : for( uint8_t i = 0; i < POCKET_SLOTS; i++ ) { if( items.pocket[i] == nullptr ) { items.pocket[i] = item; break; } } break;
      }
      
      // Check if same item is equipped in hand slot (not concerning 'Quiet Eye of the Dragon' an resource generating items )
      if( item->get_slot() == Slot::Hand )
            if( item->get_name() != "Quiet Eye of the Dragon" || item->get_effect().find("Resource") == std::string::npos )
                  for( uint8_t i = 0; i < HAND_SLOTS - 1; i++)
                        for( uint8_t j = i + 1; j < HAND_SLOTS ; j++)
                              if( items.hand[i] != nullptr && items.hand[j] != nullptr )
                                    if( item->get_name() == items.hand[i]->get_name() && items.hand[i]->get_name() == items.hand[j]->get_name() )
                                    {
                                          printf( "\n%s equips item '%s', but does not gain effects, because the same item is already equipped and its bonuses cannot be multiplied.\n", get_name().c_str(), item->get_name().c_str() );
                                          return;
                                    }

      // Check if same item is equipped in pocket slot (not concerning resource generating items )
      if( item->get_slot() == Slot::Pocket )
            if( item->get_effect().find("Gold") != std::string::npos && item->get_effect().find("Resource") != std::string::npos ) // items may generate gold or resources, but never both
                  for( uint8_t i = 0; i < POCKET_SLOTS - 1; i++)
                        for( uint8_t j = i + 1; j < POCKET_SLOTS ; j++)
                              if( items.pocket[i] != nullptr && items.pocket[j] != nullptr )
                                    if( item->get_name() == items.pocket[i]->get_name() && items.pocket[i]->get_name() == items.pocket[j]->get_name() )
                                    {
                                          printf( "\n%s equips item '%s', but does not gain effects, because the same item is already equipped and its bonuses cannot be multiplied.\n", get_name().c_str(), item->get_name().c_str() );
                                          return;
                                    }

      // TO DO : Check if recipe for combo items if fulfilled - if yes - give the bonuses. 
      // Perhaps after each equip if the items name is part of list of combination recipes a funciton to seek for the rest of items should be called. 
      // Afterwards combining the items takes place just like in the game, and the bonuses are assigned.

      printf( "\n%s equips item '%s', gaining effects : %s\n", get_name().c_str(), item->get_name().c_str(), item->get_effect().c_str() );

      add_attack(    item->get_attack_bonus()    );
      add_defense(   item->get_defense_bonus()   );
      add_power(     item->get_power_bonus()     );
      add_knowledge( item->get_knowledge_bonus() );
      if( item->get_knowledge_bonus() )
            update_mana();

      add_morale( item->get_morale_bonus() );
      add_luck(   item->get_luck_bonus()   );

      set_army_hp_bonus(    get_army_hp_bonus()    + 1*item->get_increase_hp_1()    + 2*item->get_increase_hp_2()    );
      set_army_speed_bonus( get_army_speed_bonus() + 1*item->get_increase_speed_1() + 2*item->get_increase_speed_2() );

      add_reduce_enemy_power_skill( 10*item->get_decrease_enemy_spell_power_10() + 25*item->get_decrease_enemy_spell_power_25() );
      add_reduce_enemy_morale( item->get_decrease_enemy_morale_bonus() );
      add_reduce_enemy_luck(   item->get_decrease_enemy_luck_bonus()   );

      update_army_stats();
}

void Hero::unequip_item(Item* item)
{
      switch( item->get_slot() )
      {
            case Slot::Helmet   : if( items.helmet   == item ) { if( add_item_to_chest( item ) ) { items.helmet   = nullptr; } else { return; } } else { printf( "\nItem '%s' is not equiped!\n", item->get_name().c_str() ); return; }; break;
            case Slot::Cape     : if( items.cape     == item ) { if( add_item_to_chest( item ) ) { items.cape     = nullptr; } else { return; } } else { printf( "\nItem '%s' is not equiped!\n", item->get_name().c_str() ); return; }; break;
            case Slot::Necklace : if( items.necklace == item ) { if( add_item_to_chest( item ) ) { items.necklace = nullptr; } else { return; } } else { printf( "\nItem '%s' is not equiped!\n", item->get_name().c_str() ); return; }; break;
            case Slot::Weapon   : if( items.weapon   == item ) { if( add_item_to_chest( item ) ) { items.weapon   = nullptr; } else { return; } } else { printf( "\nItem '%s' is not equiped!\n", item->get_name().c_str() ); return; }; break;
            case Slot::Shield   : if( items.shield   == item ) { if( add_item_to_chest( item ) ) { items.shield   = nullptr; } else { return; } } else { printf( "\nItem '%s' is not equiped!\n", item->get_name().c_str() ); return; }; break;
            case Slot::Armor    : if( items.armor    == item ) { if( add_item_to_chest( item ) ) { items.armor    = nullptr; } else { return; } } else { printf( "\nItem '%s' is not equiped!\n", item->get_name().c_str() ); return; }; break;
            case Slot::Boots    : if( items.boots    == item ) { if( add_item_to_chest( item ) ) { items.boots    = nullptr; } else { return; } } else { printf( "\nItem '%s' is not equiped!\n", item->get_name().c_str() ); return; }; break;
            case Slot::Hand     : for( uint8_t i = 0; i < HAND_SLOTS;   i++ ) { if( items.hand[i]   == item ) { if( add_item_to_chest( item ) ) { items.hand[i]   = nullptr; break; } else { return; } } } printf( "\nItem '%s' is not equiped!\n", item->get_name().c_str() ); return; 
            case Slot::Pocket   : for( uint8_t i = 0; i < POCKET_SLOTS; i++ ) { if( items.pocket[i] == item ) { if( add_item_to_chest( item ) ) { items.pocket[i] = nullptr; break; } else { return; } } } printf( "\nItem '%s' is not equiped!\n", item->get_name().c_str() ); return;
      }

      // Check if same item is equipped in hand slot (not concerning 'Quiet Eye of the Dragon' an resource generating items )
      if( item->get_slot() == Slot::Hand )
            if( items.hand[0]->get_name() == items.hand[1]->get_name() )
                  if( item->get_name() != "Quiet Eye of the Dragon" || item->get_effect().find("Resource") == std::string::npos )
                  {
                        printf( "\n%s unequips item '%s', but does not lose effects, because the same item is already equipped and its bonuses cannot be multiplied.\n", get_name().c_str(), item->get_name().c_str() );
                        return;
                  }

      // Check if same item is equipped in pocket slot (not concerning resource generating items )
      if( item->get_slot() == Slot::Pocket )
            if( item->get_effect().find("Gold") != std::string::npos && item->get_effect().find("Resource") != std::string::npos ) // items may generate gold or resources, but never both
                  for( uint8_t i = 0; i < POCKET_SLOTS - 1; i++)
                        for( uint8_t j = i + 1; j < POCKET_SLOTS ; j++)
                              if( item->get_name() == items.pocket[i]->get_name() && items.pocket[i]->get_name() == items.pocket[j]->get_name() )
                              {
                                    printf( "\n%s unequips item '%s', but does not lose effects, because the same item is already equipped and its bonuses cannot be multiplied.\n", get_name().c_str(), item->get_name().c_str() );
                                    return;
                              }

      // TO DO : Check if unequipping the item will destroy the combo and reduce the bonuses
      
      printf( "\n%s unequips item '%s', losing effects : %s\n", get_name().c_str(), item->get_name().c_str(), item->get_effect().c_str() );

      add_attack(    -item->get_attack_bonus()    );
      add_defense(   -item->get_defense_bonus()   );
      add_power(     -item->get_power_bonus()     );
      add_knowledge( -item->get_knowledge_bonus() );
      if( item->get_knowledge_bonus() )
            update_mana();

      add_morale( -item->get_morale_bonus() );
      add_luck(   -item->get_luck_bonus()   );

      set_army_hp_bonus(    get_army_hp_bonus()    - 1*item->get_increase_hp_1()    - 2*item->get_increase_hp_2()    );
      set_army_speed_bonus( get_army_speed_bonus() - 1*item->get_increase_speed_1() - 2*item->get_increase_speed_2() );

      add_reduce_enemy_power_skill( -10*item->get_decrease_enemy_spell_power_10() - 25*item->get_decrease_enemy_spell_power_25() );
      add_reduce_enemy_morale( -item->get_decrease_enemy_morale_bonus() );
      add_reduce_enemy_luck(   -item->get_decrease_enemy_luck_bonus()   );

      update_army_stats();
}

bool Hero::add_item_to_chest(Item* item)
{
      for( uint8_t i = 0; i < CHEST_SLOTS; i++ )
            if( chest[i] == nullptr )
            {
                  chest[i] = item;
                  return true;
            }

      printf( "\n%s's treasure chest is full and no items can be added to it!\n", get_name().c_str() );
      return false;
}

bool Hero::check_eqipped_item(std::string item_name, Slot slot)
{
      std::map<Slot, Item*> items_map;
      items_map[Slot::Helmet]   = items.helmet;
      items_map[Slot::Cape]     = items.cape;
      items_map[Slot::Necklace] = items.necklace;
      items_map[Slot::Weapon]   = items.weapon;
      items_map[Slot::Shield]   = items.shield;
      items_map[Slot::Armor]    = items.armor;
      items_map[Slot::Boots]    = items.boots;

      if(slot == Slot::Hand)
            for( uint8_t i = 0; i < HAND_SLOTS; i++)
                  if( items.hand[i] != nullptr )
                        if( items.hand[i] ->get_name() == item_name )
                              return true;
      else if(slot == Slot::Pocket)
            for( uint8_t i = 0; i < POCKET_SLOTS; i++)
                  if( items.pocket[i] != nullptr )
                        if( items.pocket[i]->get_name() == item_name )
                              return true;
      else
            if( items_map[slot] != nullptr )
                  if( items_map[slot]->get_name() == item_name )
                        return true;

      return false;
}

void Hero::print_equipped_items()
{
      std::map<Slot, Item*> items_map;
      items_map[Slot::Helmet]   = items.helmet;
      items_map[Slot::Cape]     = items.cape;
      items_map[Slot::Necklace] = items.necklace;
      items_map[Slot::Weapon]   = items.weapon;
      items_map[Slot::Shield]   = items.shield;
      items_map[Slot::Armor]    = items.armor;
      items_map[Slot::Boots]    = items.boots;

      printf( "\n%s has equipped : \n", get_name().c_str() );
      for(auto & item : items_map)
            if( item.second != nullptr )        printf( "\tSlot %s - %s : %s\n",    item.second->get_slot_as_string().c_str(),            item.second->get_name().c_str(),    item.second->get_effect().c_str()      );

      for( uint8_t i = 0; i < HAND_SLOTS; i++)
            if( items.hand[i] != nullptr )      printf( "\tSlot %s %d - %s : %s\n", items.hand[i]->get_slot_as_string().c_str(), i + 1,   items.hand[i]->get_name().c_str(),   items.hand[i]->get_effect().c_str()   );
      
      for( uint8_t i = 0; i < POCKET_SLOTS; i++)
            if( items.pocket[i] != nullptr )    printf( "\tSlot %s %d - %s : %s\n", items.pocket[i]->get_slot_as_string().c_str(), i + 1, items.pocket[i]->get_name().c_str(), items.pocket[i]->get_effect().c_str() );
}

void Hero::print_unequipped_items()
{
      bool chest_has_items = false;
      printf( "\n%s's treasure chest has : \n", get_name().c_str() );

      for( uint8_t i = 0; i < CHEST_SLOTS; i++ )
            if( chest[i] != nullptr )
            {
                  chest_has_items = true;
                  printf( "\tPosition %d - %s slot = %s : %s\n", i, chest[i]->get_slot_as_string().c_str(), chest[i]->get_name().c_str(), chest[i]->get_effect().c_str() );
            }
      
      if( !chest_has_items )
            printf( "No items.\n" );
}

void Hero::add_stack_to_army(std::unique_ptr<Stack> & stack_ptr)
{
      for( uint8_t i = 0; i < ARMY_SLOTS; i++ )
            if( army[i] == nullptr )
            {
                  army[i].swap(stack_ptr); // swaps the nullptr with the stack
                  delete stack_ptr.get();  // deletes the nullptr

                  update_army_stats();
                  return;
            }

      printf("\n%s tries to add stack of %d %s to army, but there is not enough space!\n", get_name().c_str(), stack_ptr.get()->get_number(), stack_ptr.get()->get_creature_name().c_str());
      return;
}

void Hero::add_stack_to_slot(std::unique_ptr<Stack> & stack_ptr, const uint8_t slot)
{
      auto const stack = stack_ptr.get();

      if( get_team() != stack->get_team() )
      {
            printf("\nImpossible to add this stack as ");
            print_colored_string( get_name().c_str(), get_team() );
            printf(" and the stack of ");
            print_colored_string( stack->get_creature_name().c_str(), stack->get_team());
            printf(" do not belong to the same team!\n");
            return;
      }

      if( army[slot] == nullptr )
      {
            army[slot].swap(stack_ptr); // swaps the nullptr with the stack
            delete stack_ptr.get();     // deletes the nullptr
            
            update_army_stats();
            return;
      }

      printf("\n%s tries to add stack of %d %s to army slot %d, but it is taken!\n", get_name().c_str(), stack->get_number(), stack->get_creature_name().c_str(), slot + 1);
      return;
}

void Hero::remove_stack(std::unique_ptr<Stack> & stack_ptr)
{
      auto const stack = stack_ptr.get();

      for( uint8_t i = 0; i < ARMY_SLOTS; i++)
            if( army[i] == stack_ptr )
            {
                  printf( "\nStack of %d %s removed from %s's army.\n", stack->get_number(), stack->get_creature_name().c_str(), get_name().c_str() );
                  
                  delete army[i].get();
                  army[i].reset(nullptr);

                  update_army_stats(); // because removed creatures might have army bonuses
                  return;
            }

      printf( "\nStack of %d %s does not exist in %s's army.\n", stack->get_number(), stack->get_creature_name().c_str(), get_name().c_str() );
}

void Hero::remove_stack_from_position(const uint8_t slot)
{
      if( army[slot] == nullptr )
      {
            printf( "\nSlot %d is already empty.\n", slot );
            return;
      }
      printf( "\nStack of %d %s removed from %s's army from slot %d.\n", army[slot]->get_number(), army[slot]->get_creature_name().c_str(), get_name().c_str(), slot + 1);
      
      delete army[slot].get();
      army[slot].reset(nullptr);
      
      update_army_stats(); // because removed creatures might have army bonuses
}

void Hero::swap_stack_positions(uint8_t i, uint8_t j)
{
      if( i < 0 || i > ARMY_SLOTS - 1 )
      {
            std::cerr << "Slot positions must be in the range [0;" << ARMY_SLOTS - 1 << "]!" << std::endl;
            abort();
      }

      if( j < 0 || j > ARMY_SLOTS - 1 )
      {
            std::cerr << "Slot positions must be in the range [0;" << ARMY_SLOTS - 1 << "]!" << std::endl;
            abort();
      }

      army[i].swap(army[j]);
      return;
}

void Hero::swap_entire_armies(Hero& hero)
{
      if( get_team() != hero.get_team() )
      {
            printf("Heroes must be from the same team in order to swap armies!\n");
            return;
      }

      for(uint8_t i = 0; i < ARMY_SLOTS; i++)
            army[i].swap( hero.get_army_stack_ptr(i) );
      
      update_army_stats();
      hero.update_army_stats();
}

void Hero::update_army_stats()
{      
      uint8_t att   = get_attack();
      uint8_t def   = get_defense();
      Morale morale = get_morale();
      Luck luck     = get_luck();

      bool has_equipped_elixir_of_life = _has_equipped_elixir_of_life;

      const uint8_t hero_level = get_level();
      const std::string specialty_name = get_specialty().get_name();

      Skill_level level_of_archery    = Skill_level::None;
      Skill_level level_of_offense    = Skill_level::None;
      Skill_level level_of_armorer    = Skill_level::None;
      Skill_level level_of_resistance = Skill_level::None;

      for(uint8_t i = 0; i < SECONDARY_SKILL_SLOTS; i++)
      {
            if( get_secondary_skill(i) != nullptr )
            {
                  if     ( get_secondary_skill(i)->get_name() == "Archery")    { level_of_archery    = get_secondary_skill(i)->get_level(); }
                  else if( get_secondary_skill(i)->get_name() == "Offense")    { level_of_offense    = get_secondary_skill(i)->get_level(); }
                  else if( get_secondary_skill(i)->get_name() == "Armorer")    { level_of_armorer    = get_secondary_skill(i)->get_level(); }
                  else if( get_secondary_skill(i)->get_name() == "Resistance") { level_of_resistance = get_secondary_skill(i)->get_level(); }
            }
      }
      
      // count the number of different factions for morale and luck bonus/penalty
      bool has_Neutral    = false;
      bool has_Castle     = false;
      bool has_Rampart    = false;
      bool has_Tower      = false;
      bool has_Inferno    = false;
      bool has_Necropolis = false;
      bool has_Dungeon    = false;
      bool has_Stronghold = false;
      bool has_Fortress   = false;
      bool has_Conflux    = false;
      bool has_Cove       = false;

      for(uint8_t i = 0; i < ARMY_SLOTS; i++)
      {
            if( army[i] != nullptr)
            {
                  switch( army[i]->get_creature()->get_faction() )
                  {
                        case Faction::Neutral    : has_Neutral    = true; break;
                        case Faction::Castle     : has_Castle     = true; break;
                        case Faction::Rampart    : has_Rampart    = true; break;
                        case Faction::Tower      : has_Tower      = true; break;
                        case Faction::Inferno    : has_Inferno    = true; break;
                        case Faction::Necropolis : has_Necropolis = true; break;
                        case Faction::Dungeon    : has_Dungeon    = true; break;
                        case Faction::Stronghold : has_Stronghold = true; break;
                        case Faction::Fortress   : has_Fortress   = true; break;
                        case Faction::Conflux    : has_Conflux    = true; break;
                        case Faction::Cove       : has_Cove       = true; break;
                  }
            }
      }
      uint8_t total = has_Neutral + has_Castle + has_Rampart + has_Tower + has_Inferno + has_Necropolis + has_Dungeon + has_Stronghold + has_Fortress + has_Conflux + has_Cove;
      Morale morale_penalty = Morale::Neutral; // diversity is penalized

      switch( total )
      {
            case 1  : morale_penalty = Morale::Good;     break;
            case 2  : morale_penalty = Morale::Neutral;  break;
            case 3  : morale_penalty = Morale::Bad;      break;
            case 4  : morale_penalty = Morale::Awful;    break;
            default : morale_penalty = Morale::Terrible; break;
      }

      for(uint8_t i = 0; i < ARMY_SLOTS; i++)
      {
            if( army[i] != nullptr)
            {
                  auto const c = army[i]->get_creature();

                  army[i]->set_att( c->get_att() + att );
                  army[i]->set_def( c->get_def() + def );
                  
                  army[i]->set_hp( c->get_hp() + get_army_hp_bonus() + (c->get_hp()/4)*has_equipped_elixir_of_life );
                  army[i]->set_hp_left( c->get_hp() );
                  if( has_equipped_elixir_of_life && !c->get_is_undead() && !c->get_is_bloodless() )
                        army[i]->set_has_acquired_regeneration(true);

                  army[i]->set_speed( c->get_speed() + get_army_speed_bonus() );

                  army[i]->set_morale( static_cast<Morale>( std::min( std::max( static_cast<int8_t>(c->get_morale()) + static_cast<int8_t>(get_morale()) + static_cast<int8_t>(morale_penalty), -3), 3) ) );
                  if( c->get_is_undead() || ( c->get_is_bloodless() && ( c->get_name() != "Stone Gargoyle" && c->get_name() != "Obsidian Gargoyle" ) ) )
                        army[i]->set_morale( Morale::Neutral );
                  if( c->get_minimum_morale_1() && static_cast<int8_t>(army[i]->get_morale()) < 1 )
                        army[i]->set_morale( Morale::Good );

                  army[i]->set_luck( static_cast<Luck>( std::min( std::max( static_cast<int8_t>(c->get_luck()) + static_cast<int8_t>(get_luck()), -3), 3) ) );
                  if( c->get_minimum_luck_1() && static_cast<int8_t>(army[i]->get_luck()) < 1 )
                        army[i]->set_luck( Luck::Good );
            }
      }
}

Stack* Hero::get_army_stack(uint8_t i)
{
      if( i > ARMY_SLOTS )
      {
            std::cerr << i << "is invalid army position!" << std::endl;
            abort();
      }

      return army[i].get();
}

std::unique_ptr<Stack> & Hero::get_army_stack_ptr(uint8_t i)
{
      if( i > ARMY_SLOTS )
      {
            std::cerr << i << "is invalid army position!" << std::endl;
            abort();
      }

      return army[i];
}

// this is not accurate representation of the hero movement in the game
// path to location should be calculated in days
// each tile across the path should be visited for step-on effects
// TO DO : fix move()
void Hero::move(const uint8_t x, const uint8_t y)
{
    const uint8_t distance = std::abs(x - _position.x) + std::abs(y - _position.y);
    while(get_movement_points() < distance)
    {
        printf("%s only has %d movement points and can't move that far. Pick a new position!", get_name(), get_movement_points());
    }
    _position.x = x;
    _position.y = y;
}

void Hero::print_full_info()
{
      printf( "\n" );
      printf( "Name : %s\n",      get_name().c_str() );
      printf( "Gender : %s\n",    get_gender_as_string().c_str()  );
      printf( "Role : %s\n",      get_role_as_string().c_str()    );
      printf( "Class : %s\n",     get_class_as_string().c_str()   );
      printf( "Faction : %s\n",   get_faction_as_string().c_str() );
      printf( "Team : %s\n",      get_team_as_string().c_str()    );
      printf( "Level : %d\n",     get_level() );
      printf( "Experiece : %d\n", get_experience() );

      printf( "Primary skills :\n" );
      printf( "\tAttack : %d\n",    get_attack()    );
      printf( "\tDefense : %d\n",   get_defense()   );
      printf( "\tPower : %d\n",     get_power()     );
      printf( "\tKnowledge : %d\n", get_knowledge() );

      printf( "Specialty : %s\n\t%s\n", get_specialty().get_name().c_str(), get_specialty().get_effect().c_str() );

      printf( "Morale : %d\n",          get_morale() );
      printf( "Luck : %d\n",            get_luck()   );
      printf( "Mana : %d / %d\n",       get_mana_left(), get_mana() );
      printf( "Movement points : %d\n", get_movement_points() );

      printf( "Has First Aid Tent : %s\n", get_has_first_aid() ? "true" : "false" );
      printf( "Has Ammo Cart : %s\n",      get_has_ammo_cart() ? "true" : "false" );
      // if( get_has_cannon() )
      //       printf( "Has Cannon : true" );
      // else
            printf( "Has Ballista : %s\n", get_has_ballista() ? "true" : "false" );
      printf( "Has Ballista : %s\n",  get_has_spellbook() ? "true" : "false" );
      printf( "Has Catapult : %s\n",  get_has_catapult()  ? "true" : "false" );

      printf( "Has Spellbook : %s\n", get_has_spellbook() ? "true" : "false" );
}