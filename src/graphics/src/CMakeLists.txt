find_package(SFML ${SFML_MINIMAL_VERSION} COMPONENTS system graphics window REQUIRED)

########################### SRC ###########################
add_library(graphics
  factory.cpp
  renderer_id_generator.cpp
  sfml_rectangle_shape.cpp
  sfml_renderer_pool.cpp
  sfml_texture_warehous.cpp
  simple_sfml_texture_loader.cpp
  window/sfml_window.cpp
  window/sfml_window_proxy.cpp
  )

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
  sfml_rectangle_shape.ut.cpp
  sfml_render_target.ut.cpp
  sfml_renderer_pool.ut.cpp
  sfml_texture_warehous.ut.cpp
  window/sfml_window.ut.cpp
  )

target_compile_options(graphics-ut PRIVATE
  -Wno-used-but-marked-unused
  -Wno-covered-switch-default
  -Wno-deprecated)

target_include_directories(graphics-ut SYSTEM BEFORE
  PRIVATE ${CMAKE_CURRENT_LIST_DIR}
          ${CMAKE_CURRENT_LIST_DIR}/../types
          ${UT_INCLUDES}
          ${SFML_INCLUDE_DIR})

target_link_libraries(graphics-ut
  PRIVATE graphics gmock_main ${SFML_LIBRARIES})

add_test(
  NAME graphics-ut
  COMMAND ${EXECUTABLE_OUTPUT_PATH}/graphics-ut --gtest_color=yes
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
