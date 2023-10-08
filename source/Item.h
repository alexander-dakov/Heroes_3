#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include "../utilities/types.h"
#include "Resources.h"
#include "Spell.h"

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

enum class Type
{
      None, // 0 = spell scrolls
      Treasure,
      Minor,
      Major,
      Relic
};

class Item
{
      private:
            std::string _name;
            Slot _slot;
            Type _item_type;
            uint16_t _ai_value;
            std::string _description;

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
            Item( const std::string name, const Slot slot, const Type item_type, const Resources resources, const std::string description );

            // Constructor for spellscrolls.
            Item( Spell& spellscroll, const Resources resources );

            ~Item();

            std::string get_name() { return _name; };

            Slot get_slot() { return _slot; };
            std::string get_slot_as_string();

            Type get_type() { return _item_type; };
            std::string get_type_as_string();

            uint16_t get_ai_value() { return _ai_value; };

            std::string get_description() { return _description; };

            uint16_t get_gold() { return cost._gold; };

            uint16_t get_mercury() { return cost._mercury; };

            uint16_t get_sulfur() { return cost._sulfur; };

            uint16_t get_crystals() { return cost._crystals; };

            uint16_t get_gems() { return cost._gems; };
            
            std::string get_cost();

            void print_full_info();
};


#endif