########################### VARIABLES ###########################
set(SFML_LIBS
  sfml-graphics
  sfml-window
  sfml-system
  # sfml-audio
  # sfml-network
  )

########################### GRAPHICS ###########################

add_library(graphics
  details/RendererPoolFactory.cpp
  details/RendererPoolSfml.cpp
  details/RenderTarget.cpp
  details/RendererIdGenerator.cpp
  details/SfmlRectangleShape.cpp
  details/Conversion.cpp
  )

target_include_directories(graphics SYSTEM PRIVATE
  ${LIBS_INCLUDE_PATH}
  )

############################## UT ##############################

add_executable(graphics_ut
  details/RendererPoolSfml.ut.cpp
  details/RenderTarget.ut.cpp
  details/SfmlRectangleShape.ut.cpp
  )

target_include_directories(graphics_ut SYSTEM BEFORE INTERFACE PRIVATE
  ${LIBS_INCLUDE_PATH}
  ${UT_INCLUDES}
  )

target_compile_options(graphics_ut PRIVATE "-Wno-disabled-macro-expansion")
target_link_libraries(graphics_ut graphics ${SFML_LIBS} gmock_main)
add_test(graphics_ut ${EXECUTABLE_OUTPUT_PATH}/graphics_ut --gtest_color=yes)
