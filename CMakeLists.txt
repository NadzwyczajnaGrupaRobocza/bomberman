cmake_minimum_required (VERSION 2.8.11)
project("bomberman")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules" ${CMAKE_MODULE_PATH})
set(EXTERNAL_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/external")

find_package(SFML 2 COMPONENTS system window graphics network audio)

if(SFML_FOUND)
  enable_testing()

  set(GLM_INCLUDE_DIR "${EXTERNAL_INCLUDE_DIR}/glm/")
  set(RANGEV3_INCLUDE_DIR "${EXTERNAL_INCLUDE_DIR}/range-v3/include/")
  set(FAKEIT_INCLUDE_DIR "${EXTERNAL_INCLUDE_DIR}/fakeit/single_header/gtest/")
  set(GSL_INCLUDE_DIR "${EXTERNAL_INCLUDE_DIR}/GSL/include")
  set(GMOCK_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/external/googletest/googlemock/include")
  set(GTEST_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/external/googletest/googletest/include")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGSL_THROW_ON_CONTRACT_VIOLATION")

  add_subdirectory(external/googletest)

  if(${CMAKE_COMPILER_IS_GNUCXX})
    include(${CMAKE_SOURCE_DIR}/cmake/platforms/Linux.cmake)
  else()
    include(${CMAKE_SOURCE_DIR}/cmake/platforms/Windows.cmake)
  endif()

  if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    include(${CMAKE_SOURCE_DIR}/cmake/compilators/Clang.cmake)
  elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    include(${CMAKE_SOURCE_DIR}/cmake/compilators/Msvc.cmake)
  else()
    include(${CMAKE_SOURCE_DIR}/cmake/compilators/Gcc.cmake)
  endif()

  include_directories(SYSTEM ${RANGEV3_INCLUDE_DIR})
  include_directories(SYSTEM ${SFML_INCLUDE_DIR})
  include_directories(SYSTEM ${GSL_INCLUDE_DIR})
  include_directories(SYSTEM ${GLM_INCLUDE_DIR})

  add_subdirectory(src)
endif()
