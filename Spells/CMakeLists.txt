add_library(
    spells
    Spell.h
    Spellbook.h
    )

set_target_properties(spells PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(spells PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
