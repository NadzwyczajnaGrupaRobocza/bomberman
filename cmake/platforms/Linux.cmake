message(STATUS "Detected GNU CXX compiler.")

option(ENABLE_COVERAGE "Enable coverage reporting for gcc/clang" FALSE)

if(${ENABLE_COVERAGE})
  add_compile_options(--coverage -O0)
  link_libraries(--coverage)
endif()

set(CMAKE_CXX_STANDARD 14)
