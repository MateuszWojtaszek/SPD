cmake_minimum_required(VERSION 3.20)
project(lab4)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 26)
# Add the lib folder to the include directories
include_directories(${CMAKE_SOURCE_DIR}/lib)

# Add the lib folder to the linker search paths
link_directories(${CMAKE_SOURCE_DIR}/lib)
add_executable(lab4 main.cpp src/BaseProblem.cpp src/SortByQ.cpp src/SortByR.cpp src/Permutations.cpp src/Schrage.cpp src/SchrageDiv.cpp
        lib/SortByRq.h
        src/SortByRq.cpp)
set_target_properties(lab4 PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tasks"
)


add_custom_command(TARGET lab4 POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy 
  "${CMAKE_SOURCE_DIR}/tasks/*" "${CMAKE_BINARY_DIR}/tasks"
)