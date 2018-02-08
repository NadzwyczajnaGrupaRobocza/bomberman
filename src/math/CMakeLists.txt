add_library(math INTERFACE)

target_include_directories(math
  INTERFACE ${CMAKE_CURRENT_LIST_DIR}/includes)
