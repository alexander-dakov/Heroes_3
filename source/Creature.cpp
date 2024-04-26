#include "Creature.h"

Creature::Creature( const std::string name, const Faction faction, const uint8_t level, const Upgrade_level upgrade, const uint8_t growth, const bool needs_2_tiles_in_battle,
                    const uint8_t att, const uint8_t def, const uint8_t shots, const uint8_t min_dmg, const uint8_t max_dmg, const uint16_t hp, const uint8_t speed, const Morale morale, const Luck luck, const uint16_t fight_value, const uint32_t ai_value, 
                    const Resources resources,
                    const std::string abilities ) : 
                    unit_info(name, faction, level, upgrade, growth, needs_2_tiles_in_battle),
                    battle_stats(att, def, shots, min_dmg, max_dmg, hp, speed, morale, luck, fight_value, ai_value),
                    cost(resources),  
                    special_abilities(abilities)
{
      unit_info.set_native_terrain();

      special_abilities.set_special_abilities();

      logical_limitations();

      // printf( "Creature %s created.\n", get_name().c_str() );
}

Creature::Creature(const Creature& creature) : unit_info(creature.unit_info), battle_stats(creature.battle_stats), cost(creature.cost), special_abilities(creature.special_abilities)
{
      // printf( "Creature %s created.\n", get_name().c_str() );
}

Creature::Creature(const Creature* creature) : unit_info(creature->unit_info), battle_stats(creature->battle_stats), cost(creature->cost), special_abilities(creature->special_abilities)
{
      // printf( "Creature %s created.\n", get_name().c_str() );
}

Creature::~Creature()
{
      // printf( "Creature %s destroyed!\n", get_name().c_str() );
}

void Creature::unit_info::set_native_terrain()
{
      switch(this->_faction)
      {
            case Faction::Neutral    : _native_terrain = Terrain::None;         break;
            case Faction::Castle     : _native_terrain = Terrain::Grass;        break;
            case Faction::Rampart    : _native_terrain = Terrain::Grass;        break;
            case Faction::Tower      : _native_terrain = Terrain::Snow;         break;
            case Faction::Inferno    : _native_terrain = Terrain::Lava;         break;
            case Faction::Necropolis : _native_terrain = Terrain::Dirt;         break;
            case Faction::Dungeon    : _native_terrain = Terrain::Subterranean; break;
            case Faction::Stronghold : _native_terrain = Terrain::Rough;        break;
            case Faction::Fortress   : _native_terrain = Terrain::Swamp;        break;
            case Faction::Conflux    : _native_terrain = Terrain::Highlands;    break;
            case Faction::Cove       : _native_terrain = Terrain::Swamp;        break;
      }
}

void Creature::special_abilities::set_special_abilities()
{
      // Keep that order, because the abilities map should be filled and then the number of casts and spell power should be set.
      fill_special_abilities();
      
      _number_of_casts = 0; 
      _spell_power = 0;
      
      if( _can_cast_ressurection )       { _number_of_casts = 1; return;                   } // Archangel
      if( _can_cast_advanced_fortune )   { _number_of_casts = 3; _spell_power = 6; return; } // Leprechaun
      if( _can_cast_advanced_mirth )     { _number_of_casts = 3; _spell_power = 6; return; } // Satyr

      if( _is_spellcaster )
      {
            if     ( _hates_efreeti )    { _number_of_casts = 3; _spell_power = 6; return; } // Master Genie
            else if( _has_magic_mirror ) { _number_of_casts = 5; return;                   } // Faerie Dragon
            else                         { _number_of_casts = 3; _spell_power = 3; return; } // Enchanter
      }
      
      if( _can_cast_bloodlust )          { _number_of_casts = 3; _spell_power = 3; return; } // Orge Mage
}

void Creature::logical_limitations()
{
      if( unit_info._level == 0 || unit_info._level > 7 )
      {
            std::cerr<< "Creature level must be in the interval [1;7]!" << std::endl;
            abort();
      }

      if( unit_info._growth == 0 )
      {
            std::cerr<< "Creature must have positive growth per week!" << std::endl;
            abort();
      }

      if( battle_stats._att == 0 )
      {
            std::cerr<< "Creature must have positive attack skill!" << std::endl;
            abort();
      }

      if( battle_stats._def == 0 )
      {
            std::cerr<< "Creature must have positive defense skill!" << std::endl;
            abort();
      }

      if( battle_stats._min_dmg > battle_stats._min_dmg )
      {
            std::cerr<< "Creature min damage mustn't be higher than its max value!" << std::endl;
            abort();
      }

      if( battle_stats._hp == 0 )
      {
            std::cerr<< "Creature must have positive hp!" << std::endl;
            abort();
      }

      if( battle_stats._speed == 0 )
      {
            std::cerr<< "Creature must have positive speed!" << std::endl;
            abort();
      }

      if( battle_stats._fight_value == 0 )
      {
            std::cerr<< "Creature must have positive fight value!" << std::endl;
            abort();
      }

      if( battle_stats._ai_value == 0 )
      {
            std::cerr<< "Creature must have positive ai value!" << std::endl;
            abort();
      }

      if( cost._gold == 0 )
      {
            std::cerr<< "Creature must have a price including gold!" << std::endl;
            abort();
      }

      if( unit_info._faction == Faction::Necropolis )
      {
            special_abilities._is_undead = true;
            special_abilities._is_bloodless = false;
      }

      if( special_abilities._is_undead == true )
            special_abilities._is_bloodless = false;

      if( special_abilities._is_bloodless == true )
            special_abilities._is_undead = false;

      if( !special_abilities._is_ranged )
            battle_stats._shots = 0;

      if( special_abilities._is_undead == true || special_abilities._is_bloodless == true ) // all undead, golems and elementals
            special_abilities._is_immune_to_mind_spells = true;            
}

std::map< std::string, std::vector<bool*> > Creature::special_abilities::create_map_of_all_abilities()
{
      std::map< std::string, std::vector<bool*> > all_abilities; // all special abilities in existance, refering to their respective boolean

      all_abilities["Undead."]        = { &_is_undead    };
      all_abilities["Non-living."]    = { &_is_bloodless };

      all_abilities["Flying."]        = { &_is_flying };
      all_abilities["Teleporting."]   = { &_is_flying };
      all_abilities["Ranged attack."] = { &_is_ranged };

      all_abilities["No melee penalty."]    = { &_no_melee_penalty    };
      all_abilities["No obstacle penalty."] = { &_no_obstacle_penalty };
      all_abilities["No range penalty."]    = { &_no_range_penalty    };

      all_abilities["Strike and return."]      = { &_strike_and_return       };
      all_abilities["Strike and return."]      = { &_strike_and_return       };
      all_abilities["Can attack siege walls."] = { &_can_attack_siege_walls  };

      all_abilities["Ferocity."]                             = { &_has_ferocity                };
      all_abilities["Double attack."]                        = { &_has_double_attack           };
      all_abilities["Jousting bonus."]                       = { &_has_jousting                };
      all_abilities["Revenge."]                              = { &_has_revenge                 };
      all_abilities["3-headed attack."]                      = { &_has_3_headed_attack         };
      all_abilities["Fireball attack."]                      = { &_has_fireball_attack         };
      all_abilities["Death cloud."]                          = { &_has_cloud_attack            };
      all_abilities["Attack all adjacent enemies."]          = { &_has_attack_adjacent_enemies };
      all_abilities["Attack all adjacent hexes."]            = { &_has_attack_adjacent_hexes   };
      all_abilities["Breath attack."]                        = { &_has_breath_attack           };
      all_abilities["Hates Efreeti and Efreet Sultans."]     = { &_hates_efreeti               };
      all_abilities["Hates Genies and Master Genies."]       = { &_hates_genies                };
      all_abilities["Hates Devils and Arch Devils."]         = { &_hates_devils                };
      all_abilities["Hates Angels and Archangels."]          = { &_hates_angels                };
      all_abilities["Hates Black Dragons."]                  = { &_hates_black_dragons         };
      all_abilities["Hates Titans."]                         = { &_hates_titans                };
      all_abilities["Ignores 40% of enemy's defense skill."] = { &_ignore_enemy_defense        };
      all_abilities["Ignores 80% of enemy's defense skill."] = { &_ignore_enemy_defense        };

      all_abilities["Ignores 30% of enemy's attack skill."] = { &_ignore_enemy_attack };
      all_abilities["Ignores 60% of enemy's attack skill."] = { &_ignore_enemy_attack };

      all_abilities["Two retaliations."]       = { &_has_two_retaliations       };
      all_abilities["Unlimited retaliations."] = { &_has_unlimited_retaliations };
      all_abilities["No enemy retaliation."]   = { &_no_enemy_retaliation       };
      
      all_abilities["Regeneration."] = { &_casts_regeneration };
      all_abilities["Mana drain."]   = { &_casts_mana_drain   };

      all_abilities["Binding attack."]                                    = { &_casts_binding                             };
      all_abilities["Life drain."]                                        = { &_casts_life_drain                          };
      all_abilities["Casts Dispel to benefical spells per attack."]       = { &_casts_dispell_on_buffs                    };
      all_abilities["Casts Weakness per attack."]                         = { &_casts_weakness                            };
      all_abilities["Casts Advanced Weakness per attack."]                = { &_casts_advanced_weakness                   };
      all_abilities["Casts Disrupting Ray on weakened enemies."]          = { &_casts_disrupting_ray_on_weakened          };
      all_abilities["Casts Advanced Disrupting Ray on weakened enemies."] = { &_casts_advanced_disrupting_ray_on_weakened };

      all_abilities["20% chance to cast Disease per attack."]                       = { &_may_cast_disease          };
      all_abilities["25% chance to cast Curse per attack."]                         = { &_may_cast_curse            };
      all_abilities["20% chance to cast Aging per attack."]                         = { &_may_cast_aging            };
      all_abilities["30% chance to cast Poison per attack."]                        = { &_may_cast_poison           };
      all_abilities["20% chance to cast Paralyzing Venom per attack."]              = { &_may_cast_paralyzing_venom };
      all_abilities["20% chance to cast Fear to adjacent enemies before they act."] = { &_may_cast_fear             };
      all_abilities["20% chance to cast Petrify per melee attack."]                 = { &_may_cast_petrify          };
      all_abilities["20% chance to cast Petrify per attack."]                       = { &_may_cast_petrify          };
      all_abilities["20% chance to cast Blind per attack."]                         = { &_may_cast_blind            };
      all_abilities["20% chance to cast Lightning Strike per attack."]              = { &_may_cast_lightning_strike };
      all_abilities["20% chance to cast Death Blow per attack."]                    = { &_may_cast_death_blow       };
      all_abilities["10% chance to cast Death Stare per melee attack."]             = { &_may_cast_death_stare      };
      all_abilities["10% chance to cast Accurate Shot per ranged attack."]          = { &_may_cast_accurate_shot    };
      all_abilities["20% chance to cast Acid Breath per attack."]                   = { &_may_cast_acid_breath      };
      all_abilities["Can cast Hypnotize per attack."]                               = { &_may_cast_hypnotize        };

      all_abilities["Fire Shield."] = { &_casts_fire_shield };

      all_abilities["Rebirth."] = { &_may_cast_rebirth };

      all_abilities["Can cast Ressurection once per battle."]        = { &_can_cast_ressurection          };
      all_abilities["Can cast Advanced Fortune 3 times per battle."] = { &_can_cast_advanced_fortune      };
      all_abilities["Can cast Advanced Mirth 3 times per battle."]   = { &_can_cast_advanced_mirth        };
      all_abilities["Spellcaster."]                                  = { &_is_spellcaster                 };
      all_abilities["Spellcaster (Bloodlust)."]                      = { &_can_cast_bloodlust             };
      all_abilities["Spellcaster (Protection from Air)."]            = { &_can_cast_protection_from_air   };
      all_abilities["Spellcaster (Protection from Water)."]          = { &_can_cast_protection_from_water };
      all_abilities["Spellcaster (Protection from Fire)."]           = { &_can_cast_protection_from_fire  };
      all_abilities["Spellcaster (Protection from Earth)."]          = { &_can_cast_protection_from_earth };
      all_abilities["Summon Demons."]                                = { &_can_cast_summon_demons         };

      all_abilities["Magic resistance 20%."]         = { &_has_magic_resist      };
      all_abilities["Magic resistance 40%."]         = { &_has_magic_resist      };
      all_abilities["Aura of magic resistance 20%."] = { &_has_magic_resist_aura };
      all_abilities["Naturally has Magic Mirror."]   = { &_has_magic_mirror      };

      all_abilities["Spell damage reduction 50%."] = { &_reduce_magic_damage };
      all_abilities["Spell damage reduction 75%."] = { &_reduce_magic_damage };
      all_abilities["Spell damage reduction 80%."] = { &_reduce_magic_damage };
      all_abilities["Spell damage reduction 85%."] = { &_reduce_magic_damage };
      all_abilities["Spell damage reduction 95%."] = { &_reduce_magic_damage };

      all_abilities["Immune to jousting."]                    = { &_is_immune_to_jousting };
      all_abilities["Immune to Fear."]                        = { &_is_immune_to_fear     };
      all_abilities["Immune to Blind."]                       = { &_is_immune_to_blind    };
      all_abilities["Immune to Petrify."]                     = { &_is_immune_to_petrify  };
      all_abilities["Immune to Ice Bolt and Frost Ring."]     = { &_is_immune_to_ice_bolt, &_is_immune_to_frost_ring };
      all_abilities["Immune to Meteor Shower."]               = { &_is_immune_to_meteor_shower };
      all_abilities["Immune to Lightning Bolt, Chain Lightning and Armageddon."] = { &_is_immune_to_lightning_bolt, &_is_immune_to_chain_lightning, &_is_immune_to_armageddon };
      all_abilities["Immune to fire spells (Magic Arrow included)."] = { &_is_immune_to_fire_spells, &_is_immune_to_magic_arrow };
      all_abilities["Immune to mind spells."]                 = { &_is_immune_to_mind_spells      };
      all_abilities["Immune to spells level 1-3."]            = { &_is_immune_to_spells_level_1_3 };
      all_abilities["Immune to spells level 1-4."]            = { &_is_immune_to_spells_level_1_4 };
      all_abilities["Immune to all spells."]                  = { &_is_immune_to_all_spells       };
      
      all_abilities["Vulnerable to Ice Bolt and Frost Ring."]                        = { &_is_vulnerable_to_ice_bolt, &_is_vulnerable_to_frost_ring };
      all_abilities["Vulnerable to Lightning Bolt, Chain Lightning and Armageddon."] = { &_is_vulnerable_to_lightning_bolt, &_is_vulnerable_to_chain_lightning, &_is_vulnerable_to_armageddon };
      all_abilities["Vulnerable to Armageddon, Fireball, Inferno."]                  = { &_is_vulnerable_to_armageddon, &_is_vulnerable_to_fire_ball, &_is_vulnerable_to_inferno };
      all_abilities["Vulnerable to Meteor Shower."]                                  = { &_is_vulnerable_to_meteor_shower };
      
      all_abilities["Minimum morale is +1."] = { &_minimum_morale_1 };
      all_abilities["Minimum luck is +1."]   = { &_minimum_luck_1   };

      all_abilities["+1 morale to alias troops."]         = { &_increases_alias_morale_1 };
      all_abilities["-1 morale to enemy troops."]         = { &_decreases_enemy_morale_1 };
      all_abilities["-1 luck to enemy troops."]           = { &_decreases_enemy_luck_1   };
      all_abilities["-2 luck to enemy troops."]           = { &_decreases_enemy_luck_2   };
      all_abilities["Doubles friendly unit Luck chance."] = { &_doubles_luck_chance      };

      all_abilities["Magic channel."]                         = { &_magic_channel };
      all_abilities["Magic damper."]                          = { &_magic_damper  };
      all_abilities["Hero's combat spells cost 2 less mana."] = { &_mana_economy  };

      all_abilities["Spying."]             = { &_has_spying         };
      all_abilities["Sandwalker."]         = { &_is_sandwalker      };
      all_abilities["Generates crystals."] = { &_generates_crystals };

      return all_abilities;
}

void Creature::special_abilities::fill_special_abilities()
{
      std::string helper = _abilities; // a copy of the original creature ablities to cut from
      std::string::size_type pos; // position of found substring from map in "helper" string

      auto all_abilities = create_map_of_all_abilities();

      uint8_t counter = 0;
      
      while( helper.length() > 1) // no need to enter helper when an empty space remains
      {
            counter ++;
            if( counter > MAX_NUM_OF_SPECIAL_ABILITIES )
            {
                  std::cerr << "A creature's special ability is not recognized by the algorithm. Make sure that the string in create_map_of_all_abilities() is the same as in Creature_List." << std::endl;
                  std::cerr << "Problematic string : " << helper << std::endl;
                  std::cerr << "Full string : " << _abilities << std::endl;
                  abort();
            }

            if( helper[0] == ' ' ) // if the first character is whitespace - delete it
            {
                  helper.erase(0, 1);
                  break;
            }
            else
            {
                  for(auto abilities : all_abilities) // key-value pair
                  {
                        pos = helper.find(abilities.first);
                        if( pos != std::string::npos )
                        {
                              for(auto ability : abilities.second)
                                    *ability = true;
                              helper.erase(pos, abilities.first.length());
                              if( helper[pos] == ' ' ) // if the new character on the same place is whitespace - delete it
                                    helper.erase(pos, 1);
                              break;
                        }
                  }
            }
      }

      if( _ignore_enemy_defense )
            _ignore_enemy_defense_by_percent = 40*(_abilities.find("Ignores 40% of enemy's defense skill.") != std::string::npos)
                                             + 80*(_abilities.find("Ignores 80% of enemy's defense skill.") != std::string::npos);

      if( _ignore_enemy_attack )
            _ignore_enemy_attack_by_percent = 30*(_abilities.find("Ignores 30% of enemy's attack skill.") != std::string::npos)
                                            + 60*(_abilities.find("Ignores 60% of enemy's attack skill.") != std::string::npos);

      if( _reduce_magic_damage )
            _reduce_magic_damage_by_percent = 50*(_abilities.find("Spell damage reduction 50%.") != std::string::npos)
                                            + 75*(_abilities.find("Spell damage reduction 75%.") != std::string::npos)
                                            + 80*(_abilities.find("Spell damage reduction 80%.") != std::string::npos)
                                            + 85*(_abilities.find("Spell damage reduction 85%.") != std::string::npos)
                                            + 95*(_abilities.find("Spell damage reduction 95%.") != std::string::npos);

      if( _has_magic_resist )
            _has_magic_resist_by_percent = 20*(_abilities.find("Magic resistance 20%.") != std::string::npos)
                                         + 40*(_abilities.find("Magic resistance 40%.") != std::string::npos);
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
            case Faction::Dungeon    : faction = "Dungeon";    break;
            case Faction::Stronghold : faction = "Stronghold"; break;
            case Faction::Fortress   : faction = "Fortress";   break;
            case Faction::Conflux    : faction = "Conflux";    break;
            case Faction::Cove       : faction = "Cove";       break;
      }

      return faction;
}

std::string Creature::get_cost()
{
      std::string str;

      if( cost._gold     )    str += "Gold : "     + std::to_string(cost._gold)     + '\n';
      if( cost._mercury  )    str += "Mercury : "  + std::to_string(cost._mercury)  + '\n';
      if( cost._sulfur   )    str += "Sulfur : "   + std::to_string(cost._sulfur)   + '\n';
      if( cost._crystals )    str += "Crystals : " + std::to_string(cost._crystals) + '\n';
      if( cost._gems     )    str += "Gems : "     + std::to_string(cost._gems)     + '\n';

      return str;
}

void Creature::print_full_info()
{
      printf( "\n" );
      printf( "Name : %s\n",    get_name().c_str() );
      printf( "Faction : %s\n", get_faction_as_string().c_str() );
      printf( "Level : %d\n",   get_level() );
      printf( "Level of upgrade : %d\n", get_upgrade() );
      printf( "Growth per week : %d\n",  get_growth()  );
      printf( "Attack : %d\n",  get_att() );
      printf( "Defense : %d\n", get_def() );

      if( get_is_ranged() )
            printf( "Shots : %d\n", get_shots() );
      
      if( get_min_dmg() != get_max_dmg() )
            printf( "Damage : %d - %d\n", get_min_dmg(), get_max_dmg() );
      else
            printf( "Damage : %d\n", get_min_dmg() );

      printf( "Health : %d\n", get_hp()     );
      printf( "Speed : %d\n",  get_speed()  );
      printf( "Morale : %d\n", get_morale() );
      printf( "Luck : %d\n",   get_luck()   );
      printf( "Fight value : %d\n", get_fight_value() );
      printf( "AI value : %d\n",    get_ai_value()    );
      printf( "%s", get_cost().c_str() );

      if( get_special_abilities().length() != 0 )
            printf( "Special abilities : %s\n", get_special_abilities().c_str() );
}