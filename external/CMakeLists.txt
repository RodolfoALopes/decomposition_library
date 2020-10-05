# Catch (Unit Tests) - https://github.com/catchorg/Catch2
set(CATCH_USE_VALGRIND OFF CACHE BOOL "Perform SelfTests with Valgrind" FORCE)
set(CATCH_BUILD_TESTING OFF CACHE BOOL "Build SelfTest project" FORCE)
set(CATCH_BUILD_EXAMPLES OFF CACHE BOOL "Build documentation examples" FORCE)
set(CATCH_BUILD_EXTRA_TESTS OFF CACHE BOOL "Build extra tests" FORCE)
set(CATCH_ENABLE_COVERAGE OFF CACHE BOOL "Generate coverage for codecov.io" FORCE)
set(CATCH_ENABLE_WERROR ON CACHE BOOL "Enable all warnings as errors" FORCE)
set(CATCH_INSTALL_DOCS OFF CACHE BOOL "Install documentation alongside library" FORCE)
set(CATCH_INSTALL_HELPERS OFF CACHE BOOL "Install contrib alongside library" FORCE)
set(CMAKE_POLICY_DEFAULT_CMP0042 NEW)
add_subdirectory(Catch2 EXCLUDE_FROM_ALL)

add_library(catch_main Catch2/examples/000-CatchMain.cpp)
target_link_libraries(catch_main Catch2::Catch2)

include(CTest)
include(Catch2/contrib/Catch.cmake)
set(catch_discover_tests PARENT_SCOPE)