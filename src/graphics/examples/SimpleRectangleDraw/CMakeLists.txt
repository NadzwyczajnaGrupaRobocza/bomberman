target_sources(simple_rectangle_draw
  PRIVATE ${CMAKE_CURRENT_LIST_DIR}/SimpleRectangleDraw.cpp)

target_include_directories(simple_rectangle_draw SYSTEM
  PRIVATE ${SFML_INCLUDE_DIR})

target_link_libraries(simple_rectangle_draw
  PRIVATE graphics ${SFML_LIBRARIES})
