cmake_minimum_required(VERSION 3.10)
project(TapeSort)

set(CMAKE_CXX_STANDARD 17)
include_directories(inc)

add_executable(TapeSort 
    src/main.cpp
    src/Tape.cpp
    src/TapeDelaysConfig.cpp
    src/TapeSorter
)