#######################################################
### Catch2 - Unit tests                             ###
#######################################################
# Find or get Catch2
# Note that CPM will try to "find_package(Catch2)" before downloading it
# See the option CPM_USE_LOCAL_PACKAGES in ROOT/CMakeLists.txt
# This is important: see One Definition Rule (ODR)
CPMAddPackage(
        NAME Catch2
        GITHUB_REPOSITORY catchorg/Catch2
        VERSION 2.12.1
        OPTIONS
        "CATCH_USE_VALGRIND OFF"
        "CATCH_BUILD_TESTING OFF"
        "CATCH_BUILD_EXAMPLES OFF"
        "CATCH_BUILD_EXTRA_TESTS OFF"
        "CATCH_ENABLE_COVERAGE OFF"
        "CATCH_ENABLE_WERROR ON"
        "CATCH_INSTALL_DOCS OFF"
        "CATCH_INSTALL_HELPERS OFF"
)
include(${Catch2_SOURCE_DIR}/contrib/Catch.cmake)
add_library(catch_main ${Catch2_SOURCE_DIR}/examples/000-CatchMain.cpp)
target_link_libraries(catch_main Catch2::Catch2)

#######################################################
### Tests                                           ###
#######################################################
# Differential Grouping - Unit Test
add_executable(differential_grouping_test differential_grouping_test.cpp)
target_link_libraries(differential_grouping_test PUBLIC catch_main libdecomposition)
catch_discover_tests(differential_grouping_test)


# Differential Grouping 2 - Separable Problem - Unit Test
add_executable(differential_grouping_2_test differential_grouping_2_test.cpp)
target_link_libraries(differential_grouping_2_test PUBLIC catch_main libdecomposition)
catch_discover_tests(differential_grouping_2_test)


# Extended Differential Grouping - Unit Test
add_executable(extended_differential_grouping_test extended_differential_grouping_test.cpp)
target_link_libraries(extended_differential_grouping_test PUBLIC catch_main libdecomposition)
catch_discover_tests(extended_differential_grouping_test)


# Fast Interdependency Identification - Unit Test
add_executable(fast_interdependency_identification_test fast_interdependency_identification_test.cpp)
target_link_libraries(fast_interdependency_identification_test PUBLIC catch_main libdecomposition)
catch_discover_tests(fast_interdependency_identification_test)


# Global Differential Grouping - Unit Test
add_executable(global_differential_grouping_test global_differential_grouping_test.cpp)
target_link_libraries(global_differential_grouping_test PUBLIC catch_main libdecomposition)
catch_discover_tests(global_differential_grouping_test)


# Recursive Differential Grouping 1 - Unit Test
add_executable(recursive_differential_grouping_1_test recursive_differential_grouping_1_test.cpp)
target_link_libraries(recursive_differential_grouping_1_test PUBLIC catch_main libdecomposition)
catch_discover_tests(recursive_differential_grouping_1_test)


# Recursive Differential Grouping 2 - Unit Test
add_executable(recursive_differential_grouping_2_test recursive_differential_grouping_2_test.cpp)
target_link_libraries(recursive_differential_grouping_2_test PUBLIC catch_main libdecomposition)
catch_discover_tests(recursive_differential_grouping_2_test)


# Recursive Differential Grouping 3 - Unit Test
add_executable(recursive_differential_grouping_3_test recursive_differential_grouping_3_test.cpp)
target_link_libraries(recursive_differential_grouping_3_test PUBLIC catch_main libdecomposition)
catch_discover_tests(recursive_differential_grouping_3_test)
