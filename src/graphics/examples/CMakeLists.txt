find_package(SFML ${SFML_MINIMAL_VERSION} COMPONENTS window REQUIRED)

include_directories(SYSTEM ${SFML_INCLUDE_DIR})
link_libraries(graphics ${SFML_LIBRARIES})

add_executable(simple-rectangle-draw simple_rectangle_draw.cpp)
add_executable(simple-moving-rectangle simple_moving_rectangle.cpp)

add_custom_target(graphics-examples DEPENDS
  simple-rectangle-draw
  simple-moving-rectangle)
