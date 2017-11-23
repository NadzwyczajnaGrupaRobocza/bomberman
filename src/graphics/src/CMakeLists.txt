find_package(SFML 2 COMPONENTS system graphics REQUIRED)
find_package(Boost 1.6 REQUIRED)

add_library(graphics
  RendererPoolFactory.cpp
  RendererPoolSfml.cpp
  RenderTarget.cpp
  RendererIdGenerator.cpp
  SfmlRectangleShape.cpp)

target_include_directories(graphics
  PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../includes
  PRIVATE ${CMAKE_CURRENT_LIST_DIR})

target_include_directories(graphics SYSTEM
  PRIVATE ${SFML_INCLUDE_DIR}
          Boost::boost)

target_link_libraries(graphics
  PRIVATE ${SFML_LIBRARIES}
  PUBLIC math)

add_executable(graphics-ut
  RendererPoolSfml.ut.cpp
  RenderTarget.ut.cpp
  SfmlRectangleShape.ut.cpp)

target_include_directories(graphics-ut SYSTEM BEFORE
  PRIVATE ${CMAKE_CURRENT_LIST_DIR}
          ${UT_INCLUDES}
          ${SFML_INCLUDE_DIR})

target_compile_options(graphics-ut
  PRIVATE "-Wno-disabled-macro-expansion")

target_link_libraries(graphics-ut
  PRIVATE graphics gmock_main)

add_test(graphics-ut ${EXECUTABLE_OUTPUT_PATH}/graphics-ut --gtest_color=yes)
