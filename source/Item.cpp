#include "Item.h"

Item::Item( const std::string name, const Slot slot, const Type item_type, const Resources resources, const std::string description ) : 
            _name(name), _slot(slot), _item_type(item_type), cost(resources), _description(description)
{
      // printf( "Item %s created.\n", get_name().c_str() );
}

Item::Item( Spell& spellscroll, const Resources resources ) : 
            _name(spellscroll.get_name().c_str()), _slot(Slot::Pocket), _description(spellscroll.get_description().c_str()), cost(resources)
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
            switch(get_type())
            {
                  case Type::Treasure    : _ai_value =  2000; break;
                  case Type::Minor       : _ai_value =  5000; break;
                  case Type::Major       : _ai_value = 10000; break;
                  case Type::Relic       : _ai_value = 20000; break;
            }

      // printf( "Item %s created.\n", get_name().c_str() );
}

Item::~Item()
{
      // printf( "Item %s destroyed!\n", get_name().c_str() );
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

      if(cost._gold)          str += "Gold : "     + std::to_string(cost._gold)     + '\n';
      if(cost._mercury)       str += "Mercury : "  + std::to_string(cost._mercury)  + '\n';
      if(cost._sulfur)        str += "Sulfur : "   + std::to_string(cost._sulfur)   + '\n';
      if(cost._crystals)      str += "Crystals : " + std::to_string(cost._crystals) + '\n';
      if(cost._gems)          str += "Gems : "     + std::to_string(cost._gems)     + '\n';

      return str;
}

void Item::print_full_info()
{
      printf("Name : %s\n", get_name().c_str());
      printf("Slot : %s\n", get_slot_as_string().c_str());
      printf("Type : %s\n", get_type_as_string().c_str());
      printf("AI Value : %d\n", get_ai_value());
      printf("Description : %s\n", get_description().c_str());
      printf("Cost : %s\n", get_cost().c_str());
}