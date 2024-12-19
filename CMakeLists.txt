cmake_minimum_required(VERSION 3.10)

#Project name and version 
project(MulticoreProcessorSimulation VERSION 1.0 LANGUAGES CXX)

#Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#Add the source files for the project 
set(SOURCES 
    src/cache.cpp
    src/memory.cpp
    src/processor.cpp
)
#Add the header files for the project 
set(HEADERS
    include/cache.h
    include/memory.h
    include/processor.h
)

#Create an executable 
add_executable(MulticoreSim ${SOURCES} main.cpp)

#Include directories for header files
target_include_directories(MulticoreSim PRIVATE include)

#optional : add compiler warnings 
target_compile_options(MulticoreSim PRIVATE -Wall -Wextra -pedantic)

#optional: Enable debug symbols for debuggin
set(CMAKE_BUILD_TYPE Debug)
