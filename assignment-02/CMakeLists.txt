cmake_minimum_required(VERSION 2.8)

project(useEigen)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_BUILD_TYPE "-03")

include_directories("/usr/include/eigen3")
add_executable(ex1 ex1.cpp)
add_executable(ex2 ex2.cpp)