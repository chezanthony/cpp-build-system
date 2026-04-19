add_library(cli-commands-new STATIC)

target_sources(cli-commands-new
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/new-utils.cpp
)

target_include_directories(cli-commands-new
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(cli-commands-new
  PUBLIC
    cli-utils
    cli-core
)
