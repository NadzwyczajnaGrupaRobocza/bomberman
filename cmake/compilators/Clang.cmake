message(STATUS "Detected system with clang compiler.")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything -Werror\
 -Wno-c++98-compat -Wno-c++98-compat-pedantic\
 -Wno-c++98-c++11-compat-pedantic -Wno-weak-vtables -Wno-padded\
 -Wno-global-constructors")

target_compile_options(gtest PRIVATE "-Wno-deprecated-declarations")
target_compile_options(gtest_main PRIVATE "-Wno-deprecated-declarations")
