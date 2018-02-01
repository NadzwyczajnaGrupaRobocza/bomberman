message(STATUS "Detected Linux kind system.")

option(ENABLE_COVERAGE "Enable coverage reporting for gcc/clang" FALSE)

if(${ENABLE_COVERAGE})
  add_compile_options(--coverage -O0)
  link_libraries(--coverage)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
