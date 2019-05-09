message(STATUS "Detected system with Msvc compiler v${CMAKE_CXX_COMPILER_VERSION}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /experimental:external /external:anglebrackets \
 /wd4201 /wd4309")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D not=! /D and=&& /D or=||")
