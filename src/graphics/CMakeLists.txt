add_executable(graphics_ut
  RenderEngine.ut.cpp
  )

target_include_directories(graphics_ut SYSTEM PRIVATE
  ${UT_INCLUDES}
  )


target_link_libraries(graphics_ut gtest_main)
add_test(graphics_ut ${EXECUTABLE_OUTPUT_PATH}/graphics_ut --gtest_color=yes)
