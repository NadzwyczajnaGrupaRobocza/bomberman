cmake_minimum_required (VERSION 2.8.11)

message(STATUS "Detected system with clang compiler.")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything -Werror\
 -Wno-c++98-compat -Wno-c++98-compat-pedantic\
 -Wno-c++98-c++11-compat-pedantic -Wno-undefined-internal\
 -Wno-exit-time-destructors -Wno-global-constructors\
 -Wno-unknown-pragmas -Wno-missing-prototypes -Wno-undef\
 -Wno-language-extension-token -Wno-missing-noreturn -Wno-missing-noreturn\
 -Wno-language-extension-token -Wno-used-but-marked-unused\
 -Wno-shift-sign-overflow -Wno-deprecated -Wno-documentation-deprecated-sync\
 -Wno-weak-vtables -Wno-sign-conversion -Wno-padded -Wno-covered-switch-default")

target_compile_options(gtest PRIVATE "-Wno-deprecated-declarations")
target_compile_options(gmock PRIVATE "-Wno-deprecated-declarations")
target_compile_options(gtest_main PRIVATE "-Wno-deprecated-declarations")
target_compile_options(gmock_main PRIVATE "-Wno-deprecated-declarations")
