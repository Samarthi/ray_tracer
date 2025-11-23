cmake_minimum_required(VERSION 3.14)
project(ray_tracer)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)


FetchContent_MakeAvailable(googletest)

add_subdirectory(lib)

add_executable(
  main
  src/main.cpp
)



set(CMAKE_VERBOSE_MAKEFILE ON)
target_link_libraries(
  main PRIVATE lib
)
target_include_directories(main PUBLIC "${PROJECT_SOURCE_DIR}/include")


enable_testing()

add_executable(
  hello_test
  tests/hello_test.cc
)

target_link_libraries(
  hello_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(hello_test)
