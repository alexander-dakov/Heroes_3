#include "Item.h"

Item::Item( const std::string name, const Slot slot, const Type item_type, const Resources resources, const std::string effect ) : 
            _name(name), _slot(slot), _item_type(item_type), cost(resources), effects(effect)
{
      effects.fill_effects();

      switch(get_type())
      {
            case Type::Treasure : _ai_value =  2000; break;
            case Type::Minor    : _ai_value =  5000; break;
            case Type::Major    : _ai_value = 10000; break;
            case Type::Relic    : _ai_value = 20000; break;
      }

      // printf( "Item '%s' created.\n", get_name().c_str() );
}

Item::Item( Spell& spellscroll, const Resources resources ) : 
            _name(spellscroll.get_name().c_str()), _slot(Slot::Pocket), effects(spellscroll.get_description().c_str()), cost(resources)
{
      if( get_type() == Type::None )
      {
            if     ( spellscroll.get_name() == "Town portal" )    _ai_value = 20000;
            else if( spellscroll.get_name() == "Water walk" )     _ai_value = 20000;
            else if( spellscroll.get_name() == "Fly" )            _ai_value = 20000;
            else if( spellscroll.get_name() == "Dimension door" ) _ai_value = 20000;
            else
                  switch(spellscroll.get_spell_level())
                        {
                              case Spell_level::None   : _ai_value =     0; break;
                              case Spell_level::First  : _ai_value =   500; break;
                              case Spell_level::Second : _ai_value =  2000; break;
                              case Spell_level::Third  : _ai_value =  3000; break;
                              case Spell_level::Fourth : _ai_value =  8000; break;
                              case Spell_level::Fifth  : _ai_value = 10000; break;
                        }
      }
      else
      {
            std::cerr << "\nAll spellscrolls must have type 'None'! Check up Item_List.cpp!\n";
            abort();
      }

      // printf( "Item '%s' created.\n", get_name().c_str() );
}

Item::~Item()
{
      // printf( "Item '%s' destroyed!\n", get_name().c_str() );
}

std::map< std::string, std::vector<bool*> > Item::effects::create_map_of_all_effects()
{
      std::map< std::string, std::vector<bool*> > all_effects; // all special abilities in existance, refering to their respective boolean

      all_effects["All primary skills +1."] = { &_modify_attack, &_modify_defense, &_modify_power, &_modify_knowledge };
      all_effects["All primary skills +2."] = { &_modify_attack, &_modify_defense, &_modify_power, &_modify_knowledge };
      all_effects["All primary skills +3."] = { &_modify_attack, &_modify_defense, &_modify_power, &_modify_knowledge };
      all_effects["All primary skills +4."] = { &_modify_attack, &_modify_defense, &_modify_power, &_modify_knowledge };
      all_effects["All primary skills +5."] = { &_modify_attack, &_modify_defense, &_modify_power, &_modify_knowledge };
      all_effects["All primary skills +6."] = { &_modify_attack, &_modify_defense, &_modify_power, &_modify_knowledge };

      all_effects["Attack skill -3."]  = { &_modify_attack };
      all_effects["Attack skill +1."]  = { &_modify_attack };
      all_effects["Attack skill +2."]  = { &_modify_attack };
      all_effects["Attack skill +3."]  = { &_modify_attack };
      all_effects["Attack skill +4."]  = { &_modify_attack };
      all_effects["Attack skill +5."]  = { &_modify_attack };
      all_effects["Attack skill +6."]  = { &_modify_attack };
      all_effects["Attack skill +7."]  = { &_modify_attack };
      all_effects["Attack skill +12."] = { &_modify_attack };
      
      all_effects["Defense skill -3."]  = { &_modify_defense };
      all_effects["Defense skill +1."]  = { &_modify_defense };
      all_effects["Defense skill +2."]  = { &_modify_defense };
      all_effects["Defense skill +3."]  = { &_modify_defense };
      all_effects["Defense skill +4."]  = { &_modify_defense };
      all_effects["Defense skill +5."]  = { &_modify_defense };
      all_effects["Defense skill +6."]  = { &_modify_defense };
      all_effects["Defense skill +7."]  = { &_modify_defense };
      all_effects["Defense skill +12."] = { &_modify_defense };

      all_effects["Power skill -2."]   = { &_modify_power };
      all_effects["Power skill +1."]   = { &_modify_power };
      all_effects["Power skill +2."]   = { &_modify_power };
      all_effects["Power skill +3."]   = { &_modify_power };
      all_effects["Power skill +4."]   = { &_modify_power };
      all_effects["Power skill +5."]   = { &_modify_power };
      all_effects["Power skill +6."]   = { &_modify_power };
      all_effects["Power skill +10."]  = { &_modify_power };

      all_effects["Knowledge skill -2."]   = { &_modify_knowledge };
      all_effects["Knowledge skill +1."]   = { &_modify_knowledge };
      all_effects["Knowledge skill +2."]   = { &_modify_knowledge };
      all_effects["Knowledge skill +3."]   = { &_modify_knowledge };
      all_effects["Knowledge skill +4."]   = { &_modify_knowledge };
      all_effects["Knowledge skill +5."]   = { &_modify_knowledge };
      all_effects["Knowledge skill +6."]   = { &_modify_knowledge };
      all_effects["Knowledge skill +10."]  = { &_modify_knowledge };

      all_effects["Unit's health points +1."] = { &_increase_hp_1 };
      all_effects["Unit's health points +2."] = { &_increase_hp_2 };

      all_effects["Unit's speed +1."] = { &_increase_speed_1 };
      all_effects["Unit's speed +2."] = { &_increase_speed_2 };

      return all_effects;
}

void Item::effects::fill_effects()
{
      std::string helper = _effect; // a copy of the original creature ablities to cut from
      std::string::size_type pos; // position of found substring from map in "helper" string

      auto all_effects = create_map_of_all_effects();

      uint8_t counter = 0;
      while( helper.length() > 1) // no need to enter helper when an empty space remains
      {
            counter ++;
            if( counter > MAX_NUM_OF_EFFECTS)
            {
                  std::cerr << "An items effect is not recognized by the algorithm. Make sure that the string in create_map_of_all_effects() is the same as in Item_List." << std::endl;
                  std::cerr << "Problematic string : " << helper << std::endl;
                  std::cerr << "Full string : " << _effect << std::endl;
                  abort();
            }

            if( helper[0] == ' ' ) // if the first character is whitespace - delete it
            {
                  helper.erase(0, 1);
                  break;
            }
            else
            {
                  for(auto effects : all_effects) // key-value pair
                  {
                        pos = helper.find(effects.first);
                        if( pos != std::string::npos )
                        {
                              for(auto effect : effects.second)
                                    *effect = true;
                              helper.erase(pos, effects.first.length());
                              if( helper[pos] == ' ' ) // if the new character on the same place is whitespace - delete it
                                    helper.erase(pos, 1);
                              break;
                        }
                  }
            }
      }
      
      if( _modify_attack )
            _attack =  1*(_effect.find("All primary skills +1.") != std::string::npos)
                    +  2*(_effect.find("All primary skills +2.") != std::string::npos)
                    +  3*(_effect.find("All primary skills +3.") != std::string::npos)
                    +  4*(_effect.find("All primary skills +4.") != std::string::npos)
                    +  5*(_effect.find("All primary skills +5.") != std::string::npos)
                    +  6*(_effect.find("All primary skills +6.") != std::string::npos)
                    -  3*(_effect.find("Attack skill -3.")       != std::string::npos)
                    +  1*(_effect.find("Attack skill +1.")       != std::string::npos)
                    +  2*(_effect.find("Attack skill +2.")       != std::string::npos)
                    +  3*(_effect.find("Attack skill +3.")       != std::string::npos)
                    +  4*(_effect.find("Attack skill +4.")       != std::string::npos)
                    +  5*(_effect.find("Attack skill +5.")       != std::string::npos)
                    +  6*(_effect.find("Attack skill +6.")       != std::string::npos)
                    +  7*(_effect.find("Attack skill +7.")       != std::string::npos)
                    + 12*(_effect.find("Attack skill +12.")      != std::string::npos);

      if( _modify_defense )
            _defense =  1*(_effect.find("All primary skills +1.") != std::string::npos)
                     +  2*(_effect.find("All primary skills +2.") != std::string::npos)
                     +  3*(_effect.find("All primary skills +3.") != std::string::npos)
                     +  4*(_effect.find("All primary skills +4.") != std::string::npos)
                     +  5*(_effect.find("All primary skills +5.") != std::string::npos)
                     +  6*(_effect.find("All primary skills +6.") != std::string::npos)
                     -  3*(_effect.find("Defense skill -3.")      != std::string::npos)
                     +  1*(_effect.find("Defense skill +1.")      != std::string::npos)
                     +  2*(_effect.find("Defense skill +2.")      != std::string::npos)
                     +  3*(_effect.find("Defense skill +3.")      != std::string::npos)
                     +  4*(_effect.find("Defense skill +4.")      != std::string::npos)
                     +  5*(_effect.find("Defense skill +5.")      != std::string::npos)
                     +  6*(_effect.find("Defense skill +6.")      != std::string::npos)
                     +  7*(_effect.find("Defense skill +7.")      != std::string::npos)
                     + 12*(_effect.find("Defense skill +12.")     != std::string::npos);

      if( _modify_power )
            _power =  1*(_effect.find("All primary skills +1.") != std::string::npos)
                   +  2*(_effect.find("All primary skills +2.") != std::string::npos)
                   +  3*(_effect.find("All primary skills +3.") != std::string::npos)
                   +  4*(_effect.find("All primary skills +4.") != std::string::npos)
                   +  5*(_effect.find("All primary skills +5.") != std::string::npos)
                   +  6*(_effect.find("All primary skills +6.") != std::string::npos)
                   -  2*(_effect.find("Power skill -2.")        != std::string::npos)
                   +  1*(_effect.find("Power skill +1.")        != std::string::npos)
                   +  2*(_effect.find("Power skill +2.")        != std::string::npos)
                   +  3*(_effect.find("Power skill +3.")        != std::string::npos)
                   +  4*(_effect.find("Power skill +4.")        != std::string::npos)
                   +  5*(_effect.find("Power skill +5.")        != std::string::npos)
                   +  6*(_effect.find("Power skill +6.")        != std::string::npos)
                   + 10*(_effect.find("Power skill +10.")       != std::string::npos);

      if( _modify_knowledge )
            _knowledge =  1*(_effect.find("All primary skills +1.") != std::string::npos)
                       +  2*(_effect.find("All primary skills +2.") != std::string::npos)
                       +  3*(_effect.find("All primary skills +3.") != std::string::npos)
                       +  4*(_effect.find("All primary skills +4.") != std::string::npos)
                       +  5*(_effect.find("All primary skills +5.") != std::string::npos)
                       +  6*(_effect.find("All primary skills +6.") != std::string::npos)
                       -  2*(_effect.find("Knowledge skill -2.")     != std::string::npos)
                       +  1*(_effect.find("Knowledge skill +1.")     != std::string::npos)
                       +  2*(_effect.find("Knowledge skill +2.")     != std::string::npos)
                       +  3*(_effect.find("Knowledge skill +3.")     != std::string::npos)
                       +  4*(_effect.find("Knowledge skill +4.")     != std::string::npos)
                       +  5*(_effect.find("Knowledge skill +5.")     != std::string::npos)
                       +  6*(_effect.find("Knowledge skill +6.")     != std::string::npos)
                       + 10*(_effect.find("Knowledge skill +10.")    != std::string::npos);
}

std::string Item::get_slot_as_string()
{
      std::string slot;

      switch(get_slot())
      {
            case Slot::Helmet   : slot = "Helmet";   break;
            case Slot::Cape     : slot = "Cape";     break;
            case Slot::Necklace : slot = "Necklace"; break;
            case Slot::Weapon   : slot = "Weapon";   break;
            case Slot::Shield   : slot = "Shield";   break;
            case Slot::Armor    : slot = "Armor";    break;
            case Slot::Hand     : slot = "Hand";     break;
            case Slot::Boots    : slot = "Boots";    break;
            case Slot::Pocket   : slot = "Pocket";   break;
      }
      return slot;
}

std::string Item::get_type_as_string()
{
      std::string item_type;

      switch(get_type())
      {
            case Type::None     : item_type = "None";     break;
            case Type::Treasure : item_type = "Treasure"; break;
            case Type::Minor    : item_type = "Minor";    break;
            case Type::Major    : item_type = "Major";    break;
            case Type::Relic    : item_type = "Relic";    break;
      }
      return item_type;
}

std::string Item::get_cost()
{
      std::string str;

      if( cost._gold     )    str += "Gold : "     + std::to_string(cost._gold)     + '\n';
      if( cost._mercury  )    str += "Mercury : "  + std::to_string(cost._mercury)  + '\n';
      if( cost._sulfur   )    str += "Sulfur : "   + std::to_string(cost._sulfur)   + '\n';
      if( cost._crystals )    str += "Crystals : " + std::to_string(cost._crystals) + '\n';
      if( cost._gems     )    str += "Gems : "     + std::to_string(cost._gems)     + '\n';

      return str;
}

void Item::print_full_info()
{
      printf( "\n" );
      printf( "Name : %s\n",     get_name().c_str() );
      printf( "Slot : %s\n",     get_slot_as_string().c_str() );
      printf( "Type : %s\n",     get_type_as_string().c_str() );
      printf( "AI Value : %d\n", get_ai_value() );
      printf( "Effect : %s\n",   get_effect().c_str() );
      printf( "Cost : %s\n",     get_cost().c_str()   );
}