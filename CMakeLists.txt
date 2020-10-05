#######################################################
### Decomposition library                           ###
#######################################################
cmake_minimum_required(VERSION 3.9)
project(decomposition_library)
set(CMAKE_CXX_STANDARD 11)

option(CPM_USE_LOCAL_PACKAGES "Try `find_package` before downloading dependencies" ON)
include(cmake/CPM.cmake)

# Check if this a master project or a subdirectory of another project
if (${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
    set(MASTER_PROJECT ON)
else()
    set(MASTER_PROJECT OFF)
endif()
message("MASTER_PROJECT=${MASTER_PROJECT}")
set(DECOMPOSITION_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(DECOMPOSITION_LIB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

#######################################################
### Options                                         ###
#######################################################
option(BUILD_EXAMPLES "Compile the examples" ${MASTER_PROJECT})
option(BUILD_TESTS "Compile the tests" ${MASTER_PROJECT})

#######################################################
### Build targets                                   ###
#######################################################
add_subdirectory(src)

if (BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if (BUILD_TESTS)
    include(CTest)
    enable_testing()
    add_subdirectory(unit_tests)
endif()
