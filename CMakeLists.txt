cmake_minimum_required(VERSION 3.10)
project(TapeSort LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../)

add_executable(TapeSort 
    src/main.cpp
    src/Tape.cpp
    src/TapeConfig.cpp
    src/TapeSorter.cpp
)
target_include_directories(TapeSort PUBLIC interfaces/ inc/)