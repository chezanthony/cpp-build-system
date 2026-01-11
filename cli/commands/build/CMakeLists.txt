add_library(build STATIC)

target_sources(build
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/test.cpp
)

target_include_directories(build
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
