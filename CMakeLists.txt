cmake_minimum_required(VERSION 3.13)
project(unknown_noise CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(Cairomm REQUIRED IMPORTED_TARGET cairomm-1.0)

add_subdirectory(libs/FastNoise)

add_subdirectory(src)
