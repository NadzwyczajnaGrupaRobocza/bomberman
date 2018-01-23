find_package(SFML 2 COMPONENTS system graphics window REQUIRED)
find_package(Boost 1.6 REQUIRED)

########################### SRC ###########################
add_library(graphics
  Factory.cpp
  RendererPoolSfml.cpp
  RendererIdGenerator.cpp
  SfmlRectangleShape.cpp
  WindowSfml.cpp
  SfmlWindowFacade.cpp)

target_include_directories(graphics
  PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../includes
  PRIVATE ${CMAKE_CURRENT_LIST_DIR}
          ${CMAKE_CURRENT_LIST_DIR}/../types)

target_include_directories(graphics SYSTEM
  PRIVATE ${SFML_INCLUDE_DIR}
          Boost::boost)

target_link_libraries(graphics
  PRIVATE ${SFML_LIBRARIES}
  PUBLIC math)

########################### UT ###########################
add_executable(graphics-ut
  RendererPoolSfml.ut.cpp
  SfmlRenderTarget.ut.cpp
  SfmlRectangleShape.ut.cpp
  WindowSfml.ut.cpp)

target_include_directories(graphics-ut SYSTEM BEFORE
  PRIVATE ${CMAKE_CURRENT_LIST_DIR}
          ${CMAKE_CURRENT_LIST_DIR}/../types
          ${UT_INCLUDES}
          ${SFML_INCLUDE_DIR}
          Boost::boost)

target_link_libraries(graphics-ut
  PRIVATE graphics gmock_main ${SFML_LIBRARIES})

add_test(graphics-ut ${EXECUTABLE_OUTPUT_PATH}/graphics-ut --gtest_color=yes)
