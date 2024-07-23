cmake_minimum_required(VERSION 3.20)
set(CMAKE_GENERATOR "Ninja")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "Generate compile commands")
project("Leetcode")

# Clang
set(CMAKE_C_COMPILER /opt/homebrew/opt/llvm/bin/clang)
set(CMAKE_CXX_COMPILER /opt/homebrew/opt/llvm/bin/clang++)


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_C_STANDARD 18)
set(CMAKE_C_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "Generate compile commands")

# Find all files in TechInterviewHandbook (TIHandbook) folder
file(GLOB_RECURSE TIHandbook TIHandbook/*.cpp TIHandbook/**/*.cpp) 

# print TIHandbook files
message(STATUS "TIHandbook files: ${TIHandbook}")
add_executable(leetcode leetcode.cpp ${TIHandbook})


