# find_package(Boost REQUIRED COMPONENTS program_options)

add_executable(cbs main.cpp)

# target_link_libraries(cbs
#   PRIVATE
#     Boost::program_options
#     cli-commands-base
#     cli-commands-build
#     cli-utils
# )

target_link_libraries(cbs
  PRIVATE
    cli-commands-base
    cli-commands-build
    cli-utils
)

add_subdirectory(commands)
# add_subdirectory(core)
add_subdirectory(utils)
