#ifndef CREATURE_H
#define CREATURE_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include "../utilities/types.h"
#include "Faction.h"
#include "Morale_Luck.h"
#include "Resources.h"
#include "Skill_level.h"

constexpr uint8_t max_num_of_special_abilities = 6;

enum class Upgrade_level
{
      None = 0,
      First,
      Second
};
struct Creature
{
      private:

            struct unit_info
            {
                  std::string _name;
                  Faction _faction;
                  uint8_t _level;
                  Upgrade_level _upgrade;
                  uint8_t _growth;
                  bool _needs_2_hexes_in_battle;

                  // Constructs a private structure containing data used for overview
                  unit_info( std::string name, Faction faction, uint8_t level, Upgrade_level upgrade, uint8_t growth, bool needs_2_hexes_in_battle ) :
                             _name(name), _faction(faction), _level(level), _upgrade(upgrade), _growth(growth), _needs_2_hexes_in_battle(needs_2_hexes_in_battle) 
                             {};
            }unit_info;

            struct battle_stats
            {
                  uint8_t _att;
                  uint8_t _def;
                  uint8_t _shots;
                  uint8_t _min_dmg;
                  uint8_t _max_dmg;
                  uint16_t _hp;
                  uint8_t _speed;
                  Morale _morale;
                  Luck _luck;
                  uint16_t _fight_value;
                  uint32_t _ai_value;

                  // Constructs a private structure containing data used during battles
                  battle_stats( const uint8_t att, const uint8_t def, const uint8_t shots, const uint8_t min_dmg, const uint8_t max_dmg, 
                                const uint16_t hp, const uint8_t speed, Morale morale, Luck luck, const uint16_t fight_value, const uint32_t ai_value ) : 
                                _att(att), _def(def), _shots(shots), _min_dmg(min_dmg), _max_dmg(max_dmg), _hp(hp), _speed(speed),
                                _morale(morale), _luck(luck) ,_fight_value(fight_value), _ai_value(ai_value)
                                {};
            }battle_stats;

            struct cost
            {
                  uint16_t _gold     = 0;
                  uint16_t _mercury  = 0;
                  uint16_t _sulfur   = 0; 
                  uint16_t _crystals = 0;
                  uint16_t _gems     = 0;

                  // Constructs a private structure containing data used when purchasing a unit
                  cost( const Resources resources ) : _gold(resources.Gold), _mercury(resources.Mercury), _sulfur(resources.Sulfur), _crystals(resources.Crystals), _gems(resources.Gems)
                  {};
            }cost;
            
            // All special abilities placed into booleans.
            struct special_abilities
            {
                  std::string _abilities = "";

                  // living type
                  bool _is_undead    = false; // all Necropolis units
                  bool _is_bloodless = false; // Gagroyles, Golems, Elementals

                  // attack type
                  bool _is_flying = false;
                  bool _is_ranged = false;
                  
                  // attack penalty
                  bool _no_melee_penalty    = false; // Mage, Arch Mage, Titan
                  bool _no_obstacle_penalty = false; // Mage, Arch Mage, Zealot
                  bool _no_range_penalty    = false; // Sharpshooter

                  // attack style
                  bool _strike_and_return      = false; // Harpy, Harpy Hag
                  bool _can_attack_siege_walls = false; // Cyclops, Cyclops King

                  // attack bonus
                  bool _has_ferocity                = false; // Ayssid; Effect : if a unit from the attacked stack dies, a seconda attack follows 
                  bool _has_double_attack           = false; // Marksman, Crusader, Grand Elf
                  bool _has_jousting                = false; // Cavalier, Champion
                  bool _has_revenge                 = false; // Haspid; Effect : attacks deal a bit more damage after stack suffers damage
                  bool _has_3_headed_attack         = false; // Cerberus
                  bool _has_fireball_attack         = false; // Magog
                  bool _has_cloud_attack            = false; // Lich, Power Lich
                  bool _has_attack_adjacent_enemies = false; // Hydra, Chaos Hydra
                  bool _has_attack_adjacent_hexes   = false; // Magic Elemental, Psychic Elemental
                  bool _has_breath_attack           = false; // Firebird, Pheonix, Dragons: Green + Gold + Red + Black + Faerie + Rust + Azure
                  bool _hates_efreeti               = false; // Genie, Master Genie
                  bool _hates_genies                = false; // Efreet, Efreet Sultan
                  bool _hates_devils                = false; // Angel, Arch Angel
                  bool _hates_angels                = false; // Devil, Arch Devil
                  bool _hates_black_dragons         = false; // Titan
                  bool _hates_titans                = false; // Black Dragon
                  bool _ignore_enemy_defense_40     = false; // Behemoth
                  bool _ignore_enemy_defense_80     = false; // Ancient Behemoth

                  // defense bonus
                  bool _ignore_enemy_attack_30     = false; // Nix
                  bool _ignore_enemy_attack_60     = false; // Nix Warrior

                  // retaliation
                  bool _has_two_retaliations       = false; // Griffin
                  bool _has_unlimited_retaliations = false; // Royal Griffin
                  bool _no_enemy_retaliation       = false; // Naga, Naga Queen, Devil, Arch Devil
                  
                  // casts per turn
                  bool _casts_regeneration = false;
                  bool _casts_mana_drain   = false; // Wraith; Effect = enemy hero's spell points are reduced by 2.

                  // casts after attack
                  bool _casts_binding                             = false; // Dendroid Guard, Dendroid Soldier
                  bool _casts_life_drain                          = false; // Vampire Lord
                  bool _casts_dispell_on_buffs                    = false; // Serpent Fly, Dragon Fly
                  bool _casts_weakness                            = false; // Sea Witch
                  bool _casts_advanced_weakness                   = false; // Dragon Fly, Sorceress
                  bool _casts_disrupting_ray_on_weakened          = false; // Sea Witch
                  bool _casts_advanced_disrupting_ray_on_weakened = false; // Sorceress

                  // some chance of cast per attack
                  bool _can_cast_disease          = false; // Zombie
                  bool _can_cast_curse            = false; // Black Knigt, Dread Knight
                  bool _can_cast_aging            = false; // Ghost Dragon
                  bool _can_cast_poison           = false; // Wyvern Monarch, Sea Serpent, Haspid
                  bool _can_cast_paralyzing_venom = false; // Scorpicore
                  bool _can_cast_fear             = false; // Azure Dragon
                  bool _can_cast_petrify          = false; // Medusa, Medusa Queen, Basilisk, Greater Basilisk
                  bool _can_cast_blind            = false; // Unicorn, War Unicorn
                  bool _can_cast_lightning_strike = false; // Thunderbird
                  bool _can_cast_death_blow       = false; // Dread Knight
                  bool _can_cast_death_stare      = false; // Mighty Gorgon
                  bool _can_cast_accurate_shot    = false; // Sea Dog
                  bool _can_cast_acid_breath      = false; // Rust Dragon
                  bool _can_cast_hypnotize        = false; // Fangarm; Effect = like the spell but occurs according to formula

                  // casts when attacked
                  bool _casts_fire_shield = false; // Efreet Sultan

                  // some chance of cast upon first death
                  bool _can_cast_rebirth = false; // Pheonix

                  // can cast spell in battle - player's choice
                  bool _is_spellcaster                 = false; // Master Genie
                  bool _can_cast_ressurection          = false; // Arch Angel
                  bool _can_cast_advanced_fortune      = false; // Leprechaun
                  bool _can_cast_advanced_mirth        = false; // Satyr
                  bool _can_cast_summon_demons         = false; // Pit Lord
                  bool _can_cast_bloodlust             = false; // Ogre Mage
                  bool _can_cast_protection_from_air   = false; // Storm Elemental
                  bool _can_cast_protection_from_water = false; // Ice Elemental
                  bool _can_cast_protection_from_fire  = false; // Energy Elemental
                  bool _can_cast_protection_from_earth = false; // Magma Elemental
                  
                  // resistances
                  bool _has_magic_resist_20   = false; // Dwarf
                  bool _has_magic_resist_40   = false; // Battle Dwarf
                  bool _has_magic_resist_aura = false; // Battle Dwarf
                  bool _has_magic_mirror      = false; // Faerie Dragon

                  // damage reduciton
                  bool _reduce_magic_damage_50 = false; // Stone Golem
                  bool _reduce_magic_damage_75 = false; // Iron Golem
                  bool _reduce_magic_damage_80 = false; // Steel Golem
                  bool _reduce_magic_damage_85 = false; // Gold Golem
                  bool _reduce_magic_damage_95 = false; // Diamond Golem

                  // immunities
                  bool _is_immune_to_jousting             = false; // Pikeman, Halberdier
                  bool _is_immune_to_fear                 = false; // Azure Dragon
                  bool _is_immune_to_blind                = false; // Troglodyte
                  bool _is_immune_to_petrify              = false; // Infernal Troglodyte
                  bool _is_immune_to_magic_arrow          = false; // Efreet, Efreet Sultan, Fire & Energy Elemental
                  bool _is_immune_to_ice_bolt             = false; // Water & Ice Elemental
                  bool _is_immune_to_frost_ring           = false; // Water & Ice Elemental
                  bool _is_immune_to_lightning_bolt       = false; // Earth & Magma Elemental
                  bool _is_immune_to_chain_lightning      = false; // Earth & Magma Elemental
                  bool _is_immune_to_meteor_shower        = false; // Air & Storm Elemental
                  bool _is_immune_to_armageddon           = false; // Earth & Magma Elemental
                  bool _is_immune_to_fire_spells          = false; // Efreet, Efreet Sultan, Fire & Energy Elemental
                  bool _is_immune_to_mind_spells          = false; // Giant, Titan
                  bool _is_immune_to_spells_level_1_3     = false; // Green Dragon, Red Dragon
                  bool _is_immune_to_spells_level_1_4     = false; // Gold Dragon
                  bool _is_immune_to_all_spells           = false; // Black Dragon
                  
                  // vulnerabilities
                  bool _is_vulnerable_to_ice_bolt        = false; // Fire & Energy Elemental
                  bool _is_vulnerable_to_frost_ring      = false; // Fire & Energy Elemental
                  bool _is_vulnerable_to_lightning_bolt  = false; // Air & Storm Elemental
                  bool _is_vulnerable_to_chain_lightning = false; // Air & Storm Elemental
                  bool _is_vulnerable_to_meteor_shower   = false; // Earth & Magma Elemental
                  bool _is_vulnerable_to_fire_ball       = false; // Water & Ice Elemental
                  bool _is_vulnerable_to_inferno         = false; // Water & Ice Elemental
                  bool _is_vulnerable_to_armageddon      = false; // Air & Storm Elemental, Water & Ice Elemental
                  
                  // morale modifiers
                  bool _minimum_morale_1 = false; // Minotaur, Minotaur King
                  bool _luck_is_always_1 = false; // Halfling

                  // whole army morale and luck modifiers
                  bool _increases_alias_morale_1 = false; // Angel, Arch Angel
                  bool _decreases_enemy_morale_1 = false; // Bone Dragon, Ghost Dragon
                  bool _decreases_enemy_luck_1   = false; // Devil
                  bool _decreases_enemy_luck_2   = false; // Arch Devil
                  bool _doubles_luck_chance      = false; // Leprechaun

                  // mana points modifiers
                  bool _magic_channel = false; // Familiar; Effect = 20% of mana spent from enemy hero is added to hero's mana when familiars are present.
                  bool _magic_damper = false;  // Pegasus, Silver Pegasus; Effect = enemy hero's spells during combat cost 2 mana points more. Effects continues after Pegasi perish.
                  bool _mana_economy = false;  // Mage, Arch Mage; Effect = hero's spells during combat cost 2 mana points less.
                  
                  // effects on adventure map
                  bool _has_spying         = false; // Rogue
                  bool _is_sandwalker      = false; // Nomad
                  bool _generates_crystals = false; // Crystal Dragon
                  
                  // Create a map of all special abilities, refering to the fields in the struct accordingly.
                  std::map< std::string, std::vector<bool*> > create_map_of_all_abilities();

                  // Fill the special abilities struct according to the passed special abilities string.
                  void fill_special_abilities();

                  // Fill the string in the field
                  special_abilities(std::string abilities) : _abilities(abilities) {};
            }special_abilities;
         
      public:
            // Parametrized constructor (no default constructor allowed). Calls Logical_Limitations_When_Constructing().
            Creature( const std::string name, const Faction faction, const uint8_t level, const Upgrade_level upgrade, const uint8_t growth, const bool needs_2_hexes_in_battle,
                      const uint8_t att, const uint8_t def, const uint8_t shots, const uint8_t min_dmg, const uint8_t max_dmg, const uint16_t hp, const uint8_t speed, const Morale morale, const Luck luck, const uint16_t fight_value, const uint32_t ai_value, 
                      const Resources resources, 
                      const std::string abilities );
            
            // Copy constructors by reference. Calls Logical_Limitations_When_Constructing().
            Creature(const Creature& creature);

            // Copy constructors by pointer. Calls Logical_Limitations_When_Constructing().
            Creature(const Creature* creature);

            // Destructor
            ~Creature();

            // Straight-forward logical limits that need to be set when constructing.
            void logical_limitations();

            std::string get_name() { return unit_info._name; };

            Faction get_faction() { return unit_info._faction; };
            std::string get_faction_as_string();

            uint8_t get_level() { return unit_info._level; };

            Upgrade_level get_upgrade() { return unit_info._upgrade; };

            uint8_t get_growth() { return unit_info._growth; };

            bool get_needs_2_hexes_in_battle() { return unit_info._needs_2_hexes_in_battle; };

            uint8_t get_att() { return battle_stats._att; };

            uint8_t get_def() { return battle_stats._def; };

            uint8_t get_shots() { return battle_stats._shots; };

            uint8_t get_min_dmg() { return battle_stats._min_dmg; };

            uint8_t get_max_dmg() { return battle_stats._max_dmg; };

            uint16_t get_hp() { return battle_stats._hp; };

            uint8_t get_speed() { return battle_stats._speed; };

            Morale get_morale() { return battle_stats._morale; };

            Luck get_luck() { return battle_stats._luck; };

            uint16_t get_fight_value() { return battle_stats._fight_value; };

            uint32_t get_ai_value() { return battle_stats._ai_value; };

            uint16_t get_gold() { return cost._gold; };

            uint16_t get_mercury() { return cost._mercury; };

            uint16_t get_sulfur() { return cost._sulfur; }; 
            
            uint16_t get_crystals() { return cost._crystals; };
            
            uint16_t get_gems() { return cost._gems; };

            bool get_is_undead()    { return special_abilities._is_undead;    };
            bool get_is_bloodless() { return special_abilities._is_bloodless; };

            bool get_is_flying() { return special_abilities._is_flying; };
            bool get_is_ranged() { return special_abilities._is_ranged; };

            bool get_no_melee_penalty()    { return special_abilities._no_melee_penalty;    };
            bool get_no_obstacle_penalty() { return special_abilities._no_obstacle_penalty; };
            bool get_no_range_penalty()    { return special_abilities._no_range_penalty;    };

            bool get_strike_and_return()      { return special_abilities._strike_and_return;      };
            bool get_can_attack_siege_walls() { return special_abilities._can_attack_siege_walls; };

            bool get_has_double_attack()           { return special_abilities._has_double_attack;           };
            bool get_has_jousting()                { return special_abilities._has_jousting;                };
            bool get_has_revenge()                 { return special_abilities._has_revenge;                 };
            bool get_has_3_headed_attack()         { return special_abilities._has_3_headed_attack;         };
            bool get_has_fireball_attack()         { return special_abilities._has_fireball_attack;         };
            bool get_has_cloud_attack()            { return special_abilities._has_cloud_attack;            };
            bool get_has_attack_adjacent_enemies() { return special_abilities._has_attack_adjacent_enemies; };
            bool get_has_attack_adjacent_hexes()   { return special_abilities._has_attack_adjacent_hexes;   };
            bool get_has_breath_attack()           { return special_abilities._has_breath_attack;           };
            bool get_hates_efreeti()               { return special_abilities._hates_efreeti;               };
            bool get_hates_genies()                { return special_abilities._hates_genies;                };
            bool get_hates_devils()                { return special_abilities._hates_devils;                };
            bool get_hates_angels()                { return special_abilities._hates_angels;                };
            bool get_hates_black_dragons()         { return special_abilities._hates_black_dragons;         };
            bool get_hates_titans()                { return special_abilities._hates_titans;                };
            bool get_ignore_enemy_defense_40()     { return special_abilities._ignore_enemy_defense_40;     };
            bool get_ignore_enemy_defense_80()     { return special_abilities._ignore_enemy_defense_80;     };

            bool get_ignore_enemy_attack_30() { return special_abilities._ignore_enemy_attack_30; };
            bool get_ignore_enemy_attack_60() { return special_abilities._ignore_enemy_attack_60; };

            bool get_has_two_retaliations()       { return special_abilities._has_two_retaliations;       };
            bool get_has_unlimited_retaliations() { return special_abilities._has_unlimited_retaliations; };
            bool get_no_enemy_retaliation()       { return special_abilities._no_enemy_retaliation;       };
            
            bool get_casts_regeneration() { return special_abilities._casts_regeneration; };
            bool get_casts_mana_drain()   { return special_abilities._casts_mana_drain;   };

            bool get_minimum_morale_1() { return special_abilities._minimum_morale_1; };
            bool get_luck_is_always_1() { return special_abilities._luck_is_always_1; };
            
            bool get_increases_alias_morale_1() { return special_abilities._increases_alias_morale_1; };
            bool get_decreases_enemy_morale_1() { return special_abilities._decreases_enemy_morale_1; };
            bool get_decreases_enemy_luck_1()   { return special_abilities._decreases_enemy_luck_1;   };
            bool get_decreases_enemy_luck_2()   { return special_abilities._decreases_enemy_luck_2;   };
            bool get_doubles_luck_chance()      { return special_abilities._doubles_luck_chance;      };

            bool get_casts_binding()                             { return special_abilities._casts_binding;                             };
            bool get_casts_life_drain()                          { return special_abilities._casts_life_drain;                          };
            bool get_casts_dispell_on_buffs()                    { return special_abilities._casts_dispell_on_buffs;                    };
            bool get_casts_weakness()                            { return special_abilities._casts_weakness;                            };
            bool get_casts_advanced_weakness()                   { return special_abilities._casts_advanced_weakness;                   };
            bool get_casts_disrupting_ray_on_weakened()          { return special_abilities._casts_disrupting_ray_on_weakened;          };
            bool get_casts_advanced_disrupting_ray_on_weakened() { return special_abilities._casts_advanced_disrupting_ray_on_weakened; };

            bool get_can_cast_disease()          { return special_abilities._can_cast_disease;          };
            bool get_can_cast_curse()            { return special_abilities._can_cast_curse;            };
            bool get_can_cast_aging()            { return special_abilities._can_cast_aging;            };
            bool get_can_cast_poison()           { return special_abilities._can_cast_poison;           };
            bool get_can_cast_lightning_strike() { return special_abilities._can_cast_lightning_strike; };
            bool get_can_cast_paralyzing_venom() { return special_abilities._can_cast_paralyzing_venom; };
            bool get_can_cast_fear()             { return special_abilities._can_cast_fear;             };
            bool get_can_cast_petrify()          { return special_abilities._can_cast_petrify;          };
            bool get_can_cast_blind()            { return special_abilities._can_cast_blind;            };
            bool get_can_cast_death_blow()       { return special_abilities._can_cast_death_blow;       };
            bool get_can_cast_death_stare()      { return special_abilities._can_cast_death_stare;      };
            bool get_can_cast_accurate_shot()    { return special_abilities._can_cast_accurate_shot;    };
            bool get_can_cast_acid_breath()      { return special_abilities._can_cast_acid_breath;      };
            bool get_can_cast_hypnotize()        { return special_abilities._can_cast_hypnotize;        };

            bool get_casts_fire_shield() { return special_abilities._casts_fire_shield; };

            bool get_can_cast_rebirth() { return special_abilities._can_cast_rebirth; };

            bool get_is_spellcaster()                 { return special_abilities._is_spellcaster;                 };
            bool get_can_cast_ressurection()          { return special_abilities._can_cast_ressurection;          };
            bool get_can_cast_advanced_fortune()      { return special_abilities._can_cast_advanced_fortune;      };
            bool get_can_cast_advanced_mirth()        { return special_abilities._can_cast_advanced_mirth;        };
            bool get_can_cast_bloodlust()             { return special_abilities._can_cast_bloodlust;             };
            bool get_can_cast_protection_from_air()   { return special_abilities._can_cast_protection_from_air;   };
            bool get_can_cast_protection_from_water() { return special_abilities._can_cast_protection_from_water; };
            bool get_can_cast_protection_from_fire()  { return special_abilities._can_cast_protection_from_fire;  };
            bool get_can_cast_protection_from_earth() { return special_abilities._can_cast_protection_from_earth; };
            
            bool get_has_magic_resist_20()   { return special_abilities._has_magic_resist_20;   };
            bool get_has_magic_resist_40()   { return special_abilities._has_magic_resist_40;   };
            bool get_has_magic_resist_aura() { return special_abilities._has_magic_resist_aura; };
            bool get_has_magic_mirror()      { return special_abilities._has_magic_mirror;      };

            bool get_reduce_magic_damage_50() { return special_abilities._reduce_magic_damage_50; };
            bool get_reduce_magic_damage_75() { return special_abilities._reduce_magic_damage_75; };
            bool get_reduce_magic_damage_80() { return special_abilities._reduce_magic_damage_80; };
            bool get_reduce_magic_damage_85() { return special_abilities._reduce_magic_damage_85; };
            bool get_reduce_magic_damage_95() { return special_abilities._reduce_magic_damage_95; };

            bool get_is_immune_to_jousting()         { return special_abilities._is_immune_to_jousting;         };
            bool get_is_immune_to_fear()             { return special_abilities._is_immune_to_fear;             };
            bool get_is_immune_to_blind()            { return special_abilities._is_immune_to_blind;            };
            bool get_is_immune_to_petrify()          { return special_abilities._is_immune_to_petrify;          };
            bool get_is_immune_to_magic_arrow()      { return special_abilities._is_immune_to_magic_arrow;      };
            bool get_is_immune_to_ice_bolt()         { return special_abilities._is_immune_to_ice_bolt;         };
            bool get_is_immune_to_frost_ring()       { return special_abilities._is_immune_to_frost_ring;       };
            bool get_is_immune_to_lightning_bolt()   { return special_abilities._is_immune_to_lightning_bolt;   };
            bool get_is_immune_to_chain_lightning()  { return special_abilities._is_immune_to_chain_lightning;  };
            bool get_is_immune_to_meteor_shower()    { return special_abilities._is_immune_to_meteor_shower;    };
            bool get_is_immune_to_armageddon()       { return special_abilities._is_immune_to_armageddon;       };
            bool get_is_immune_to_fire_spells()      { return special_abilities._is_immune_to_fire_spells;      };
            bool get_is_immune_to_mind_spells()      { return special_abilities._is_immune_to_mind_spells;      };
            bool get_is_immune_to_spells_level_1_3() { return special_abilities._is_immune_to_spells_level_1_3; };
            bool get_is_immune_to_spells_level_1_4() { return special_abilities._is_immune_to_spells_level_1_4; };
            bool get_is_immune_to_all_spells()       { return special_abilities._is_immune_to_all_spells;       };

            bool get_is_vulnerable_to_ice_bolt()        { return special_abilities._is_vulnerable_to_ice_bolt;        };
            bool get_is_vulnerable_to_frost_ring()      { return special_abilities._is_vulnerable_to_frost_ring;      };
            bool get_is_vulnerable_to_lightning_bolt()  { return special_abilities._is_vulnerable_to_lightning_bolt;  };
            bool get_is_vulnerable_to_chain_lightning() { return special_abilities._is_vulnerable_to_chain_lightning; };
            bool get_is_vulnerable_to_meteor_shower()   { return special_abilities._is_vulnerable_to_meteor_shower;   };
            bool get_is_vulnerable_to_fire_ball()       { return special_abilities._is_vulnerable_to_fire_ball;       };
            bool get_is_vulnerable_to_inferno()         { return special_abilities._is_vulnerable_to_inferno;         };
            bool get_is_vulnerable_to_armageddon()      { return special_abilities._is_vulnerable_to_armageddon;      };

            bool get_magic_channel() { return special_abilities._magic_channel; };
            bool get_magic_damper()  { return special_abilities._magic_damper;  };
            bool get_mana_economy()  { return special_abilities._mana_economy;  };

            bool get_has_spying()         { return special_abilities._has_spying;         };
            bool get_is_sandwalker()      { return special_abilities._is_sandwalker;      };
            bool get_generates_crystals() { return special_abilities._generates_crystals; };

            // Returns a string with the cost of a creature.
            std::string get_cost();

            // Returns a string with the special abilities of a creature.
            std::string get_special_abilities() { return special_abilities._abilities; };

            // Prints the full information of a creature.
            void print_full_info();
};

#endif