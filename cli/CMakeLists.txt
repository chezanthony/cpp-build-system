find_package(Boost REQUIRED COMPONENTS program_options)

add_executable(cbs main.cpp)

target_link_libraries(cbs
  PRIVATE
    Boost::program_options
    cli-commands-base
    build
)

add_subdirectory(commands)
