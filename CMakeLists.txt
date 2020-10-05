cmake_minimum_required(VERSION 3.9)
project(decomposition_library)

set(CMAKE_CXX_STANDARD 11)


set(DECOMPOSITION_LIB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_subdirectory(external)
add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(unit_tests)
