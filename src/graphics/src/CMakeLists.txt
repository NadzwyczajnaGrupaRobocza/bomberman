find_package(SFML 2 COMPONENTS system graphics window REQUIRED)
find_package(Boost 1.6 REQUIRED)

add_library(graphics
  core/RendererPoolFactory.cpp
  core/RendererPoolSfml.cpp
  core/RenderTarget.cpp
  core/RendererIdGenerator.cpp
  core/SfmlRectangleShape.cpp
  core/WindowSfml.cpp
  core/SfmlWindowFacade.cpp)

target_include_directories(graphics
  PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../includes
  PRIVATE ${CMAKE_CURRENT_LIST_DIR}/core
          ${CMAKE_CURRENT_LIST_DIR}/types)

target_include_directories(graphics SYSTEM
  PRIVATE ${SFML_INCLUDE_DIR}
          Boost::boost)

target_link_libraries(graphics
  PRIVATE ${SFML_LIBRARIES}
  PUBLIC math)

add_executable(graphics-ut
  core/RendererPoolSfml.ut.cpp
  core/RenderTarget.ut.cpp
  core/SfmlRectangleShape.ut.cpp
  core/WindowSfml.ut.cpp)

target_include_directories(graphics-ut SYSTEM BEFORE
  PRIVATE ${CMAKE_CURRENT_LIST_DIR}/core
          ${CMAKE_CURRENT_LIST_DIR}/types
          ${UT_INCLUDES}
          ${SFML_INCLUDE_DIR})

target_compile_options(graphics-ut
  PRIVATE "-Wno-disabled-macro-expansion")

target_link_libraries(graphics-ut
  PRIVATE --coverage graphics gmock_main ${SFML_LIBRARIES})

add_test(graphics-ut ${EXECUTABLE_OUTPUT_PATH}/graphics-ut --gtest_color=yes)
