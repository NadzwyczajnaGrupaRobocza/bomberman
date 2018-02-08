find_package(SFML 2 COMPONENTS window graphics REQUIRED)

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

add_executable(game-ut
  BoundaryWallsPositionsGenerator.ut.cpp
  Entity.ut.cpp
  Map.ut.cpp
  SimpleMap.ut.cpp
  TimeBomb.ut.cpp
  )


target_include_directories(game-ut SYSTEM PRIVATE
  ${UT_INCLUDES}
  )

  
target_include_directories(game PRIVATE
  ${INTERNAL_LIBS_INCLUDE_PATH}
  ${SFML_INCLUDE_DIR}
  )

target_include_directories(game-ut PRIVATE
  ${INTERNAL_LIBS_INCLUDE_PATH}
  )

add_executable(Bomberman main.cpp)

target_include_directories(Bomberman PRIVATE
  ${INTERNAL_LIBS_INCLUDE_PATH}
  ${SFML_INCLUDE_DIR}
)

target_link_libraries(game-ut
  PRIVATE game graphics gtest_main gmock)

add_test(game-ut ${EXECUTABLE_OUTPUT_PATH}/game-ut --gtest_color=yes)
target_link_libraries(Bomberman game ${SFML_LIBRARIES})

