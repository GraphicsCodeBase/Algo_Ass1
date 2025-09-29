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
# Your library
# -----------------------
add_library(algo
    src/algo.cpp
    src/algo.hpp
)

# -----------------------
# Main executable
# -----------------------
add_executable(main
    src/main.cpp
    src/algo.cpp
    # any other source files needed for the main program
)
target_link_libraries(main PRIVATE algo gtest_main)


# Enable testing and discover tests
include(GoogleTest)
enable_testing()
gtest_discover_tests(main PROPERTIES TIMEOUT 10)
