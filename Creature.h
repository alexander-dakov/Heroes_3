#ifndef CREATURE_H
#define CREATURE_H

#include <iostream>
#include <algorithm>
#include "types.h"
#include "Faction.h"
#include "Morale_Luck.h"
#include "Resources.h"
#include "Skill_level.h"


struct Creature
{
      private:

            struct unit_info
            {
                  std::string _name;
                  Faction _faction;
                  uint8_t _level;
                  bool _is_upgraded;
                  uint8_t _growth;
                  Morale _morale;
                  Luck _luck;
                  bool _needs_2_hexes_in_battle;

                  unit_info( std::string name, Faction faction, uint8_t level, bool is_upgraded, uint8_t growth, Morale morale, Luck luck, bool needs_2_hexes_in_battle ) :
                             _name(name), _faction(faction), _level(level), _is_upgraded(is_upgraded), _growth(growth), _needs_2_hexes_in_battle(needs_2_hexes_in_battle) 
                             {};
            }unit_info;

            struct battle_stats
            {
                  uint8_t _att;
                  uint8_t _def;
                  uint8_t _shots;
                  uint8_t _min_dmg;
                  uint8_t _max_dmg;
                  uint8_t _hp;
                  uint8_t _speed;
                  uint16_t _fight_value;
                  uint16_t _ai_value;

                  battle_stats( const uint8_t att, const uint8_t def, const uint8_t shots, const uint8_t min_dmg, const uint8_t max_dmg, 
                                const uint8_t hp, const uint8_t speed, const uint16_t fight_value, const uint16_t ai_value ) : 
                                _att(att), _def(def), _shots(shots), _min_dmg(min_dmg), _max_dmg(max_dmg),
                                _hp(hp), _speed(speed), _fight_value(fight_value), _ai_value(ai_value)
                                {};
            }battle_stats;

            struct cost
            {
                  uint16_t _gold;
                  uint16_t _mercury;
                  uint16_t _sulfur; 
                  uint16_t _crystals;
                  uint16_t _gems;

                  cost( const Resources resources ) : _gold(resources.Gold), _mercury(resources.Mercury), _sulfur(resources.Sulfur), _crystals(resources.Crystals), _gems(resources.Gems)
                  {};
            }cost;

            struct special_abilities
            {
                  bool _is_undead;
                  bool _is_unliving;
                  bool _is_flying;
                  bool _is_ranged;
                  bool _has_dragon_breath;
                  bool _has_attack_adjacent;

                  special_abilities( const bool is_undead, const bool is_unliving, const bool is_flying, const bool is_ranged, const bool has_dragon_breath, const bool has_attack_adjacent ) :
                                     _is_undead(is_undead),
                                     _is_unliving(is_unliving),
                                     _is_flying(is_flying), 
                                     _is_ranged(is_ranged), 
                                     _has_dragon_breath(has_dragon_breath), 
                                     _has_attack_adjacent(has_attack_adjacent)
                                     {};
            }special_abilities;
         
      public:
            // Constructors and Destructor
            // no default constructor, only parametrized and copy constructors
            Creature( const std::string name, const Faction faction, const uint8_t level, const bool is_upgraded, const uint8_t growth, const Morale morale, const Luck luck, const bool needs_2_hexes_in_battle,
                      const uint8_t att, const uint8_t def, const uint8_t shots, const uint8_t min_dmg, const uint8_t max_dmg, const uint8_t hp, const uint8_t speed, const uint16_t fight_value, const uint16_t ai_value, 
                      const Resources resources, 
                      const bool is_undead, const bool is_unliving, const bool is_flying, const bool is_ranged, const bool has_dragon_breath, const bool has_attack_adjacent );

            Creature(const Creature& creature);

            Creature(const Creature* creature);

            ~Creature();

            // straight-forward logical limits just in case
            void Logical_Limitations_When_Constructing();

            // getters
            std::string get_name() { return unit_info._name; };

            Faction get_faction() { return unit_info._faction; };
            std::string get_faction_as_string();

            uint8_t get_level() { return unit_info._level; };

            bool get_is_upgraded() { return unit_info._is_upgraded; };

            uint8_t get_growth() { return unit_info._growth; };

            Morale get_morale() { return unit_info._morale; };

            Luck get_luck() { return unit_info._luck; };

            bool get_needs_2_hexes_in_battle() { return unit_info._needs_2_hexes_in_battle; };

            uint8_t get_att() { return battle_stats._att; };

            uint8_t get_def() { return battle_stats._def; };

            uint8_t get_shots() { return battle_stats._shots; };

            uint8_t get_min_dmg() { return battle_stats._min_dmg; };

            uint8_t get_max_dmg() { return battle_stats._max_dmg; };

            uint8_t get_hp() { return battle_stats._hp; };

            uint8_t get_speed() { return battle_stats._speed; };

            uint16_t get_fight_value() { return battle_stats._fight_value; };

            uint16_t get_ai_value() { return battle_stats._ai_value; };

            uint16_t get_gold() { return cost._gold; };

            uint16_t get_mercury() { return cost._mercury; };

            uint16_t get_sulfur() { return cost._sulfur; }; 
            
            uint16_t get_crystals() { return cost._crystals; };
            
            uint16_t get_gems() { return cost._gems; };

            bool get_is_undead() { return special_abilities._is_undead; };

            bool get_is_unliving() { return special_abilities._is_unliving; };

            bool get_is_flying() { return special_abilities._is_flying; };

            bool get_is_ranged() { return special_abilities._is_ranged; };
            
            bool get_has_dragon_breath() { return special_abilities._has_dragon_breath; };

            bool get_has_attack_adjacent() { return special_abilities._has_attack_adjacent; };

            // recieve buffs or debuffs
            // recieve magic dmg
            // do_dmg + get_dmg function
            // get battle info function

            std::string get_cost();

            std::string get_special_abilities();

            void print_full_info();
};

#endif