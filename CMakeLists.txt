cmake_minimum_required (VERSION 3.2.2)
project("bomberman" CXX)

set(CMAKE_CXX_EXTENSIONS OFF)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules" ${CMAKE_MODULE_PATH})
set(EXTERNAL_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/external")
set(GLM_INCLUDE_DIR "${EXTERNAL_INCLUDE_DIR}/glm/")
set(RANGEV3_INCLUDE_DIR "${EXTERNAL_INCLUDE_DIR}/range-v3/include/")
set(FAKEIT_INCLUDE_DIR "${EXTERNAL_INCLUDE_DIR}/fakeit/single_header/gtest/")
set(GSL_INCLUDE_DIR "${EXTERNAL_INCLUDE_DIR}/GSL/include")
set(GMOCK_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/external/googletest/googlemock/include")
set(GTEST_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/external/googletest/googletest/include")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGSL_THROW_ON_CONTRACT_VIOLATION")

enable_testing()

add_subdirectory(external/googletest/)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
  include(${CMAKE_SOURCE_DIR}/cmake/platforms/Windows.cmake)
else()
  include(${CMAKE_SOURCE_DIR}/cmake/platforms/Linux.cmake)
endif()

if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
  include(${CMAKE_SOURCE_DIR}/cmake/compilators/Clang.cmake)
elseif(MSVC)
  include(${CMAKE_SOURCE_DIR}/cmake/compilators/Msvc.cmake)
else()
  include(${CMAKE_SOURCE_DIR}/cmake/compilators/Gcc.cmake)
endif()

include_directories(SYSTEM ${RANGEV3_INCLUDE_DIR})
include_directories(SYSTEM ${GSL_INCLUDE_DIR})
include_directories(SYSTEM ${GLM_INCLUDE_DIR})

add_subdirectory(src)
