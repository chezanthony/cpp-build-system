add_library(cli-core STATIC)

target_sources(cli-core
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

target_include_directories(cli-core
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
