#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <vector>
#include <map>
#include "../utilities/types.h"
#include "Resources.h"
#include "Morale_Luck.h"
#include "Spell.h"

constexpr uint8_t MAX_NUM_OF_EFFECTS = 10; // used to catch inaccuracies when constructing objects in Item_List.cpp


struct Item
{
      public:
            enum Slot
            {
                  Helmet = 1, // 1 = crown, hat
                  Cape,       // 2
                  Necklace,   // 3
                  Weapon,     // 4 = mace, trident, club
                  Shield,     // 5
                  Armor,      // 6
                  Hand,       // 7 = ring, gloves
                  Boots,      // 8
                  Pocket      // 9 = orbs, tomes, figurines, badges and others
            };

            enum Type
            {
                  None, // 0 = spell scrolls
                  Treasure,
                  Minor,
                  Major,
                  Relic
            };

      private:
            std::string _name;
            Slot _slot;
            Type _item_type;
            uint16_t _ai_value;

            struct effects
            {
                  std::string _effect = "";

                  // primary skill bonuses and penalties
                  bool _modify_attack = false;
                  int8_t _attack = 0;

                  bool _modify_defense = false;
                  int8_t _defense = 0;

                  bool _modify_power = false;
                  int8_t _power = 0;

                  bool _modify_knowledge = false;
                  int8_t _knowledge = 0;

                  // morale and luck bonuses and penalties
                  bool _modify_morale = false;
                  uint8_t _morale = 0;
                  uint8_t _decrease_enemy_morale = 0;
                  bool _disable_positive_morale = false; // Spirit of Oppression

                  bool _modify_luck = false;
                  uint8_t _luck = 0;
                  uint8_t _decrease_enemy_luck = 0;
                  bool _disable_positive_luck = false; // Hourglass of the Evil Hour
                  
                  // increase hp of all creature stacks in army
                  bool _increase_hp_1 = false; // Ring of Vitality, Ring of Life
                  bool _increase_hp_2 = false; // Vial of Lifeblood
                  bool _increase_hp_quater = false; // Elixir of Life

                  bool _give_regeneration_ability = false; // Elixir of Life

                  // increase speed of all creature stacks in army
                  bool _increase_speed_1 = false; // Necklace of Swiftness, Ring of the Wayfarer
                  bool _increase_speed_2 = false; // Cape of Velocity

                  // increase spells duration
                  bool _increase_spell_duration_1  = false; // Collar of Conjuring
                  bool _increase_spell_duration_2  = false; // Ring of Conjuring
                  bool _increase_spell_duration_3  = false; // Cape of Conjuring
                  bool _increase_spell_duration_50 = false; // Ring of the Magi
                  
                  // increase chance to resist magic damage
                  bool _increase_magic_resist_5  = false; // Garniture of Interference
                  bool _increase_magic_resist_10 = false; // Surcoat of Counterpoise
                  bool _increase_magic_resist_15 = false; // Boots of Polarity
                  bool _increase_magic_resist_20 = false; // Pendant of Reflection
                  
                  // reduce enemy spellpower
                  bool _decrease_enemy_spell_power_10 = false; // Charm of Eclipse, Seal of Sunset
                  bool _decrease_enemy_spell_power_25 = false; // Plate of Dying Light
                  
                  // immunity bonuses and penalties
                  bool _immune_to_dispel           = false; // Sphere of Permanence
                  bool _immune_to_curse            = false; // Pendant of Holiness
                  bool _immune_to_forgetfulness    = false; // Pendant of Total Recall
                  bool _immune_to_blind            = false; // Pendant of Second Sight
                  bool _immune_to_hypnotize        = false; // Pendant of Free Will
                  bool _immune_to_berserk          = false; // Pendant of Dispassion
                  bool _immune_to_destroy_undead   = false; // Pendant of Death
                  bool _immune_to_death_ripple     = false; // Pendant of Life
                  bool _immune_to_lightning_bolt   = false; // Pendant of Negativity
                  bool _immune_to_chain_lightning  = false; // Pendant of Negativity
                  bool _immune_to_armageddon       = false; // Armageddon's Blade
                  bool _immune_to_spells_level_1_4 = false; // Power of the Dragon Father
                  bool _no_immunities              = false; // Orb of Vulnerability
                 
                  // adds spells to spellbook
                  bool _add_all_air_spells        = false; // Tome of Air
                  bool _add_all_water_spells      = false; // Tome of Water
                  bool _add_all_earth_spells      = false; // Tome of Earth
                  bool _add_all_fire_spells       = false; // Tome of Fire
                  bool _add_all_level_5_spells    = false; // Spellbinder's Hat
                  bool _add_titans_lightning_bolt = false; // Titan's Thunder
                  // spellscrolls need to be added here
                 
                  // movement points
                  bool _increase_land_movement_points_200 = false; // Equestrian's Gloves
                  bool _increase_land_movement_points_400 = false; // Boots of Speed
                  bool _increase_sea_movement_points_500  = false; // Sea Captain's Hat	
                  bool _increase_sea_movement_points_1000 = false; // Necklace of Ocean Guidance
                  bool _no_rough_terrain_penalty          = false; // Wayfarer's Boots

                  // increase mana points regeneration per day
                  bool _mana_regeneration_1    = false; // Charm of Mana
                  bool _mana_regeneration_2    = false; // Talisman of Mana
                  bool _mana_regeneration_3    = false; // Mystic Orb of Mana
                  bool _mana_regeneration_full = false; // Wizard's Well

                  // generate resources per day
                  bool _generates_gold_500    = false; // Endless Purse of Gold	
                  bool _generates_gold_750    = false; // Endless Bag of Gold	
                  bool _generates_gold_1000   = false; // Endless Sack of Gold	
                  bool _generates_gold_4750   = false; // Golden Goose
                  bool _generates_wood        = false; // Inexhaustible Cart of Lumber
                  bool _generates_ore         = false; // Inexhaustible Cart of Ore
                  bool _generates_mercury     = false; // Everpouring Vial of Mercury
                  bool _generates_sulfur      = false; // Eversmoking Ring of Sulfur
                  bool _generates_crystal     = false; // Everflowing Crystal Cloak
                  bool _generates_gem         = false; // Ring of Infinite Gems
                  bool _generates_resources_4 = false; // Cornucopia
                  
                  // Create a map of all special abilities, refering to the fields in the struct accordingly.
                  std::map< std::string, std::vector<bool*> > create_map_of_all_effects();

                  // Fill the effects struct according to the passed effect string.
                  void fill_effects();

                  // Fill the string in the field
                  effects(std::string effect) : _effect(effect) {};
            }effects;

            struct cost
            {
                  uint16_t _gold     = 0;
                  uint16_t _mercury  = 0;
                  uint16_t _sulfur   = 0; 
                  uint16_t _crystals = 0;
                  uint16_t _gems     = 0;

                  // Constructs a private structure containing data used when purchasing an item
                  cost( const Resources resources ) : _gold(resources.Gold), _mercury(resources.Mercury), _sulfur(resources.Sulfur), _crystals(resources.Crystals), _gems(resources.Gems)
                  {};
            }cost;

      public:
            // Parametrized constructor (no default constructor allowed) for every item besides spellscrolls.
            Item( const std::string name, const Slot slot, const Type item_type, const Resources resources, const std::string effect );

            // Constructor for spellscrolls.
            Item( Spell& spellscroll, const Resources resources );

            ~Item();

            std::string get_name() { return _name; };

            Slot get_slot() { return _slot; };
            std::string get_slot_as_string();

            Type get_type() { return _item_type; };
            std::string get_type_as_string();

            uint16_t get_ai_value() { return _ai_value; };

            std::string get_effect() { return effects._effect; };

            int8_t get_attack_bonus()    { return effects._modify_attack    * effects._attack;    };
            int8_t get_defense_bonus()   { return effects._modify_defense   * effects._defense;   };
            int8_t get_power_bonus()     { return effects._modify_power     * effects._power;     };
            int8_t get_knowledge_bonus() { return effects._modify_knowledge * effects._knowledge; };

            uint8_t get_morale_bonus() { return effects._modify_morale * effects._morale; };
            uint8_t get_luck_bonus()   { return effects._modify_luck   * effects._luck;   };

            uint8_t get_decrease_enemy_morale_bonus() { return -effects._modify_morale * effects._decrease_enemy_morale; };
            uint8_t get_decrease_enemy_luck_bonus()   { return -effects._modify_luck   * effects._decrease_enemy_luck;   };

            bool get_disable_positive_morale() { return effects._disable_positive_morale; };
            bool get_disable_positive_luck()   { return effects._disable_positive_luck;   };

            bool get_increase_hp_1() { return effects._increase_hp_1; }
            bool get_increase_hp_2() { return effects._increase_hp_1; }

            bool get_increase_speed_1() { return effects._increase_speed_1; }
            bool get_increase_speed_2() { return effects._increase_speed_2; }

            uint8_t get_decrease_enemy_spell_power_10() { return -effects._decrease_enemy_spell_power_10; };
            uint8_t get_decrease_enemy_spell_power_25() { return -effects._decrease_enemy_spell_power_25; };

            uint16_t get_gold() { return cost._gold; };

            uint16_t get_mercury() { return cost._mercury; };

            uint16_t get_sulfur() { return cost._sulfur; };

            uint16_t get_crystals() { return cost._crystals; };

            uint16_t get_gems() { return cost._gems; };
            
            std::string get_cost();

            void print_full_info();
};


#endif