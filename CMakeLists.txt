cmake_minimum_required(VERSION 2.8)

#プロジェクト名と使用する言語を指定
project(ryosuke_numeric CXX)

add_executable(euler lead_e_euler.cpp)
add_executable(runge lead_e_runge.cpp)