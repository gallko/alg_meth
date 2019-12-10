cmake_minimum_required(VERSION 3.10)

project(StepikAlgorithmsStructures VERSION 0.1 LANGUAGES CXX)

set(EXTERNAL_LIB ext_lib)

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(src)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${EXTERNAL_LIB}/googletest
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)
