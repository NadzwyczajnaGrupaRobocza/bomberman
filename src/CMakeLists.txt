set(UT_INCLUDES ${FAKEIT_INCLUDE_DIR} ${GMOCK_INCLUDE_DIR} ${GTEST_INCLUDE_DIR})
set(LIBS_INCLUDE_PATH ${CMAKE_CURRENT_LIST_DIR})
set(GRAPHICS_INCLUDE_PATH ${CMAKE_CURRENT_LIST_DIR}/graphics)

add_subdirectory(graphics)
add_subdirectory(game)
add_subdirectory(examples)
