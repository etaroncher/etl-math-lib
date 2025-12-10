# MathLib/CMakeLists.txt

cmake_minimum_required(VERSION 4.2.0)
project(MathLib VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

# Include dirs
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/private)

# Add the src directory (it defines the sources)
add_subdirectory(src)

# Option to enable/disable tests (useful for when library is used as subproject)
option(MATHLIB_BUILD_TESTS "Build MathLib tests" ON)

# Enable test and add test directory
if(MATHLIB_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
