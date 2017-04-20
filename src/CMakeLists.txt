add_executable(game_test
	game/EntityInterfaceTest.cpp)

target_link_libraries(game_test gtest_main)
add_test(game_test ${EXECUTABLE_OUTPUT_PATH}/game_test)

