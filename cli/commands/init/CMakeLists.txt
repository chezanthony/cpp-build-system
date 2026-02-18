add_library(cli-commands-init INTERFACE)

target_include_directories(cli-commands-init
  INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(cli-commands-init
  INTERFACE
    CLI11::CLI11
    cli-commands-base
    cli-core
    cli-utils
)
