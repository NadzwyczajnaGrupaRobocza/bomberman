find_package(SFML ${SFML_MINIMAL_VERSION} COMPONENTS system graphics window REQUIRED)

########################### SRC ###########################
add_library(graphics
  factory.cpp
  sfml_renderer_pool.cpp
  renderer_id_generator.cpp
  sfml_rectangle_shape.cpp
  window/sfml_window.cpp
  window/sfml_window_proxy.cpp)

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
  sfml_renderer_pool.ut.cpp
  sfml_render_target.ut.cpp
  sfml_rectangle_shape.ut.cpp
  window/sfml_window.ut.cpp)

if(NOT ${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
  target_compile_options(graphics-ut PRIVATE
    -Wno-used-but-marked-unused
    -Wno-covered-switch-default)
else()
  target_compile_options(graphics-ut PRIVATE
    /wd4100)
endif()

target_include_directories(graphics-ut SYSTEM BEFORE
  PRIVATE ${CMAKE_CURRENT_LIST_DIR}
          ${CMAKE_CURRENT_LIST_DIR}/../types
          ${UT_INCLUDES}
          ${SFML_INCLUDE_DIR})

target_link_libraries(graphics-ut
  PRIVATE graphics gmock_main ${SFML_LIBRARIES})

add_test(graphics-ut ${EXECUTABLE_OUTPUT_PATH}/graphics-ut --gtest_color=yes)
