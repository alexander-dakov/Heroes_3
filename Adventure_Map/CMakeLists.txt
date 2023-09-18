add_library(
    adventure_map 
    Terrains.h
    )
    
set_target_properties(adventure_map PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(adventure_map PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")