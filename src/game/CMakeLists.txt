add_library(game
  BombermanGameWorld.cpp
  BoundaryWallsPositionsGenerator.cpp
  ExplosionRange.cpp
  HumanPlayerSfml.cpp
  LimitedBombLauncher.cpp
  SimpleMap.cpp
  TimeBomb.cpp
  )

add_executable(game_test
  BoundaryWallsPositionsGenerator.ut.cpp
  Entity.ut.cpp
  LimitedBombLauncher.ut.cpp
  Map.ut.cpp
  SimpleMap.ut.cpp
  TimeBomb.ut.cpp
  )

target_include_directories(game_test SYSTEM PRIVATE
  ${UT_INCLUDES}
  )

target_include_directories(game PRIVATE
  ${INTERNAL_LIBS_INCLUDE_PATH}
  )

target_include_directories(game_test PRIVATE
  ${INTERNAL_LIBS_INCLUDE_PATH}
  )

target_include_directories(game PRIVATE
  ${INTERNAL_LIBS_INCLUDE_PATH}
  )

target_link_libraries(game_test --coverage gmock gtest_main game)
add_test(game_test ${EXECUTABLE_OUTPUT_PATH}/game_test --gtest_color=yes)
