find_package(SFML 2.4.2 COMPONENTS window REQUIRED)

add_executable(simple_rectangle_draw
  SimpleRectangleDraw.cpp)

target_include_directories(simple_rectangle_draw SYSTEM
  PRIVATE ${SFML_INCLUDE_DIR})

target_link_libraries(simple_rectangle_draw
  PRIVATE graphics ${SFML_LIBRARIES})
