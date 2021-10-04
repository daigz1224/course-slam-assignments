cmake_minimum_required(VERSION 2.8)

project(HELLOSLAM)

set(CMAKE_BUILD_TYPE "Release")

INCLUDE_DIRECTORIES(include)

add_library(hello SHARED src/hello.cc)

add_executable(sayhello useHello.cc)

target_link_libraries(sayhello hello)

install(TARGETS hello LIBRARY DESTINATION lib)

install(FILES include/hello.h DESTINATION include)