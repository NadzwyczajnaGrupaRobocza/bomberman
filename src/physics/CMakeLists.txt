# add_library(physics "")

# target_link_libraries(physics
#   PUBLIC math)

add_executable(physics-ut
  PhysicsId.ut.cpp
  PhysicsEngine.ut.cpp
  )

target_include_directories(physics-ut SYSTEM
  PRIVATE ${UT_INCLUDES}
  )

target_link_libraries(physics-ut
  PRIVATE math gtest_main)

add_test(physics-ut ${EXECUTABLE_OUTPUT_PATH}/physics-ut --gtest_color=yes)
