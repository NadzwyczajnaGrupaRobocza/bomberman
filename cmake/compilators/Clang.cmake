message(STATUS "Detected system with clang compiler v"
  ${CMAKE_CXX_COMPILER_VERSION})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything -Werror\
 -Wno-c++98-compat -Wno-c++98-compat-pedantic\
 -Wno-c++98-c++11-compat-pedantic -Wno-weak-vtables -Wno-padded\
 -Wno-global-constructors -Wno-extra-semi -Wno-disabled-macro-expansion")

if(${CMAKE_CXX_COMPILER_VERSION} GREATER 4)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-zero-as-null-pointer-constant")
endif()

target_compile_options(gtest PRIVATE "-Wno-deprecated-declarations")
target_compile_options(gmock PRIVATE "-Wno-deprecated-declarations")
target_compile_options(gtest_main PRIVATE "-Wno-deprecated-declarations")
target_compile_options(gmock_main PRIVATE "-Wno-deprecated-declarations")
