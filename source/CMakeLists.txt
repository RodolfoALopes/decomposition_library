#######################################################
### Library                                         ###
#######################################################
add_library(libdecomposition
        decomposition/common.h
        decomposition/decomposition.h
        decomposition/problem.h
        decomposition/solver.h
        decomposition/differential_grouping_method.h
        decomposition/differential_grouping_2_method.h
        decomposition/extended_differential_grouping_method.h
        decomposition/fast_interdependency_identification_method.h
        decomposition/global_differential_grouping_method.h
        decomposition/recursive_differential_grouping_1_method.h
        decomposition/recursive_differential_grouping_2_method.h
        decomposition/recursive_differential_grouping_3_method.h
        decomposition/common.cpp
        decomposition/problem.cpp
        decomposition/solver.cpp
        decomposition/differential_grouping_method.cpp
        decomposition/differential_grouping_2_method.cpp
        decomposition/extended_differential_grouping_method.cpp
        decomposition/fast_interdependency_identification_method.cpp
        decomposition/global_differential_grouping_method.cpp
        decomposition/recursive_differential_grouping_1_method.cpp
        decomposition/recursive_differential_grouping_2_method.cpp
        decomposition/recursive_differential_grouping_3_method.cpp
        )

target_include_directories(libdecomposition PUBLIC ${DECOMPOSITION_LIB_INCLUDE_DIR})

target_include_directories(libdecomposition
        INTERFACE $<BUILD_INTERFACE:${DECOMPOSITION_ROOT_DIR}/source>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

if (BUILD_WITH_PEDANTIC_WARNINGS)
    if (MSVC)
        target_compile_options(libdecomposition INTERFACE /W4 /WX)
    else ()
        # -Wno-self-assign-overloaded has a false positive that prevents pybind11
        # from working
        target_compile_options(libdecomposition INTERFACE -Wall -Wextra -pedantic -Werror -Wno-self-assign-overloaded)
    endif ()
endif ()


#######################################################
### Installer                                       ###
#######################################################
if (BUILD_INSTALLER)
    # Install hv and pareto_front targets
    # Because pareto_front is INTERFACE, this installs no artifacts
    # but includes pareto_front in the EXPORT
    install(TARGETS libdecomposition
            EXPORT DecompositionTargets
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            )

    # Install headers
    install(DIRECTORY ${DECOMPOSITION_ROOT_DIR}/source/
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
            FILES_MATCHING PATTERN "*.h"
            )

    # Install cmake script that imports the targets
    install(EXPORT DecompositionTargets
            FILE DecompositionTargets.cmake
            NAMESPACE DecompositionTargets::
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Decomposition
            )
endif ()