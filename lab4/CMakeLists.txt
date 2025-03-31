cmake_minimum_required(VERSION 3.20)
project(lab4)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 26)

add_executable(lab4 main.cpp BaseProblem.cpp SortByQ.cpp SortByR.cpp Permutations.cpp Schrage.cpp)
set_target_properties(lab4 PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tasks"
)


add_custom_command(TARGET lab4 POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy 
  "${CMAKE_SOURCE_DIR}/tasks/*" "${CMAKE_BINARY_DIR}/tasks"
)