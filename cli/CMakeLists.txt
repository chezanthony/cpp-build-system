# find_package(Boost REQUIRED COMPONENTS program_options)

add_executable(cbs main.cpp)

# target_link_libraries(cbs
#   PRIVATE
#     Boost::program_options
#     cli-commands-base
#     cli-commands-build
#     cli-utils
# )

include(FetchContent)

FetchContent_Declare(
  CLI11
  GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
  GIT_TAG v2.4.2
)

FetchContent_MakeAvailable(CLI11)

target_link_libraries(cbs
  PUBLIC
    CLI11::CLI11
  PRIVATE
    cli-commands-base
    cli-commands-build
    cli-commands-init
    cli-utils
)

add_subdirectory(commands)
add_subdirectory(core)
add_subdirectory(utils)
