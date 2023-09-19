cmake_minimum_required(VERSION 3.0.0)
project(Heroes3 VERSION 0.1.0 LANGUAGES C CXX)

add_subdirectory(utilities)

add_subdirectory(source)

add_subdirectory(tests)

add_subdirectory(main)