add_library(game
  game/Bomb.cpp
  )

add_executable(game_test
  game/EntityInterfaceTest.cpp
  game/BombTest.cpp
  )

target_include_directories(game_test SYSTEM PRIVATE
  ${FAKEIT_INCLUDE_DIR}
  ${GMOCK_INCLUDE_DIR}
  ${GTEST_INCLUDE_DIR}
  )


target_link_libraries(game_test gtest_main game)
add_test(game_test ${EXECUTABLE_OUTPUT_PATH}/game_test --gtest_color=yes)
