cmake_minimum_required(VERSION 3.14)
project(Assignment1)

set(CMAKE_CXX_STANDARD 17)

# -----------------------
# Force MSVC runtime to /MD or /MDd
# -----------------------
# This makes sure all targets (your code + gtest) agree on the runtime library
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

# -----------------------
# Fetch GoogleTest
# -----------------------
include(FetchContent)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE) # makes gtest use /MDd too
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        7917641ff965959afae189afb5f052524395525c
)
FetchContent_MakeAvailable(googletest)

# -----------------------
# Main executable
# -----------------------
add_executable(main
    src/main.cpp
    src/algo.cpp
    # any other source files needed for the main program
)

# -----------------------
# Test executable
# -----------------------

# Get all test files
file(GLOB TEST_SOURCES "test/*.cpp")

# Create test executable
add_executable(runTests
    ${SOURCES}
    ${TEST_SOURCES}
)

# Link GoogleTest library
target_link_libraries(runTests gtest_main)

# Enable CTest and register the test
enable_testing()
add_test(NAME all_tests COMMAND runTests)
