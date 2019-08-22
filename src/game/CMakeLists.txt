find_package(SFML ${SFML_MINIMAL_VERSION} COMPONENTS window REQUIRED)

add_library(game
  Bomberman.cpp
  BombermanGameWorld.cpp
  BoundaryWallsPositionsGenerator.cpp
  DefaultBombFactory.cpp
  ExplosionRange.cpp
  HumanPlayerSfml.cpp
  InsideWallsPositionsGenerator.cpp
  LimitedBombLauncher.cpp
  SimpleMap.cpp
  TimeBomb.cpp
  )

target_include_directories(game SYSTEM
  PRIVATE ${SFML_INCLUDE_DIR})

target_link_libraries(game
  PUBLIC math
  PRIVATE graphics
  )

add_executable(game-ut
  Bomberman.ut.cpp
  BoundaryWallsPositionsGenerator.ut.cpp
  Entity.ut.cpp
  InsideWallsPositionsGenerator.ut.cpp
  LimitedBombLauncher.ut.cpp
  Map.ut.cpp
  SimpleMap.ut.cpp
  TimeBomb.ut.cpp
  )


target_include_directories(game-ut SYSTEM PRIVATE
  ${UT_INCLUDES}
  ${SFML_INCLUDE_DIR}
  )

target_compile_options(game-ut PRIVATE
  -Wno-used-but-marked-unused)

target_include_directories(game PRIVATE
  ${INTERNAL_LIBS_INCLUDE_PATH}
  ${SFML_INCLUDE_DIR}
  )

target_include_directories(game-ut PRIVATE
  ${INTERNAL_LIBS_INCLUDE_PATH}
  )

add_executable(Bomberman main.cpp)

target_include_directories(Bomberman SYSTEM
     PRIVATE ${INTERNAL_LIBS_INCLUDE_PATH} ${SFML_INCLUDE_DIR}
)

target_link_libraries(game-ut
  PRIVATE game graphics gtest_main gmock)

add_test(game-ut ${EXECUTABLE_OUTPUT_PATH}/game-ut --gtest_color=yes)
target_link_libraries(Bomberman PRIVATE game ${SFML_LIBRARIES} graphics physics math editor)
