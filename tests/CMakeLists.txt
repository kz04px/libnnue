cmake_minimum_required(VERSION 3.12)

# Base directory relative includes
include_directories($(CMAKE_CURRENT_SOURCE_DIR)/../libs/catch2/)

# Flags
set(CMAKE_CXX_STANDARD 20)
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
    main.cpp
    xor.cpp
)

target_link_libraries(
    tests
    nnue
)

set_property(TARGET tests PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE FALSE)
