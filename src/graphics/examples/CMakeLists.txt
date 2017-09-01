find_package(SFML 2 COMPONENTS window REQUIRED)

add_executable(simple_rectangle_draw
  SimpleRectangleDraw.cpp)

target_link_libraries(simple_rectangle_draw
  PRIVATE graphics ${SFML_LIBRARIES})
