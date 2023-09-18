add_library(
    tests
    tests.cpp
    )

target_include_directories(tests PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
