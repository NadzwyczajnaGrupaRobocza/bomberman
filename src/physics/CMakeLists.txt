add_executable(physics_ut
  PhysicsId.ut.cpp
  PhysicsEngine.ut.cpp
  )

target_include_directories(physics_ut SYSTEM PRIVATE
  ${UT_INCLUDES}
  )


target_link_libraries(physics_ut gtest_main)
add_test(physics_ut ${EXECUTABLE_OUTPUT_PATH}/physics_ut --gtest_color=yes)
