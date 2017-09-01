find_package(SFML 2 COMPONENTS system graphics REQUIRED)

set(CPP_DIR graphics/details)

add_library(graphics
  ${CPP_DIR}/RendererPoolFactory.cpp
  ${CPP_DIR}/RendererPoolSfml.cpp
  ${CPP_DIR}/RenderTarget.cpp
  ${CPP_DIR}/RendererIdGenerator.cpp
  ${CPP_DIR}/SfmlRectangleShape.cpp)

target_include_directories(graphics
  PUBLIC ${CMAKE_CURRENT_LIST_DIR}
  PRIVATE ${CMAKE_CURRENT_LIST_DIR}/graphics)

target_link_libraries(graphics
  PRIVATE ${SFML_LIBRARIES})

add_executable(graphics_ut
  ${CPP_DIR}/RendererPoolSfml.ut.cpp
  ${CPP_DIR}/RenderTarget.ut.cpp
  ${CPP_DIR}/SfmlRectangleShape.ut.cpp)

target_include_directories(graphics_ut SYSTEM BEFORE
  PRIVATE ${CMAKE_CURRENT_LIST_DIR}/graphics
  ${UT_INCLUDES})

target_compile_options(graphics_ut
  PRIVATE "-Wno-disabled-macro-expansion")

target_link_libraries(graphics_ut
  PRIVATE graphics gmock_main)

add_test(graphics_ut ${EXECUTABLE_OUTPUT_PATH}/graphics_ut --gtest_color=yes)
