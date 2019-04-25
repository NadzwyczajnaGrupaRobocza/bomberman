cmake_minimum_required (VERSION 3.2.2)
project("bomberman" CXX)

find_package(Boost 1.6 REQUIRED)

set(CMAKE_CXX_EXTENSIONS OFF)

option(TREAT_WARNING_AS_ERROR "" ON)

if(TREAT_WARNING_AS_ERROR)
  message(STATUS "Treat warning as error ON")
else()
  message(STATUS "Treat warning as error OFF")
endif()

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

set(CMAKE_CXX_STANDARD 20)

set(SFML_MINIMAL_VERSION 2.5.1)

enable_testing()

add_subdirectory(external/googletest/)

if(${WIN32})
  include(${CMAKE_SOURCE_DIR}/cmake/platforms/Windows.cmake)
else()
  include(${CMAKE_SOURCE_DIR}/cmake/platforms/Linux.cmake)
endif()

if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
  include(${CMAKE_SOURCE_DIR}/cmake/compilators/Clang.cmake)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
  include(${CMAKE_SOURCE_DIR}/cmake/compilators/Msvc.cmake)
else()
  include(${CMAKE_SOURCE_DIR}/cmake/compilators/Gcc.cmake)
endif()

include_directories(SYSTEM ${RANGEV3_INCLUDE_DIR})
include_directories(SYSTEM ${GSL_INCLUDE_DIR})
include_directories(SYSTEM ${GLM_INCLUDE_DIR})
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

add_subdirectory(src)

include(${CMAKE_SOURCE_DIR}/cmake/utils/PlantUml.cmake)

