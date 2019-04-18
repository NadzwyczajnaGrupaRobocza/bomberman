message(STATUS "Detected system with gcc compiler.")

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
-g ")
