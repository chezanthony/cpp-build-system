add_library(cli-commands-build STATIC)

target_sources(cli-commands-build
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/test.cpp
)

target_include_directories(cli-commands-build
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

