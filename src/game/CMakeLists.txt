add_executable(game_test
  Entity.ut.cpp
  )

target_include_directories(game_test SYSTEM PRIVATE
  ${UT_INCLUDES}
  )


target_link_libraries(game_test gtest_main)
add_test(game_test ${EXECUTABLE_OUTPUT_PATH}/game_test --gtest_color=yes)

add_library(game
  HumanPlayerSfml.cpp
  )
