add_executable(game_test
  game/EntityInterfaceTest.cpp
  )

target_include_directories(game_test SYSTEM PRIVATE
  ${FAKEIT_INCLUDE_DIR}
  ${GMOCK_INCLUDE_DIR}
  ${GTEST_INCLUDE_DIR}
  )


target_link_libraries(game_test gtest_main)
add_test(game_test ${EXECUTABLE_OUTPUT_PATH}/game_test --gtest_color=yes)
