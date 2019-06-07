find_package(SFML ${SFML_MINIMAL_VERSION} COMPONENTS window REQUIRED)

if(HOT_RELOAD)
  add_library(editor src/JetLive.cpp)
else()
  add_library(editor src/ColdReload.cpp)
endif()

target_include_directories(editor SYSTEM
  PRIVATE include/editor ${SFML_INCLUDE_DIR}
  PUBLIC include)
