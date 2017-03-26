cmake_minimum_required (VERSION 2.8.11)
project("bomberman")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/.cmakes/modules" ${CMAKE_MODULE_PATH})

find_package(SFML 2 COMPONENTS system window graphics network audio)

if(SFML_FOUND)
  enable_testing()

  set(RANGEV3_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/external/range-v3/include/")
  set(FAKEIT_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/external/fakeit/single_header/gtest/")
  set(GSL_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/external/GSL/include")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGSL_THROW_ON_CONTRACT_VIOLATION")

  add_subdirectory(external/googletest/googletest)

  if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    include(${CMAKE_SOURCE_DIR}/.cmakes/platforms/Windows.cmake)
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
  endif()

  if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    include(${CMAKE_SOURCE_DIR}/.cmakes/compilators/Clang.cmake)
  elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    include(${CMAKE_SOURCE_DIR}/.cmakes/compilators/Msvc.cmake)
  else()
    include(${CMAKE_SOURCE_DIR}/.cmakes/compilators/Gcc.cmake)
  endif()

  include_directories(SYSTEM ${RANGEV3_INCLUDE_DIR})
  include_directories(SYSTEM ${SFML_INCLUDE_DIR})
  include_directories(SYSTEM ${GSL_INCLUDE_DIR})
  add_subdirectory(bomberman)
endif()
