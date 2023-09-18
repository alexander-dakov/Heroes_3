add_library(
    heroes
    Hero.h
    Hero.cpp
    Hero_List.cpp
    Morale_Luck.h
    Secondary_Skill.h
    Secondary_Skill_List.cpp
    Skill_level.h
    Specialty.h
    Specialty_List.cpp
    )

target_include_directories(heroes PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")