cmake_minimum_required (VERSION 2.8.11)

message(STATUS "Detected system with clang compiler.")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything -Werror\
 -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-disabled-macro-expansion\
 -Wno-c++98-c++11-compat-pedantic -Wno-weak-vtables -Wno-padded\
 -Wno-global-constructors\
 -Wno-undef -Wno-missing-noreturn\
 -Wno-language-extension-token -Wno-used-but-marked-unused\
 -Wno-shift-sign-overflow -Wno-deprecated -Wno-documentation-deprecated-sync")

target_compile_options(gtest PRIVATE "-Wno-deprecated-declarations")
target_compile_options(gtest_main PRIVATE "-Wno-deprecated-declarations")