#ifndef HERO_H
#define HERO_H

#include <iostream>
#include "../utilities/types.h"
#include "Specialty.h"
#include "Secondary_Skill.h"
#include "Morale_Luck.h"
#include "Item.h"
#include "Spellbook.h"
#include "Creature_stack.h"
#include "Faction.h"
#include "Position.h"
#include "Level_Experience.h"
#include "Skills_Probability.h"

constexpr uint8_t SECONDARY_SKILL_SLOTS = 10;

constexpr uint8_t ARMY_SLOTS = 7;

constexpr uint8_t HAND_SLOTS = 2;    // one slot on each hand for rings and gloves
constexpr uint8_t POCKET_SLOTS = 5;  // for orbs, tomes, figurines, badges and others 
constexpr uint8_t CHEST_SLOTS = 100; // for storing unequipped items


enum Gender
{
      Male,  // 0
      Female // 1
};

enum Role
{
      Might, // 0
      Magic  // 1
};

enum Class
{
      Knight,       // Castle
      Cleric,       // Castle
      Ranger,       // Rampart
      Druid,        // Rampart
      Alchemist,    // Tower
      Wizard,       // Tower      
      Demoniac,     // Inferno
      Heretic,      // Inferno
      Death_Knight, // Necropolis
      Necromancer,  // Necropolis
      Overlord,     // Dungeon
      Warlock,      // Dungeon
      Barbarian,    // Stronghold
      Battle_Mage,  // Stronghold     
      Beastmaster,  // Fortress
      Witch,        // Fortress
      Planeswalker, // Conflux
      Elementalist, // Conflux
      Captain,      // Cove
      Navigator     // Cove
};

class Hero
{
      private:
            std::string _name;
            Gender _gender;
            Role _role;
            Class _class;
            Faction _faction;
            Team _team;
            uint8_t _level;
            uint32_t _experience;

            struct primary_skills
            {
                  uint8_t _attack;
                  uint8_t _defense;
                  uint8_t _power;
                  uint8_t _knowledge;

                  primary_skills( uint8_t attack, uint8_t defense, uint8_t power, uint8_t knowledge ) : 
                                  _attack(attack), _defense(defense), _power(power), _knowledge(knowledge)
                                  {};
            }primary_skills;

            Specialty _specialty;

            Secondary_Skill* _secondary_skills[SECONDARY_SKILL_SLOTS] = {nullptr}; // TO DO : add to constructors

            Morale _morale;
            Luck _luck;

            uint8_t _army_hp_bonus    = 0;
            uint8_t _army_speed_bonus = 0;

            uint16_t _mana;
            uint16_t _mana_left;
            
            uint16_t _movement_points;

            struct war_machines
            {
                  bool _has_first_aid;
                  bool _has_ammo_cart;
                  bool _has_ballista;
                  // bool _has_cannon;
                  bool _has_catapult;

                  war_machines( const bool has_first_aid = false, const bool has_ammo_cart = false, const bool has_ballista = false, const bool has_catapult = true ) :
                                _has_first_aid(has_first_aid), _has_ammo_cart(has_ammo_cart), _has_ballista(has_ballista), _has_catapult(has_catapult)
                                {};    
            }war_machines;

            bool _has_spellbook;

            struct items
            {
                  Item* helmet   = nullptr;
                  Item* cape     = nullptr;
                  Item* necklace = nullptr;
                  Item* weapon   = nullptr;
                  Item* shield   = nullptr;
                  Item* armor    = nullptr;
                  Item* hand[HAND_SLOTS] = {nullptr};
                  Item* boots = nullptr;
                  Item* pocket[POCKET_SLOTS] = {nullptr};
            }items;

            Item* chest[CHEST_SLOTS] = {nullptr};

            // items - implement a structure with flags for possible effects from items, analogical to special abilities
            bool _has_equipped_elixir_of_life = false;

            Stack* army[ARMY_SLOTS] = {nullptr}; // probably would be better with unique_ptr
            // std::array<std::unique_ptr, ARMY_SLOTS> army;

            Position _position = Position(0, 0);

      public:
            Hero( const std::string name, const Gender gender, const Role hero_role, const Faction faction, const Team team, const uint8_t level, const uint32_t experience, 
                  const uint8_t attack, const uint8_t defense, const uint8_t power, const uint8_t knowledge,
                  const Specialty& specialty,
                  const Morale morale, const Luck luck,
                  // secondary skills
                  struct war_machines war_machinery,
                  const bool has_spellbook );

            ~Hero();

            std::string get_name(){ return _name; };

            Gender get_gender(){ return _gender; };
            std::string get_gender_as_string();

            Role get_role(){ return _role; };
            std::string get_role_as_string();

            Class get_class(){ return _class; };
            std::string get_class_as_string();

            Faction get_faction(){ return _faction; };
            std::string get_faction_as_string();

            Team get_team(){ return _team; };
            std::string get_team_as_string();

            void set_level(const uint8_t level) { _level = level; };
            void add_level(const uint8_t level);
            uint8_t get_level(){ return _level; };

            void add_to_primary_on_level_up(uint8_t probability, const uint8_t* array);

            void set_experience(const uint32_t experience) { _experience = experience; };
            void add_experience(const uint32_t experience);
            uint32_t get_experience(){ return _experience; };

            void set_attack(const uint8_t attack) { primary_skills._attack = attack; };
            void add_attack(const  int8_t attack) { primary_skills._attack = std::max(0, primary_skills._attack + attack); }; // bug prone
            uint8_t get_attack() {return primary_skills._attack; };

            void set_defense(const uint8_t defense) { primary_skills._defense = defense; };
            void add_defense(const  int8_t defense) { primary_skills._defense = std::max(0, primary_skills._defense + defense); }; // bug prone
            uint8_t get_defense() {return primary_skills._defense; };

            void set_power(const uint8_t power) { primary_skills._power = power; };
            void add_power(const  int8_t power) { primary_skills._power = std::max(0, primary_skills._power + power); }; // bug prone
            uint8_t get_power() {return primary_skills._power; };

            void set_knowledge(const uint8_t knowledge) { primary_skills._knowledge = knowledge; };
            void add_knowledge(const  int8_t knowledge) { primary_skills._knowledge = std::max(0, primary_skills._knowledge + knowledge); }; // bug prone
            uint8_t get_knowledge() {return primary_skills._knowledge; };

            Specialty get_specialty() { return _specialty; };

            void set_secondary_skill(const uint8_t i, Secondary_Skill skill) { _secondary_skills[i] = &skill; };
            Secondary_Skill* get_secondary_skill(uint8_t i) { return _secondary_skills[i]; };
            std::string get_secondary_skill_name(uint8_t i) { return _secondary_skills[i]->get_name(); };

            void set_army_hp_bonus(const uint8_t bonus) { _army_hp_bonus = bonus; };
            uint8_t get_army_hp_bonus()                 { return _army_hp_bonus;  };

            void set_army_speed_bonus(const uint8_t bonus) { _army_speed_bonus = bonus; };
            uint8_t get_army_speed_bonus()                 { return _army_speed_bonus;  };

            void set_morale(const Morale morale) { _morale = morale; };
            void add_morale(const Morale morale) { _morale = static_cast<Morale>( std::min( std::max( static_cast<int8_t>(_morale) + static_cast<int8_t>(morale), -3), 3) ); };
            Morale get_morale() { return _morale; };

            void set_luck(const Luck luck) { _luck = luck; };
            void add_luck(const Luck luck) { _luck = static_cast<Luck>( std::min( std::max( static_cast<int8_t>(_luck) + static_cast<int8_t>(luck), -3), 3) ); };
            Luck get_luck() { return _luck; };

            void set_mana(const uint16_t mana) { _mana = mana; };
            void update_mana() { _mana = 10*get_knowledge(); };
            uint16_t get_mana() { return _mana; };

            void set_mana_left(const uint16_t mana_left) { _mana_left = mana_left; };
            void add_mana_left(const uint16_t mana) { _mana_left += mana; };
            void reset_mana_left() { _mana_left = _mana; };
            uint16_t get_mana_left() { return _mana_left; };

            void set_movement_points(const uint16_t movement_points) { _movement_points = movement_points; };
            void add_movement_points(const uint16_t movement_points) { _movement_points += movement_points; };
            uint16_t get_movement_points() { return _movement_points; };

            bool get_has_first_aid() { return war_machines._has_first_aid; };
            bool get_has_ammo_cart() { return war_machines._has_ammo_cart; };
            bool get_has_ballista()  { return war_machines._has_ballista;  };
            // bool get_has_cannon()    { return war_machines._has_cannon;    };
            bool get_has_catapult()  { return war_machines._has_catapult;  };

            bool get_has_spellbook() { return _has_spellbook; };

            // Checks if slot is taken - if yes - tries to send the item to chest. If not - places it in slot.
            void pick_up_item(Item* item);

            // Checks if item is in treasure chest and if yes, checks if the item slot is empty. If empty - calls equip_item(), if not empty - calls unequip_item() on the artifact in the slot and than calls equip_item() on the parsed one.
            void equip_item_from_chest(Item* item);

            // Assigns the item to the correct slot and allows hero to gain the item's bonuses.
            void equip_item(Item* item);

            // Checks if item is equiped, places it in the treasure chest and hero losses the item's bonuses.
            void unequip_item(Item* item);

            // Checks if chest has a free slot. If yes - places the item there. If not - prints a message.
            bool add_item_to_chest(Item* item);

            // Prints the names and effects of all equipped items.
            void print_equipped_items();
            
            // Prints the names and effects of all equipped items.
            void print_unequipped_items();

            // Adds a stack to the first empty slot in army.
            void add_stack_to_army(Stack* stack);
            
            // Adds a stack to a specific slot in army.
            void add_stack_to_slot(Stack* stack, const uint8_t slot);

            // Removes a stack from army.
            void remove_stack(Stack& stack);

            // Removes a stack from specific slot in army.
            void remove_stack_from_position(const uint8_t slot);
            
            // Swaps positions of two stacks in the same army. ALso used when one of the slots is empty.
            void swap_stack_positions();
            
            // Update battle stats of each stack according to current hero attributes. Called every time hero adds or removes creature from army, gets a new level, gets a morale/luck bonus, equips/unequips an item.
            void update_army_stats();

            void set_position(const Position position) { _position = position; };
            Position get_position() { return _position; };

            void move(const uint8_t x, const uint8_t y); // if map object - interact = take resources item, flag mine, fight monster/hero, enter castle
            
            void print_full_info();
};

#endif