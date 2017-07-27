add_library(game
  TimeBomb.cpp
  HumanPlayerSfml.cpp
  SimpleMap.cpp
  )

add_executable(game_test
  TimeBomb.ut.cpp
  Entity.ut.cpp
  Map.ut.cpp
  SimpleMap.ut.cpp
  )

target_include_directories(game_test SYSTEM PRIVATE
  ${UT_INCLUDES}
  )

target_include_directories(game_test PRIVATE
  ${INTERNAL_LIBS_INCLUDE_PATH}
  )

target_link_libraries(game_test gtest_main game)
add_test(game_test ${EXECUTABLE_OUTPUT_PATH}/game_test --gtest_color=yes)
