project(test_computer_vision)

add_executable( test_computer_vision ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp )

target_link_libraries(test_computer_vision func_algo1)
target_link_directories(test_computer_vision PUBLIC ${CMAKE_BINARY_DIR}/googletest-install/lib)
target_link_libraries(test_computer_vision gtest gtest_main)
