add_library(
    source

    Terrains.h

    Battle.h
    Position.h

    Morale_Luck.h
    Secondary_Skill.h
    Secondary_Skill_List.cpp
    Skill_level.h
    Specialty.h
    Specialty_List.cpp

    Item.h

    Resources.h
    Team.h

    Spell.h
    Spellbook.h

    Faction.h

    Creature.h
    Creature.cpp
    Creature_List.cpp
    Creature_Stack.h
    Creature_Stack.cpp

    Hero.h
    Hero.cpp
    Hero_List.cpp
    )
    
set_target_properties(source PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(source PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
