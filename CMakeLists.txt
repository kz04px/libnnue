cmake_minimum_required(VERSION 3.12)

project(
    libnnue
    VERSION 1.0
    DESCRIPTION "A C++ NNUE library"
    LANGUAGES CXX
)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_library(nnue INTERFACE)

target_include_directories(nnue INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src/)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    option(LIBATAXX_BUILD_TESTS "whether or not tests should be built" ON)

    if(LIBATAXX_BUILD_TESTS)
        enable_testing()
        add_subdirectory(tests)
    endif()
endif()
