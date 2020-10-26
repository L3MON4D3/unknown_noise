cmake_minimum_required(VERSION 3.13)
project(unknown_perlin CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(PkgConfig REQUIRED)

add_subdirectory(src)
