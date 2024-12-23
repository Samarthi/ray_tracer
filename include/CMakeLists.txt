
add_library(
  include
  tuple.h
)
set_target_properties(include PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(include PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

