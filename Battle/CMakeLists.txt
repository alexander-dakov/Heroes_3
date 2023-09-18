add_library(
    battle
    Battle.h
    Position.h
    )

set_target_properties(battle PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(battle PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")