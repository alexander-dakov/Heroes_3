add_library(
    creatures
    Creature.h
    Creature.cpp
    Creature_List.cpp
    Creature_Stack.h
    Creature_Stack.cpp
    )

target_include_directories(creatures PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")