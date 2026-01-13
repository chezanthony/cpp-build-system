add_library(cli-utils STATIC)

target_sources(cli-utils
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/arg-parser.cpp
)

target_include_directories(cli-utils
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

include(FetchContent)

FetchContent_Declare(
  CLI11
  GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
  GIT_TAG v2.4.2
)

FetchContent_MakeAvailable(CLI11)

target_link_libraries(cli-utils
  PUBLIC
    CLI11::CLI11
)
