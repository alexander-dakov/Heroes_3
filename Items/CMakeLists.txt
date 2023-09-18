add_library(
    items
    Item.h
    )

set_target_properties(items PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(items PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")