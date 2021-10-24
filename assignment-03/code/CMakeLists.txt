cmake_minimum_required(VERSION 2.8)

project(DrawTrajectory)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_BUILD_TYPE "-03")

include_directories("/usr/include")
include_directories("/usr/local/include")
include_directories("/usr/include/eigen3")

add_executable(draw_trajectory draw_trajectory.cpp)
target_link_libraries(draw_trajectory pangolin GL)
