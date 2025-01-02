cmake_minimum_required(VERSION 3.14)
project(ray_tracer)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(lib)

add_executable(
  main
  src/main.cpp
)

set(CMAKE_VERBOSE_MAKEFILE ON)
target_link_libraries(main PRIVATE lib)
target_include_directories(main PUBLIC "${PROJECT_SOURCE_DIR}/include")

