add_executable(Heroes3 main.cpp)

target_link_libraries(Heroes3 PRIVATE source)

target_link_libraries(Heroes3 PRIVATE utilities)

target_link_libraries(Heroes3 PRIVATE tests)