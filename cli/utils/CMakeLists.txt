add_library(cli-utils STATIC)

target_sources(cli-utils
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/arg-parser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/exec-helper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/files-helper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/string-normalizer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/toml-validator.cpp
)

# target_include_directories(cli-utils
#   PUBLIC
#     ${CMAKE_CURRENT_SOURCE_DIR}/include
#   PRIVATE
#     ${CMAKE_CURRENT_SOURCE_DIR}/../cli/commands/init/include
# )

target_include_directories(cli-utils
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# include(FetchContent)
# 
# FetchContent_Declare(
#   CLI11
#   GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
#   GIT_TAG v2.4.2
# )
# 
# FetchContent_MakeAvailable(CLI11)

include(FetchContent)

FetchContent_Declare(
  tomlplusplus
  GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
  GIT_TAG        v3.4.0
)
FetchContent_MakeAvailable(tomlplusplus)

target_link_libraries(cli-utils
  PUBLIC
    CLI11::CLI11
  PRIVATE
    cli-commands-init
    cli-commands-new
    cli-core
    tomlplusplus::tomlplusplus
)
