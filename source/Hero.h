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

#define SECONDARY_SKILLS (8)
#define ARMY_SLOTS (7)

enum Gender
{
      Male,  // 0
      Female // 1
};

enum Class
{
      Might, // 0
      Magic  // 1
};

class Hero
{
      private:
            std::string _name;
            Gender _gender;
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

            Secondary_Skill* _secondary_skills[SECONDARY_SKILLS] = {nullptr};

            Morale _morale;
            Luck _luck;

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

            // items - implement a structure with flags for possible effects from items, analogical to special abilities
            bool _has_equipped_ring_of_life          = false;
            bool _has_equipped_ring_of_vitality      = false;
            bool _has_equipped_vail_of_lifeblood     = false;
            bool _has_equipped_elixir_of_life        = true && _has_equipped_ring_of_life + _has_equipped_ring_of_vitality + _has_equipped_vail_of_lifeblood;
            bool _has_equipped_ring_of_wayfarer      = false;
            bool _has_equipped_necklace_of_swiftness = false;
            bool _has_equipped_cape_of_velocity      = false;

            // treasure chest

            Stack* army[ARMY_SLOTS] = {nullptr}; // probably would be better with unique_ptr
            // std::array<std::unique_ptr, ARMY_SLOTS> army;

            Position _position = Position(0, 0);

      public:
            Hero( const std::string name, const Gender gender, const Class hero_class, const Faction faction, const Team team, const uint8_t level, const uint32_t experience, 
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

            Class get_class(){ return _class; };
            std::string get_class_as_string();

            Faction get_faction(){ return _faction; };
            std::string get_faction_as_string();

            Team get_team(){ return _team; };
            std::string get_team_as_string();

            void add_level(const uint8_t level);
            uint8_t get_level(){ return _level; };

            void add_experience(const uint32_t experience);
            uint32_t get_experience(){ return _experience; };

            void set_attack(const uint8_t attack) { primary_skills._attack = attack; };
            uint8_t get_attack() {return primary_skills._attack; };

            void set_defense(const uint8_t defense) { primary_skills._defense = defense; };
            uint8_t get_defense() {return primary_skills._defense; };

            void set_power(const uint8_t power) { primary_skills._power = power; };
            uint8_t get_power() {return primary_skills._power; };

            void set_knowledge(const uint8_t knowledge) { primary_skills._knowledge = knowledge; };
            uint8_t get_knowledge() {return primary_skills._knowledge; };

            Specialty get_specialty() { return _specialty; };

            void set_secondary_skill(uint8_t i, Secondary_Skill skill) { _secondary_skills[i] = &skill; };
            Secondary_Skill* get_secondary_skill(uint8_t i) { return _secondary_skills[i]; };
            std::string get_secondary_skill_name(uint8_t i) { return _secondary_skills[i]->get_name(); };

            void set_morale(const Morale morale) { _morale = morale; };
            Morale get_morale() { return _morale; };

            void set_luck(const Luck luck) { _luck = luck; };
            Luck get_luck() { return _luck; };

            void set_mana(const uint16_t mana) { _mana = mana; };
            uint16_t get_mana() { return _mana; };

            void set_mana_left(const uint16_t mana_left) { _mana_left = mana_left; };
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

            // Checks if item is in treasure chest and places it in the according slot. If another item is there the other item gets moved to the treasure chest.
            void equip_item(Item& item);
            
            // Checks if item is in slot and places it in the treasure chest.
            void unequip_item(Item& item);

            // Adds a stack to the first empty slot in army.
            void add_stack_to_army(Stack* stack);
            
            // Adds a stack to a specific slot in army.
            void add_stack_to_slot(Stack* stack, uint8_t slot);

            // Removes a stack from army.
            void remove_stack(Stack& stack);

            // Removes a stack from specific slot in army.
            void remove_stack_from_position(uint8_t slot);
            
            // Swaps positions of two stacks in the same army. ALso used when one of the slots is empty.
            void swap_stack_positions();
            
            // Update battle stats of each stack according to current hero attributes. Called every time hero adds or removes creature from army, gets a new level, gets a morale/luck bonus, equips/unequips an item.
            void update_army_stats();

            void set_position(Position position) { _position = position; };
            Position get_position() { return _position; };

            void move(uint8_t x, uint8_t y); // if map object - interact = take resources item, flag mine, fight monster/hero, enter castle
            
            void print_full_info();
};

#endif