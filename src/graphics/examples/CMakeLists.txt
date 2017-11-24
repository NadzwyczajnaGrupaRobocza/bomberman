find_package(SFML 2 COMPONENTS window REQUIRED)

add_executable(simple_rectangle_draw "")
add_executable(simple_moving_rectangle "")

include(SimpleRectangleDraw/CMakeLists.txt)
include(SimpleMovingRectangle/CMakeLists.txt)

add_custom_target(graphics_examples
  DEPENDS simple_rectangle_draw
          simple_moving_rectangle)
