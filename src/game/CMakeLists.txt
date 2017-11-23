find_package(SFML 2 COMPONENTS graphics REQUIRED)

add_library(game
  TimeBomb.cpp
  HumanPlayerSfml.cpp
  BombermanGameWorld.cpp
  )

target_include_directories(game SYSTEM
  PRIVATE ${SFML_INCLUDE_DIR}
  PUBLIC math)

add_executable(game_test
  TimeBomb.ut.cpp
  Entity.ut.cpp
  Map.ut.cpp
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

target_link_libraries(game_test gtest_main game)
add_test(game_test ${EXECUTABLE_OUTPUT_PATH}/game_test --gtest_color=yes)
