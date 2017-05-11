add_library(game
  TimeBomb.cpp
  HumanPlayerSfml.cpp
  )

add_executable(game_test
  EntityInterfaceTest.cpp
  TimeBombTest.cpp
  )

target_include_directories(game_test SYSTEM PRIVATE
  ${UT_INCLUDES}
  )


target_link_libraries(game_test gtest_main game)
add_test(game_test ${EXECUTABLE_OUTPUT_PATH}/game_test --gtest_color=yes)
