cmake_minimum_required(VERSION 3.0.0)
project(Heroes3 VERSION 0.1.0 LANGUAGES C CXX)
# project(Heroes3)

add_subdirectory(adventure_map)
add_subdirectory(battle)
add_subdirectory(creatures)
add_subdirectory(heroes)
add_subdirectory(items)
add_subdirectory(players)
add_subdirectory(spells)
add_subdirectory(towns)
add_subdirectory(utilities)

add_subdirectory(tests)

add_subdirectory(main-exe)