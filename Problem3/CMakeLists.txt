cmake_minimum_required(VERSION 3.28)
project(Problem2)

set(CMAKE_CXX_STANDARD 26)

add_executable(Problem2 main.cpp)

target_sources(Problem2
        PRIVATE
        src/BaseProblem.cpp
        src/Zupelny.cpp
        src/NEH.cpp
        src/FNEH.cpp
        src/Jonson.cpp
        src/BandB.cpp
)

target_include_directories(Problem2
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/lib
)