FILE(COPY ${DECOMPOSITION_ROOT_DIR}/external/cec2013_benchmark_functions/cec2013_cdatafiles DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
FILE(COPY ${DECOMPOSITION_ROOT_DIR}/experiments/decomposition_solutions DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# DIFFERENTIAL EVOLUTION - COOPERATIVE COEVOLUTION VERSION
add_executable(experiments_de_cc experiments_de_cc.cpp differential_evolution_cooperative_coevolutive.h differential_evolution_cooperative_coevolutive.cpp)
target_include_directories(experiments_de_cc PUBLIC ${DECOMPOSITION_LIB_INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(experiments_de_cc PUBLIC libdecomposition cec_benchmark)
