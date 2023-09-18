add_library(
    players
    Resources.h
    Team.h
    )

set_target_properties(players PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(players PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")