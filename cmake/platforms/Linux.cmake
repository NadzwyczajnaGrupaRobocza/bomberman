message(STATUS "Detected GNU CXX compiler.")

option(ENABLE_COVERAGE "Enable coverage reporting for gcc/clang" FALSE)

if(${ENABLE_COVERAGE})
  add_compile_options(--coverage -O0)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
