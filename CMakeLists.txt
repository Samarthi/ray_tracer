cmake_minimum_required(VERSION 3.14)
project(ray_tracer)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
      GIT_REPOSITORY https://github.com/google/googletest.git
      GIT_TAG v1.15.2
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_subdirectory(
  lib
)


add_executable(
  tests
  tests/tests.cpp
)
set(CMAKE_VERBOSE_MAKEFILE ON)
target_link_libraries(tests PRIVATE lib)
target_link_libraries( 
  tests
  PRIVATE
  GTest::gtest_main
)

target_include_directories(tests PUBLIC "${PROJECT_SOURCE_DIR}/include")
include(GoogleTest)
gtest_discover_tests(tests)

