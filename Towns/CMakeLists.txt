add_library(
    towns
    Faction.h
    )

set_target_properties(towns PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(towns PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
