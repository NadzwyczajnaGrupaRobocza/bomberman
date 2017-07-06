set(UT_INCLUDES ${FAKEIT_INCLUDE_DIR} ${GMOCK_INCLUDE_DIR} ${GTEST_INCLUDE_DIR})

add_subdirectory(graphics)
set(GRAPHICS_INCLUDE_PATH ${CMAKE_CURRENT_LIST_DIR}/graphics)

add_subdirectory(game)
