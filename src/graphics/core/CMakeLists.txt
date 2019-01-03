find_package(SFML ${SFML_MINIMAL_VERSION} COMPONENTS system graphics window REQUIRED)

########################### SRC ###########################
add_library(graphics
  factory.cpp
  renderer_pool_sfml.cpp
  renderer_id_generator.cpp
  sfml_rectangle_shape.cpp
  window_sfml.cpp
  sfml_window_facade.cpp)

target_include_directories(graphics
  PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../includes
  PRIVATE ${CMAKE_CURRENT_LIST_DIR}
          ${CMAKE_CURRENT_LIST_DIR}/../types)

target_include_directories(graphics SYSTEM
  PRIVATE ${SFML_INCLUDE_DIR}
          )

target_link_libraries(graphics
  PRIVATE ${SFML_LIBRARIES}
  PUBLIC math)

########################### UT ###########################
add_executable(graphics-ut
  renderer_pool_sfml.ut.cpp
  sfml_render_target.ut.cpp
  sfml_rectangle_shape.ut.cpp
  window_sfml.ut.cpp)

target_include_directories(graphics-ut SYSTEM BEFORE
  PRIVATE ${CMAKE_CURRENT_LIST_DIR}
          ${CMAKE_CURRENT_LIST_DIR}/../types
          ${UT_INCLUDES}
          ${SFML_INCLUDE_DIR})

target_link_libraries(graphics-ut
  PRIVATE graphics gmock_main ${SFML_LIBRARIES})

add_test(graphics-ut ${EXECUTABLE_OUTPUT_PATH}/graphics-ut --gtest_color=yes)
