cmake_minimum_required(VERSION 3.28)
project(lamp-of-god VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS  "-O2 -std=c++20 -Wall -Wextra -Wpedantic -Werror")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS src/*.hpp)

add_executable(main ${SOURCES})

target_compile_features(main PRIVATE cxx_std_20)
