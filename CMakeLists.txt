cmake_minimum_required(VERSION 3.14)
project(ray_tracer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "Force gtest to use shared CRT") 

FetchContent_MakeAvailable(googletest)
set(BUILD_SHARED_LIBS ON)
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
    tests/hello_test.cpp
)

target_link_libraries(
    hello_test PRIVATE lib
    GTest::gtest_main
)
target_include_directories(hello_test PUBLIC "${PROJECT_SOURCE_DIR}/include")

include(GoogleTest)
gtest_discover_tests(hello_test)