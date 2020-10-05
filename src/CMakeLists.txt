set(DECOMPOSITION_SRCS
        ${DECOMPOSITION_LIB_INCLUDE_DIR}/common.h
        ${DECOMPOSITION_LIB_INCLUDE_DIR}/decomposition.h
        ${DECOMPOSITION_LIB_INCLUDE_DIR}/problem.h
        ${DECOMPOSITION_LIB_INCLUDE_DIR}/solver.h
        ${DECOMPOSITION_LIB_INCLUDE_DIR}/differential_grouping_method.h
        ${DECOMPOSITION_LIB_INCLUDE_DIR}/differential_grouping_2_method.h
        ${DECOMPOSITION_LIB_INCLUDE_DIR}/extended_differential_grouping_method.h
        ${DECOMPOSITION_LIB_INCLUDE_DIR}/fast_interdependency_identification_method.h
        ${DECOMPOSITION_LIB_INCLUDE_DIR}/global_differential_grouping_method.h
        ${DECOMPOSITION_LIB_INCLUDE_DIR}/recursive_differential_grouping_1_method.h
        ${DECOMPOSITION_LIB_INCLUDE_DIR}/recursive_differential_grouping_2_method.h
        ${DECOMPOSITION_LIB_INCLUDE_DIR}/recursive_differential_grouping_3_method.h
        ${CMAKE_CURRENT_SOURCE_DIR}/differential_grouping_method.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/differential_grouping_2_method.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/extended_differential_grouping_method.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/fast_interdependency_identification_method.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/global_differential_grouping_method.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/recursive_differential_grouping_1_method.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/recursive_differential_grouping_2_method.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/recursive_differential_grouping_3_method.cpp
        )

add_library(libdecomposition ${DECOMPOSITION_SRCS})

target_include_directories(libdecomposition PUBLIC
        ${DECOMPOSITION_LIB_INCLUDE_DIR}
        )

#set_target_properties(libdecomposition PROPERTIES ENABLE_EXPORTS 1)

#install(TARGETS libdecomposition
#        RUNTIME DESTINATION .
#        LIBRARY DESTINATION libraries
#        ARCHIVE DESTINATION libraries
#        COMPONENT library)
