add_executable(environment_test
  cpp17Test.cpp
  )

target_include_directories(environment_test SYSTEM PRIVATE
  ${UT_INCLUDES}
  )

target_include_directories(environment_test PRIVATE
  ${INTERNAL_LIBS_INCLUDE_PATH}
  )

target_link_libraries(environment_test --coverage gtest_main)
add_test(environment_test ${EXECUTABLE_OUTPUT_PATH}/environment_test --gtest_color=yes)
