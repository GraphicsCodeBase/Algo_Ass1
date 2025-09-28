cmake_minimum_required(VERSION 3.14)
project(Assignment1)

set(CMAKE_CXX_STANDARD 17)

# -----------------------
# Force MSVC runtime to /MD or /MDd
# -----------------------
# This makes sure all targets (your code + gtest) agree on the runtime library
if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
endif()

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
    src/bucket_sort.cpp
    src/bucket_sort.hpp
    src/transport.cpp
    src/transport.cpp)

# -----------------------
# Main executable
# -----------------------
add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE algo)

# -----------------------
# Test executable
# -----------------------

add_executable(runTests
    ${SOURCES}
    test/test.cpp
    test/bucket_sort_test.cpp)
target_link_libraries(runTests PRIVATE gtest_main gtest algo) # Link GoogleTest library

 add_executable(transportTests 
    test/transport_test.cpp
    src/transport.cpp
    src/transport.hpp)
target_link_libraries(transportTests PRIVATE gtest_main gtest algo)


# Enable testing and discover tests
include(GoogleTest)
enable_testing()
gtest_discover_tests(runTests PROPERTIES TIMEOUT 10)
gtest_discover_tests(transportTests PROPERTIES TIMEOUT 10)
