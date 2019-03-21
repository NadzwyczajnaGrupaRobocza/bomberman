set(UT_INCLUDES ${FAKEIT_INCLUDE_DIR} ${GMOCK_INCLUDE_DIR} ${GTEST_INCLUDE_DIR})
set(INTERNAL_LIBS_INCLUDE_PATH ${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(graphics)
add_subdirectory(physics)
add_subdirectory(math)
add_subdirectory(game)

