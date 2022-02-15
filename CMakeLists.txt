cmake_minimum_required(VERSION 3.10)

# Project
project(libnnue VERSION 1.0 LANGUAGES CXX)

# Base directory relative includes
include_directories(src/)
include_directories(libs/catch2/)

# Flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wshadow")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -DNDEBUG")
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)

# Default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Add tests
add_executable(
    tests
    tests/main.cpp
    tests/xor.cpp
)

set_property(TARGET tests PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE FALSE)
