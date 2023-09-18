add_executable(Heroes3 main.cpp)

target_link_libraries(Heroes3 PRIVATE adventure_map)
target_link_libraries(Heroes3 PRIVATE battle)
target_link_libraries(Heroes3 PRIVATE creatures)
target_link_libraries(Heroes3 PRIVATE heroes)
target_link_libraries(Heroes3 PRIVATE items)
target_link_libraries(Heroes3 PRIVATE players)
target_link_libraries(Heroes3 PRIVATE spells)
target_link_libraries(Heroes3 PRIVATE towns)
target_link_libraries(Heroes3 PRIVATE utilities)

target_link_libraries(Heroes3 PRIVATE tests)