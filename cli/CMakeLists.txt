add_executable(cbs main.cpp)

target_link_libraries(cbs
  PRIVATE
    build
)

add_subdirectory(commands)
