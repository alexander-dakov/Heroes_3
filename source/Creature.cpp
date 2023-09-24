#include "Creature.h"

Creature::Creature( const std::string name, const Faction faction, const uint8_t level, const bool is_upgraded, const uint8_t growth, const bool needs_2_hexes_in_battle,
                    const uint8_t att, const uint8_t def, const uint8_t shots, const uint8_t min_dmg, const uint8_t max_dmg, const uint16_t hp, const uint8_t speed, const Morale morale, const Luck luck, const uint16_t fight_value, const uint16_t ai_value, 
                    const Resources resources,
                    const std::string abilities ) : 
                    unit_info(name, faction, level, is_upgraded, growth, needs_2_hexes_in_battle),
                    battle_stats(att, def, shots, min_dmg, max_dmg, hp, speed, morale, luck, fight_value, ai_value),
                    cost(resources),  
                    special_abilities(abilities)
{
      special_abilities.fill_special_abilities(); 

      logical_limitations();

      // std::cout << "Creature "<< unit_info._name <<" created." << std::endl;
}

Creature::Creature(const Creature& creature) : unit_info(creature.unit_info), battle_stats(creature.battle_stats), cost(creature.cost), special_abilities(creature.special_abilities)
{
      // std::cout << "Creature "<< unit_info._name <<" created." << std::endl;
}

Creature::Creature(const Creature* creature) : unit_info(creature->unit_info), battle_stats(creature->battle_stats), cost(creature->cost), special_abilities(creature->special_abilities)
{
      // std::cout << "Creature "<< unit_info._name <<" created." << std::endl;
}

Creature::~Creature()
{
      // std::cout << "Creature " << this->get_name() << " destroyed!" << std::endl;
}

void Creature::logical_limitations()
{
      if(unit_info._level == 0 || unit_info._level > 7)
      {
            std::cout<< "Creature level must be in the interval [1;7]!" << std::endl;
            abort();
      }

      if(unit_info._growth == 0)
      {
            std::cout<< "Creature must have positive growth per week!" << std::endl;
            abort();
      }

      if(battle_stats._att == 0)
      {
            std::cout<< "Creature must have positive attack skill!" << std::endl;
            abort();
      }

      if(battle_stats._def == 0)
      {
            std::cout<< "Creature must have positive defense skill!" << std::endl;
            abort();
      }

      if(battle_stats._min_dmg > battle_stats._min_dmg)
      {
            std::cout<< "Creature min damage mustn't be higher than its max value!" << std::endl;
            abort();
      }

      if(battle_stats._hp == 0)
      {
            std::cout<< "Creature must have positive hp!" << std::endl;
            abort();
      }

      if(battle_stats._speed == 0)
      {
            std::cout<< "Creature must have positive speed!" << std::endl;
            abort();
      }

      if(battle_stats._fight_value == 0)
      {
            std::cout<< "Creature must have positive fight value!" << std::endl;
            abort();
      }

      if(battle_stats._ai_value == 0)
      {
            std::cout<< "Creature must have positive ai value!" << std::endl;
            abort();
      }

      if(cost._gold == 0)
      {
            std::cout<< "Creature must have a price including gold!" << std::endl;
            abort();
      }

      if(unit_info._faction == Faction::Necropolis)
      {
            special_abilities._is_undead = true;
            special_abilities._is_bloodless = false;
      }

      if(special_abilities._is_undead == true)
            special_abilities._is_bloodless = false;

      if(special_abilities._is_bloodless == true)
            special_abilities._is_undead = false;

      if(!special_abilities._is_ranged)
            battle_stats._shots = 0;

}

std::map<std::string, bool*> Creature::special_abilities::create_map_of_all_abilities()
{
      std::map<std::string, bool*> all_abilities; // all special abilities in existance, refering to their respective boolean

      all_abilities["Undead."]        = &_is_undead;
      all_abilities["Non-living."]    = &_is_bloodless;

      all_abilities["Flying."]        = &_is_flying;
      all_abilities["Ranged attack."] = &_is_ranged;

      all_abilities["No melee penalty."]    = &_no_melee_penalty;
      all_abilities["No obstacle penalty."] = &_no_obstacle_penalty;

      all_abilities["Double attack."]                    = &_has_double_attack;
      all_abilities["Jousting bonus."]                   = &_has_jousting;
      all_abilities["Fireball attack."]                  = &_has_fireball_attack;
      all_abilities["Death cloud."]                      = &_has_cloud_attack;
      all_abilities["Attack all adjacent enemies."]      = &_has_attack_adjacent;
      all_abilities["Breath attack."]                    = &_has_breath_attack;
      all_abilities["Hates Efreeti and Efreet Sultans."] = &_hates_efreeti;
      all_abilities["Hates Genies and Master Genies."]   = &_hates_genies;
      all_abilities["Hates Devils and Arch Devils."]     = &_hates_devils;
      all_abilities["Hates Angels and Arch Angels."]     = &_hates_angels;
      all_abilities["Hates Black Dragons."]              = &_hates_black_dragons;
      all_abilities["Hates Titans."]                     = &_hates_titans;

      all_abilities["Two retaliations."]       = &_has_two_retaliations;
      all_abilities["Unlimited retaliations."] = &_has_unlimited_retaliations;
      all_abilities["No enemy retaliation."]   = &_no_enemy_retaliation;
      
      all_abilities["Regeneration."] = &_casts_regeneration;
      all_abilities["Mana drain."]   = &_casts_mana_drain;

      all_abilities["Binding attack."]       =  &_casts_binding;
      all_abilities["Life drain."]           =  &_casts_life_drain;
      // all_abilities["Casts Dispell."]        =  &_casts_dispell;
      // all_abilities["Casts Weakness."]       =  &_casts_weakness;
      // all_abilities["Casts Disrupting Ray."] =  &_casts_disrupting_ray;

      all_abilities["20% chance to cast Disease per attack."]          = &_can_cast_disease;
      // all_abilities["20% chance to cast Weakness per attack."]         = &_can_cast_weakness;
      // all_abilities["20% chance to cast Disrupting Ray per attack."]   = &_can_cast_disrupting_ray;
      all_abilities["25% chance to cast Curse per attack."]            = &_can_cast_curse;
      all_abilities["20% chance to cast Aging per attack."]            = &_can_cast_aging;
      // all_abilities["20% chance to cast Poison per attack."]           = &_can_cast_poison;
      // all_abilities["20% chance to cast Paralyzing Venom per attack."] = &_can_cast_paralyzing_venom;
      all_abilities["20% chance to cast Blind per attack."]            = &_can_cast_blind;
      // all_abilities["20% chance to cast Lightning Strike per attack."] = &_can_cast_lightning_strike;
      all_abilities["20% chance to cast Death Blow per attack."]       = &_can_cast_death_blow;

      all_abilities["Fire Shield."] = &_casts_fire_shield;

      all_abilities["Rebirth."] = &_can_cast_rebirth;

      all_abilities["Spellcaster."]                           = &_is_spellcaster;
      all_abilities["Can cast Ressurection once per battle."] = &_can_cast_ressurection;
      all_abilities["Spellcaster (Bloodlust)."]               = &_can_cast_bloodlust;
      all_abilities["Spellcaster (Protection from Air)."]     = &_can_cast_protection_from_air;
      all_abilities["Spellcaster (Protection from Water)."]   = &_can_cast_protection_from_water;
      all_abilities["Spellcaster (Protection from Fire)."]    = &_can_cast_protection_from_fire;
      all_abilities["Spellcaster (Protection from Earth)."]   = &_can_cast_protection_from_earth;

      all_abilities["Magic resistance 20%."]         = &_has_magic_resist_20;
      all_abilities["Magic resistance 40%."]         = &_has_magic_resist_40;
      all_abilities["Aura of magic resistance 20%."] = &_has_magic_resist_aura;

      all_abilities["Spell damage reduction 50%."] = &_reduce_magic_damage_50;
      all_abilities["Spell damage reduction 75%."] = &_reduce_magic_damage_75;

      all_abilities["Immune to jousting."]         = &_is_immune_to_jousting;
      all_abilities["Immune to level 1-3 spells."] = &_is_immune_to_spells_level_1_3;
      all_abilities["Immune to level 1-4 spells."] = &_is_immune_to_spells_level_1_4;
      all_abilities["Immune to all spells."]       = &_is_immune_to_all_spells;
      all_abilities["Immunity to mind spells."]    = &_is_immune_to_mind_spells;

      all_abilities["+1 morale to alias troops."] = &_increases_alias_morale;
      all_abilities["-1 morale to enemy troops."] = &_decreases_enemy_morale;

      all_abilities["Magic damper."] = &_magic_damper;
      all_abilities["Hero's combat spells cost 2 less mana."]   = &_mana_economy;

      return all_abilities;
}

void Creature::special_abilities::fill_special_abilities()
{
      std::string helper = _abilities; // a copy of the original creature ablities to cut from
      std::string::size_type pos; // position of found substring from map in "helper" string

      auto all_abilities = create_map_of_all_abilities();

      while( helper.length() > 1) // no need to enter helper when an empty space remains
      {
            if( helper[0] == ' ' ) // if the first character is whitespace - delete it
            {
                  helper.erase(0, 1);
                  break;
            }
            else
            {
                  for(auto ability : all_abilities) // key-value pair
                  {
                        pos = helper.find(ability.first);
                        if(pos != std::string::npos)
                        {
                              *ability.second = true;
                              helper.erase(pos, ability.first.length());
                              if( helper[pos] == ' ' ) // if the new character on the same place is whitespace - delete it
                                    helper.erase(pos, 1);
                              break;
                        }
                  }
            }
      }
}

std::string Creature::get_faction_as_string()
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
            case Faction::Fortress   : faction = "Fortress";   break;
            case Faction::Stronghold : faction = "Stronghold"; break;
            case Faction::Conflux    : faction = "Conflux";    break;
            case Faction::Cove       : faction = "Cove";       break;
      }

      return faction;
}

std::string Creature::get_cost()
{
      std::string str;

      if(cost._gold)          str += "Gold : "     + std::to_string(cost._gold)     + '\n';
      if(cost._mercury)       str += "Mercury : "  + std::to_string(cost._mercury)  + '\n';
      if(cost._sulfur)        str += "Sulfur : "   + std::to_string(cost._sulfur)   + '\n';
      if(cost._crystals)      str += "Crystals : " + std::to_string(cost._crystals) + '\n';
      if(cost._gems)          str += "Gems : "     + std::to_string(cost._gems)     + '\n';

      return str;
}

void Creature::print_full_info()
{
      printf("Name : %s\n", get_name().c_str());
      printf("Faction : %s\n", get_faction_as_string().c_str());
      printf("Level : %d\n", get_level());
      printf("Upgraded : %d\n", get_is_upgraded());
      printf("Growth per week : %d\n", get_growth());
      printf("Attack : %d\n", get_att());
      printf("Defence : %d\n", get_def());

      if(get_is_ranged())
            printf("Shots : %d\n", get_shots());
      
      printf("Damage : %d - %d\n", get_min_dmg(), get_max_dmg());
      printf("Health : %d\n", get_hp());
      printf("Morale : %d\n", get_morale());
      printf("Luck : %d\n", get_luck());
      printf("Fight value : %d\n", get_fight_value());
      printf("AI value : %d\n", get_ai_value());
      printf("%s", get_cost().c_str());

      if(get_special_abilities().length() != 0)
            printf("Special abilities : %s\n", get_special_abilities().c_str());
}