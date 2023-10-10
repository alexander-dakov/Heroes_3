#include "Hero.h"

Hero::Hero( const std::string name, const Gender gender, const Class hero_class, const Faction faction, const Team team, const uint8_t level, const uint32_t experience, 
            const uint8_t attack, const uint8_t defense, const uint8_t power, const uint8_t knowledge,
            const Specialty& specialty,
            const Morale morale, const Luck luck,
            // secondary skills
            const struct war_machines war_machinery,
            const bool has_spellbook ) :
            _name(name), _gender(gender), _class(hero_class), _faction(faction), _team(team), _level(level), _experience(experience), 
            primary_skills(attack, defense, power, knowledge),
            _specialty(specialty),
            _morale(morale), _luck(luck),
            // {"None", ...} write them in some way and change field in Hero.h,
            war_machines(war_machinery),
            _has_spellbook(has_spellbook)
{
      _mana = knowledge*10;
      _mana_left = _mana;
      _movement_points = 1560;
}

Hero::~Hero()
{
      // printf( "Hero %s destroyed!\n", get_name().c_str() );
}

std::string Hero::get_gender_as_string()
{
      if( get_gender() == Gender::Male )  
            return "Male";
      return "Female";
}

std::string Hero::get_class_as_string()
{
      std::string hero_class;

      switch(get_faction())
      {
            case Faction::Neutral    : get_class() ? hero_class = "Magic"        : hero_class = "Might";        break;
            case Faction::Castle     : get_class() ? hero_class = "Cleric"       : hero_class = "Knight";       break;
            case Faction::Rampart    : get_class() ? hero_class = "Druid"        : hero_class = "Ranger";       break;
            case Faction::Tower      : get_class() ? hero_class = "Wizard"       : hero_class = "Alchemist";    break;
            case Faction::Inferno    : get_class() ? hero_class = "Heretic"      : hero_class = "Demoniac";     break;
            case Faction::Necropolis : get_class() ? hero_class = "Necromancer"  : hero_class = "Death Knight"; break;
            case Faction::Dungeon    : get_class() ? hero_class = "Warlock"      : hero_class = "Overlord";     break;
            case Faction::Stronghold : get_class() ? hero_class = "Battle Mage"  : hero_class = "Barbarian";    break;
            case Faction::Fortress   : get_class() ? hero_class = "Witch"        : hero_class = "Beastmaster";  break;
            case Faction::Conflux    : get_class() ? hero_class = "Elementalist" : hero_class = "Planeswalker"; break;
            case Faction::Cove       : get_class() ? hero_class = "Navigator"    : hero_class = "Captain";      break;
      }

      return hero_class;
}

std::string Hero::get_faction_as_string()
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

std::string Hero::get_team_as_string()
{
      std::string team;

      switch(get_team())
      {
            case Team::Neutral : team = "Neutral"; break;
            case Team::Red     : team = "Red";     break;
            case Team::Blue    : team = "Blue";    break;
            case Team::Tan     : team = "Tan";     break;
            case Team::Green   : team = "Green";   break;
            case Team::Orange  : team = "Orange";  break;
            case Team::Purple  : team = "Purple";  break;
            case Team::Teal    : team = "Teal";    break;
            case Team::Pink    : team = "Pink";    break;
      }

      return team;
}

void Hero::add_level(const uint8_t level)
{
      // use map for these
      // 1	0	
      // 2	1,000
      // 3	2,000
      // 4	3,200
      // 5	4,600
      // 6	6,200
      // 7	8,000
      // 8	10,000
      // 9	12,200
      // 10	14,700
}

void Hero::add_experience(const uint32_t experience)
{
      // according to add_level
}

// this is not accurate representation of the hero movement in the game
// path to location should be calculated in days
// each tile across the path should be visited for step-on effects
void Hero::move(uint8_t x, uint8_t y)
{
    uint8_t distance = std::abs(x - _position.x) + std::abs(y - _position.y);
    while(get_movement_points() < distance)
    {
        printf("%s have only %i speed and can't move that far. Pick a new position!", get_name());
    }
    _position.x = x;
    _position.y = y;
}

void Hero::equip_item(Item& item)
{
      // TODO : Implement update!
      return;
}

void Hero::unequip_item(Item& item)
{
      // TODO : Implement update!
      return;
}

void Hero::add_stack_to_army(Stack* stack)
{
      for( uint8_t i = 0; i < ARMY_SLOTS; i++ )
            if( army[i] == nullptr )
            {
                  army[i] = stack;
                  update_army_stats();
                  return;
            }

      printf("There is not enough sapce in the army for this stack!");
      return;
}

void Hero::add_stack_to_slot(Stack* stack, uint8_t slot)
{
      if( army[slot] == nullptr )
      {
            army[slot] = stack;
            update_army_stats();
            return;
      }

      printf("There is not enough sapce in the army for this stack!");
      return;
}

void Hero::remove_stack(Stack& stack)
{
      // TODO : Implement update!
      return;
}

void Hero::remove_stack_from_position(uint8_t slot)
{
      // TODO : Implement update!
      return;
}

void Hero::swap_stack_positions()
{
      // TODO : Implement update!
      return;
}

void Hero::update_army_stats()
{      
      uint8_t att   = get_attack();
      uint8_t def   = get_defense();
      Morale morale = get_morale();
      Luck luck     = get_luck();

      // items adding hp to units
      bool has_equipped_ring_of_life      = _has_equipped_ring_of_life;
      bool has_equipped_ring_of_vitality  = _has_equipped_ring_of_vitality;
      bool has_equipped_vail_of_lifeblood = _has_equipped_vail_of_lifeblood;
      bool has_equipped_elixir_of_life    = _has_equipped_elixir_of_life;

      // items adding speed to units
      bool has_equipped_ring_of_wayfarer      = _has_equipped_ring_of_wayfarer;
      bool has_equipped_necklace_of_swiftness = _has_equipped_necklace_of_swiftness;
      bool has_equipped_cape_of_velocity      = _has_equipped_cape_of_velocity;

      std::string specialty_name = get_specialty().get_name();

      Skill_level level_of_archery    = Skill_level::None;
      Skill_level level_of_offence    = Skill_level::None;
      Skill_level level_of_armorer    = Skill_level::None;
      Skill_level level_of_resistance = Skill_level::None;

      for(uint8_t i = 0; i < SECONDARY_SKILLS; i++)
      {
            if( get_secondary_skill(i) != nullptr )
            {
                  if     ( get_secondary_skill(i)->get_name() == "Archery")    { level_of_archery    = get_secondary_skill(i)->get_level(); }
                  else if( get_secondary_skill(i)->get_name() == "Offence")    { level_of_offence    = get_secondary_skill(i)->get_level(); }
                  else if( get_secondary_skill(i)->get_name() == "Armorer")    { level_of_armorer    = get_secondary_skill(i)->get_level(); }
                  else if( get_secondary_skill(i)->get_name() == "Resistance") { level_of_resistance = get_secondary_skill(i)->get_level(); }
            }
      }
      
      for(int i = 0; i < ARMY_SLOTS; i++)
      {
            if( army[i] != nullptr)
            {
                  auto c = army[i]->get_creature();

                  army[i]->set_att(c->get_att() + att);
                  army[i]->set_def(c->get_def() + def);

                  army[i]->set_hp(c->get_hp() + 1*_has_equipped_ring_of_life + 1*has_equipped_ring_of_vitality + 2*has_equipped_vail_of_lifeblood + (c->get_hp()/4)*has_equipped_elixir_of_life);
                  army[i]->set_hp_left(c->get_hp());

                  army[i]->set_speed(c->get_speed() + 1*has_equipped_ring_of_wayfarer + 1*has_equipped_necklace_of_swiftness + 2*has_equipped_cape_of_velocity);

                  // TO DO : morale/luck penalties for different factions in same army should be implemented + no morale/luck update for some creatures (undead, bloodless, satyr, leprechaun, etc.)
                  army[i]->set_morale( static_cast<Morale>( std::min( std::max( static_cast<int8_t>(c->get_morale()) + static_cast<int8_t>(get_morale()), -3), 3) ) );
                  army[i]->set_luck(   static_cast<Luck>(   std::min( std::max( static_cast<int8_t>(c->get_luck())   + static_cast<int8_t>(get_luck()),   -3), 3) ) );

                  army[i]->set_hero_specialty_name(specialty_name);
                  army[i]->set_hero_level_of_archery(level_of_archery);
                  army[i]->set_hero_level_of_offence(level_of_offence);
                  army[i]->set_hero_level_of_armorer(level_of_armorer);
                  army[i]->set_hero_level_of_resistance(level_of_resistance);
            }
      }
}

void Hero::print_full_info()
{
      printf("Name : %s\n", get_name().c_str());
      printf("Gender : %s\n", get_gender_as_string().c_str());
      printf("Class : %s\n", get_class_as_string().c_str());
      printf("Faction : %s\n", get_faction_as_string().c_str());
      printf("Team : %s\n", get_team_as_string().c_str());
      printf("Level : %d\n", get_level());
      printf("Experiece : %d\n", get_experience());

      printf("Primary skills :\n");
      printf("\tAttack : %d\n", get_attack());
      printf("\tDefense : %d\n", get_defense());
      printf("\tPower : %d\n", get_power());
      printf("\tKnowledge : %d\n", get_knowledge());

      printf("Specialty : %s\n\t%s\n", get_specialty().get_name().c_str(), get_specialty().get_effect().c_str());

      printf("Morale : %d\n", get_morale());
      printf("Luck : %d\n", get_luck());
      printf("Mana : %d / %d\n", get_mana_left(), get_mana());
      printf("Movement points : %d\n", get_movement_points());

      printf("Has First Aid Tent : %s\n", get_has_first_aid() ? "true" : "false");
      printf("Has Ammo Cart : %s\n", get_has_ammo_cart() ? "true" : "false");
      // if(get_has_cannon())
      //       printf("Has Cannon : true");
      // else
            printf("Has Ballista : %s\n", get_has_ballista() ? "true" : "false");
      printf("Has Ballista : %s\n", get_has_spellbook() ? "true" : "false");
      printf("Has Catapult : %s\n", get_has_catapult() ? "true" : "false");

      printf("Has Spellbook : %s\n", get_has_spellbook() ? "true" : "false");
}