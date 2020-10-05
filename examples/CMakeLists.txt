# Example 1
add_executable(dg_default_options differential_grouping_default_options.cpp)
target_include_directories(dg_default_options PUBLIC ${DECOMPOSITION_LIB_INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(dg_default_options PUBLIC libdecomposition)


# Example 2
add_executable(dg_example differential_grouping_setting_parameter.cpp)
target_include_directories(dg_example PUBLIC ${DECOMPOSITION_LIB_INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(dg_example PUBLIC libdecomposition)


# Example 3
add_executable(cc_random_solver cooperative_coevolution_random_solver.cpp)
target_include_directories(cc_random_solver PUBLIC ${DECOMPOSITION_LIB_INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(cc_random_solver PUBLIC libdecomposition)