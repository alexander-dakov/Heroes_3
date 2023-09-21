#include "Creature.h"

Creature::Creature( const std::string name, const Faction faction, const uint8_t level, const bool is_upgraded, const uint8_t growth, const bool needs_2_hexes_in_battle,
                    const uint8_t att, const uint8_t def, const uint8_t shots, const uint8_t min_dmg, const uint8_t max_dmg, const uint16_t hp, const uint8_t speed, const Morale morale, const Luck luck, const uint16_t fight_value, const uint16_t ai_value, 
                    const Resources resources, 
                    const bool is_undead = false, const bool is_unliving = false, const bool is_flying = false, const bool is_ranged = false, const bool has_dragon_breath = false, const bool has_attack_adjacent = false ) :
                    unit_info(name, faction, level, is_upgraded, growth, needs_2_hexes_in_battle),
                    battle_stats(att, def, shots, min_dmg, max_dmg, hp, speed, morale, luck, fight_value, ai_value),
                    cost(resources),
                    special_abilities(is_undead, is_unliving, is_flying, is_ranged, has_dragon_breath, has_attack_adjacent)
{
      Logical_Limitations_When_Constructing();

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

void Creature::Logical_Limitations_When_Constructing()
{
      if(unit_info._level == 0 || unit_info._level > 7)
      {
            std::cout<< "Creture level must be in the interval [1;7]!" << std::endl;
            abort();
      }

      if(unit_info._growth == 0)
      {
            std::cout<< "Creture must have positive growth per week!" << std::endl;
            abort();
      }

      if(battle_stats._att == 0)
      {
            std::cout<< "Creture must have positive attack skill!" << std::endl;
            abort();
      }

      if(battle_stats._def == 0)
      {
            std::cout<< "Creture must have positive defense skill!" << std::endl;
            abort();
      }

      if(battle_stats._min_dmg > battle_stats._min_dmg)
      {
            std::cout<< "Creture min damage mustn't be higher than its max value!" << std::endl;
            abort();
      }

      if(battle_stats._hp == 0)
      {
            std::cout<< "Creture must have positive hp!" << std::endl;
            abort();
      }

      if(battle_stats._speed == 0)
      {
            std::cout<< "Creture must have positive speed!" << std::endl;
            abort();
      }

      if(battle_stats._fight_value == 0)
      {
            std::cout<< "Creture must have positive fight value!" << std::endl;
            abort();
      }

      if(battle_stats._ai_value == 0)
      {
            std::cout<< "Creture must have positive ai value!" << std::endl;
            abort();
      }

      if(cost._gold == 0)
      {
            std::cout<< "Creture must have a price including gold!" << std::endl;
            abort();
      }

      if(unit_info._faction == Faction::Necropolis)
      {
            special_abilities._is_undead = true;
            special_abilities._is_unliving = false;
      }

      if(special_abilities._is_unliving == true)
            special_abilities._is_undead = false;

      if(!special_abilities._is_ranged)
      {
            battle_stats._shots = 0;
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

std::string Creature::get_special_abilities()
{
      std::string str;

      if(special_abilities._is_undead)                str += "Undead. ";
      if(special_abilities._is_unliving)              str += "Unliving. ";
      if(special_abilities._is_flying)                str += "Flying. ";
      if(special_abilities._is_ranged)                str += "Ranged. ";
      if(special_abilities._has_dragon_breath)        str += "Dragon breath. ";
      if(special_abilities._has_attack_adjacent)      str += "Attacks all adjacent. ";

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