find_package(SFML 2 COMPONENTS window REQUIRED)

include_directories(SYSTEM ${SFML_INCLUDE_DIR})
link_libraries(graphics ${SFML_LIBRARIES})

add_executable(simple-rectangle-draw SimpleRectangleDraw.cpp)
add_executable(simple-moving-rectangle SimpleMovingRectangle.cpp)

add_custom_target(graphics-examples DEPENDS
  simple-rectangle-draw
  simple-moving-rectangle)
