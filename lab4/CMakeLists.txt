cmake_minimum_required(VERSION 3.20)
project(lab4)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 26)

add_executable(lab4 main.cpp BaseProblem.cpp SortByQ.cpp SortByR.cpp Permutations.cpp)
