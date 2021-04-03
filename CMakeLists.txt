#######################################################
### Decomposition library                           ###
#######################################################
cmake_minimum_required(VERSION 3.9)
project(decomposition_library VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 17)

# CMake dependencies for installer
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# Include CPM to find or download packages
# Note that CPM will try to find the packages locally before downloading them
# This avoids ODR problems
option(CPM_USE_LOCAL_PACKAGES "Try `find_package` before downloading dependencies" ON)
include(cmake/CPM.cmake)

# Check if this a master project or a subdirectory of another project
if (${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
    set(MASTER_PROJECT ON)
else ()
    set(MASTER_PROJECT OFF)
endif ()
message("MASTER_PROJECT=${MASTER_PROJECT}")
set(DECOMPOSITION_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#######################################################
### Options                                         ###
#######################################################
option(BUILD_EXPERIMENTS "Compile the experiments" ${MASTER_PROJECT})
option(BUILD_EXAMPLES "Compile the examples" ${MASTER_PROJECT})
option(BUILD_TESTS "Compile the tests" ${MASTER_PROJECT})
option(BUILD_INSTALLER "Build an installation package" ${MASTER_PROJECT})
option(BUILD_PACKAGE "Build an installation package" ${MASTER_PROJECT})

option(BUILD_WITH_PEDANTIC_WARNINGS "Use pedantic warnings. This is useful for developers because many of these warnings will be in continuous integration anyway." ${DEBUG_MODE})

#######################################################
### Build targets                                   ###
#######################################################
add_subdirectory(source)
add_subdirectory(external)

if (BUILD_EXPERIMENTS)
    add_subdirectory(experiments)
endif ()

if (BUILD_EXAMPLES)
    add_subdirectory(examples)
endif ()

if (BUILD_TESTS)
    include(CTest)
    enable_testing()
    add_subdirectory(unit_tests)
endif ()

#######################################################
### Installer                                       ###
#######################################################
if (BUILD_INSTALLER)
    # https://cliutils.gitlab.io/modern-cmake/chapters/install/installing.html
    # Set variable where the cmake config is
    set(CONFIG_INSTALL_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/Decomposition)

    # Create DecompositionConfigVersion.cmake and install it
    write_basic_package_version_file(
            DecompositionConfigVersion.cmake
            VERSION ${PACKAGE_VERSION}
            COMPATIBILITY AnyNewerVersion
    )

    # Create DecompositionConfig.cmake from DecompositionConfig.cmake.in
    # DecompositionConfig.cmake will include the DecompositionTargets.cmake file
    # We could have just renamed DecompositionTargets.cmake to DecompositionConfig.cmake
    # But DecompositionConfig.cmake allows us to include extra dependencies
    configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/DecompositionConfig.cmake.in
            ${CMAKE_CURRENT_BINARY_DIR}/DecompositionConfig.cmake
            INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Decomposition)

    # Install the file DecompositionConfig.cmake
    install(FILES
            ${CMAKE_CURRENT_BINARY_DIR}/DecompositionConfig.cmake
            ${CMAKE_CURRENT_BINARY_DIR}/DecompositionConfigVersion.cmake
            COMPONENT "CPP_Library"
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Decomposition
            )
endif ()

#######################################################
### Packages                                        ###
#######################################################
if (BUILD_INSTALLER AND BUILD_PACKAGE)
    # Set the cpack variables
    # https://cliutils.gitlab.io/modern-cmake/chapters/install/packaging.html

    # The most common cpack variables
    set(CPACK_PACKAGE_NAME "Decomposition")
    set(CPACK_PACKAGE_VENDOR "https://github.com/RodolfoALopes")
    set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Decomposition Algorithms")
    set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
    set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
    set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
    set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
    set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")

    # Set CPACK_SOURCE_IGNORE_FILES with files source packages shouldn't install
    # We get these from .gitignore to avoid redundancy
    FILE(READ .gitignore GITIGNORE_CONTENTS)
    STRING(REGEX REPLACE ";" "\\\\;" GITIGNORE_CONTENTS "${GITIGNORE_CONTENTS}")
    STRING(REGEX REPLACE "\n" ";" GITIGNORE_CONTENTS "${GITIGNORE_CONTENTS}")
    set(CPACK_SOURCE_IGNORE_FILES ${GITIGNORE_CONTENTS})

    # Always include CPack at last
    include(CPack)
endif ()