cmake_minimum_required (VERSION 2.8.11)
project("bomberman")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

enable_testing()

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(external/googletest)

set(GOOGLETEST_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/external/googletest/googletest/include/")
set(GOOGLEMOCK_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/external/googletest/googlemock/include/")
set(GSL_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/external/GSL/include")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGSL_THROW_ON_CONTRACT_VIOLATION")

set(COMMON_INCLUDES ${GOOGLETEST_INCLUDE_DIR} ${GOOGLEMOCK_INCLUDE_DIR})

set(PAPUC_COMMON_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/common/include")

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
  message(STATUS "Detected Windows system.")

  if("${BUILD_SHARED_LIBS}" STREQUAL "ON")
    string(REPLACE "/MTd" "/MDd" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
    string(REPLACE "/MT" "/MD" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
  else()
    string(REPLACE "/MDd" "/MTd" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
    string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
  endif()

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")

  if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --driver-mode=cl -fms-compatibility-version=19")
  endif()
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
endif()

if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
  message(STATUS "Detected system with clang compiler.")

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything -Werror\
 -Wno-c++98-compat -Wno-c++98-compat-pedantic\
 -Wno-c++98-c++11-compat-pedantic -Wno-undefined-internal\
 -Wno-exit-time-destructors -Wno-global-constructors\
 -Wno-unknown-pragmas -Wno-missing-prototypes -Wno-undef\
 -Wno-language-extension-token -Wno-missing-noreturn -Wno-missing-noreturn\
 -Wno-language-extension-token -Wno-used-but-marked-unused\
 -Wno-shift-sign-overflow -Wno-deprecated\
 -Wno-weak-vtables -Wno-sign-conversion -Wno-padded -Wno-covered-switch-default")

  target_compile_options(gtest PRIVATE "-Wno-deprecated-declarations")
  target_compile_options(gmock PRIVATE "-Wno-deprecated-declarations")
  target_compile_options(gtest_main PRIVATE "-Wno-deprecated-declarations")
  target_compile_options(gmock_main PRIVATE "-Wno-deprecated-declarations")

elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
  message(STATUS "Detected system with Microsoft compiler.")

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc /Wall\
 /wd4251 /wd4265 /wd4350 /wd4371 /wd4514 /wd5031 /wd5026 /wd5027\
 /wd4625 /wd4619 /wd4626 /wd4710 /wd4711 /wd4820 /wd4668")

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D not=! /D and=&& /D or=||")

else()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
-Wall \
-Wextra \
-Wconversion \
-Wfloat-equal \
-Wunreachable-code \
-Wswitch-enum \
-Wmissing-declarations \
-Wshadow \
-Wnon-virtual-dtor \
-std=c++14 \
-pedantic \
-g \
-Werror")
endif()

include_directories(${GSL_INCLUDE_DIR})
include_directories(${PAPUC_COMMON_INCLUDE_DIR})

find_package(SFML 2 COMPONENTS system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  add_subdirectory(bomberman)
endif()
