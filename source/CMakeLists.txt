add_library(
    source

    Terrains.h

    Battle.h
    Battle.cpp
    Battlefield_Tile.h
    Battlefield_Tile.cpp
    Position.h

    Morale_Luck.h
    Secondary_Skill.h
    Secondary_Skill_List.cpp
    Skill_level.h
    Specialty.h
    Specialty_List.cpp

    Item.h
    Item.cpp
    Item_List.cpp

    Resources.h
    Team.h
    Team.cpp

    Spell.h
    Spellbook.h

    Faction.h

    Creature.h
    Creature.cpp
    Creature_List.cpp
    Creature_Stack.h
    Creature_Stack.cpp

    Level_Experience.h
    Skills_Probability.h
    Hero.h
    Hero.cpp
    Hero_List.cpp
    )
    
set_target_properties(source PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(source PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
