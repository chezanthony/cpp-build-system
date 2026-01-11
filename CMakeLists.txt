cmake_minimum_required(VERSION 3.15)

project(cpp-build-system
  VERSION 0.0.1
  DESCRIPTION "The unified C++ build system"
  LANGUAGES CXX
)

message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Version: ${PROJECT_VERSION}")
message(STATUS "Description: ${PROJECT_DESCRIPTION}")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(cli)
