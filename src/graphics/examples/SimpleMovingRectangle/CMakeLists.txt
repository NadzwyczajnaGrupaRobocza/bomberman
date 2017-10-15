add_executable(simple_moving_rectangle
  SimpleMovingRectangle.cpp)

target_include_directories(simple_moving_rectangle SYSTEM
  PRIVATE ${SFML_INCLUDE_DIR})

target_link_libraries(simple_moving_rectangle
  PRIVATE graphics ${SFML_LIBRARIES})
