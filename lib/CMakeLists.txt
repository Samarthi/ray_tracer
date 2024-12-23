add_executable(
  lib
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)
target_link_libraries(lib PRIVATE tracer)
