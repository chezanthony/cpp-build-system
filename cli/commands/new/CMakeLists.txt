add_library(cli-commands-new INTERFACE)

target_include_directories(cli-commands-new
  INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(cli-commands-new
  INTERFACE
    cli-utils
)
