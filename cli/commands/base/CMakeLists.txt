add_library(cli-commands-base INTERFACE)

target_include_directories(cli-commands-base
  INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

