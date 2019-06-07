message(STATUS "Detected system with clang compiler v"
  ${CMAKE_CXX_COMPILER_VERSION})

add_compile_options(-fcolor-diagnostics
  -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-c++98-c++11-compat-pedantic
  -Wno-weak-vtables -Wno-padded -Wno-global-constructors -Wno-extra-semi -Wno-disabled-macro-expansion)

if(TREAT_WARNING_AS_ERROR)
  add_compile_options(-Werror)
endif()

if(${CMAKE_CXX_COMPILER_VERSION} GREATER 4)
  add_compile_options(-Wno-zero-as-null-pointer-constant)
endif()

set(GTEST_UNUSED_WARNINGS -Wno-deprecated-declarations)

target_compile_options(gtest PRIVATE ${GTEST_UNUSED_WARNINGS})
target_compile_options(gmock PRIVATE ${GTEST_UNUSED_WARNINGS})
target_compile_options(gtest_main PRIVATE ${GTEST_UNUSED_WARNINGS})
target_compile_options(gmock_main PRIVATE ${GTEST_UNUSED_WARNINGS})
