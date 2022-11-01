cmake_minimum_required(VERSION 3.8)

#プロジェクト名と使用する言語を指定
project(ryosuke_numeric CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_executable(euler lead_e_euler.cpp)
add_executable(runge lead_e_runge.cpp)

add_subdirectory("./src")