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
  set(CMAKE_INCLUDE_SYSTEM_FLAG_CXX "/imsvc ")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
  -Xclang -std=c++17")
endif()

# It is a workaround for boost uuid issue #78
link_libraries(bcrypt)
