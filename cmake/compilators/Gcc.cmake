message(STATUS "Detected system with gcc compiler v${CMAKE_CXX_COMPILER_VERSION}")

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
-pedantic \
-g \
-Werror")
