add_library(physics-lib STATIC
  Physics/Private/Collision.cpp
  Physics/Private/Collider.cpp)

target_include_directories(physics-lib PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/Physics/Public
  ${CMAKE_CURRENT_LIST_DIR}/Bomberman/Public
  )

add_executable(bomberman
  Bomberman/Private/Bomberman.cpp
  Bomberman/Private/Entity.cpp
  Bomberman/Private/Board.cpp
  Bomberman/Private/RedAllert.cpp
  Bomberman/Private/GreenAllert.cpp)

target_include_directories(bomberman PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/Bomberman/Public
  )

target_link_libraries(bomberman physics-lib ${SFML_LIBRARIES})

add_executable(dummy_test
  Dummy_UT/dummy_class.cpp
  Dummy_UT/dummy_class_test.cpp)

target_include_directories(dummy_test SYSTEM PRIVATE
  ${FAKEIT_INCLUDE_DIR}
  )

target_link_libraries(dummy_test gtest_main)
add_test(dummy_test ${EXECUTABLE_OUTPUT_PATH}/dummy_test)
