find_package(SFML 2 COMPONENTS graphics REQUIRED)

add_library(game
  BombermanGameWorld.cpp
  BoundaryWallsPositionsGenerator.cpp
  ExplosionRange.cpp
  HumanPlayerSfml.cpp
  SimpleMap.cpp
  TimeBomb.cpp
  )

target_include_directories(game SYSTEM
  PRIVATE ${SFML_INCLUDE_DIR})

target_link_libraries(game
  PUBLIC math
  PRIVATE graphics
  )

add_executable(game_test
  BoundaryWallsPositionsGenerator.ut.cpp
  Entity.ut.cpp
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

target_link_libraries(game_test
  PRIVATE game graphics gtest_main gmock)

add_test(game_test ${EXECUTABLE_OUTPUT_PATH}/game_test --gtest_color=yes)
