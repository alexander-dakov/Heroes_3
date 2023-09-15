#ifndef HERO_H
#define HERO_H

#include <iostream>
#include "utilities/types.h"
#include "Skills/Specialty_List.h"
#include "Skills/Secondary_Skill_List.h"
#include "Heroes/Morale_Luck.h"
#include "Items/Item.h"
#include "Spells/Spellbook.h"
#include "Creature/Creature_stack.h"
#include "Towns/Faction.h"

#define MAX_SECONDARY_SKILLS (8)

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
                  uint8_t _defence;
                  uint8_t _power;
                  uint8_t _knowledge;

                  primary_skills( uint8_t attack, uint8_t defence, uint8_t power, uint8_t knowledge ) : 
                                  _attack(attack), _defence(defence), _power(power), _knowledge(knowledge)
                                  {};
            }primary_skills;

            Specialty _specialty;

            Morale _morale;
            Luck _luck;

            uint16_t _mana;
            uint16_t _mana_left;
            
            Secondary_Skill* _secondary_skills[MAX_SECONDARY_SKILLS];
            // for(uint8_t i = 0; i < MAX_SECONDARY_SKILLS; i++)
            //      _secondary_skills[i] = &Secondary_Skill_List::None;
            
            uint16_t _moving_points;

            //items

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

            struct army_slot
            {
                  bool _is_empty;
                  Creature creature;
                  uint8_t number;
            };

      public:
            Hero( const std::string name, const Gender gender, const Class class_, const Faction faction, const Team team, const uint8_t level, const uint32_t experience, 
                  const uint8_t attack, const uint8_t defence, const uint8_t power, const uint8_t knowledge,
                  const Specialty& specialty,
                  const Morale morale, const Luck luck,
                  // secondary skills
                  const bool has_first_aid, const bool has_ammo_cart, const bool has_ballista, const bool has_catapult,
                  const bool has_spellbook );

            ~Hero();

            std::string get_name(){ return _name; };

            Gender get_gender(){ return _gender; };

            Class get_class(){ return _class; };

            Faction get_faction(){ return _faction; };

            Team get_team(){ return _team; };

            void add_level(const uint8_t level);
            uint8_t get_level(){ return _level; };

            void add_experience(const uint32_t experience);
            uint32_t get_experience(){ return _experience; };

            void set_attack(const uint8_t attack) { primary_skills._attack = attack; };
            uint8_t get_attack() {return primary_skills._attack; };

            void set_defence(const uint8_t defence) { primary_skills._defence = defence; };
            uint8_t get_defence() {return primary_skills._defence; };

            void set_power(const uint8_t power) { primary_skills._power = power; };
            uint8_t get_power() {return primary_skills._power; };

            void set_knowledge(const uint8_t knowledge) { primary_skills._knowledge = knowledge; };
            uint8_t get_knowledge() {return primary_skills._knowledge; };

            Specialty get_specialty() { return _specialty; };

            void set_morale(const Morale morale) { _morale = morale; };
            Morale get_morale() { return _morale; };

            void set_luck(const Luck luck) { _luck = luck; };
            Luck get_luck() { return _luck; };

            void set_mana(const uint16_t mana) { _mana = mana; };
            uint16_t get_mana() { return _mana; };

            void set_mana_left(const uint16_t mana_left) { _mana_left = mana_left; };
            uint16_t get_mana_left() { return _mana_left; };

            void set_secondary_skill(uint8_t i, Secondary_Skill skill) { _secondary_skills[i] = &skill; };
            Secondary_Skill* get_secondary_skill(uint8_t i) { return _secondary_skills[i]; };

            void move(uint8_t x, uint8_t y); // if map object - interact = take resources item, flag mine, fight monster/hero, enter castle

};

#endif