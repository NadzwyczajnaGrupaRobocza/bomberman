target_sources(simple_moving_rectangle
  PRIVATE ${CMAKE_CURRENT_LIST_DIR}/SimpleMovingRectangle.cpp)

target_include_directories(simple_moving_rectangle SYSTEM
  PRIVATE ${SFML_INCLUDE_DIR})

target_link_libraries(simple_moving_rectangle
  PRIVATE graphics ${SFML_LIBRARIES})
