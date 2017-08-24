########################### VARIABLES ###########################
set(SFML_LIBS
  sfml-graphics
  sfml-window
  sfml-system
  # sfml-audio
  # sfml-network
  )

add_executable(simple_rectangle_draw
  SimpleRectangleDraw.cpp
  )

target_include_directories(simple_rectangle_draw SYSTEM BEFORE INTERFACE PRIVATE
  ${LIBS_INCLUDE_PATH}
  ${UT_INCLUDES}
  )

target_link_libraries(simple_rectangle_draw graphics ${SFML_LIBS} gtest_main)
