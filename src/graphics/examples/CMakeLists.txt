find_package(SFML ${SFML_MINIMAL_VERSION} COMPONENTS window REQUIRED)

include_directories(SYSTEM ${SFML_INCLUDE_DIR})
link_libraries(graphics ${SFML_LIBRARIES})

add_executable(draw draw.cpp)
add_executable(clock clock.cpp)
add_executable(lerp lerp.cpp)

add_custom_target(graphics-examples DEPENDS
  draw clock lerp)
