message(STATUS "Detected system with gcc compiler.")

add_compile_options(
  -fdiagnostics-color=always
  -Wall
  -Wextra
  -Wconversion
  -Wfloat-equal
  -Wunreachable-code
  -Wswitch-enum
  -Wmissing-declarations
  -Wshadow
  -Wnon-virtual-dtor
  -pedantic
  -g
  )

if(TREAT_WARNING_AS_ERROR)
  add_compile_options(-Werror)
endif()
