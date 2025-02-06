cmake_minimum_required(VERSION 3.10)

#Project name and version 
project(MulticoreProcessorSimulation VERSION 1.0 LANGUAGES CXX)

#Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#Add the source files for the project 
set(SOURCES 
    src/cache.cpp
    src/processor.cpp
    src/node.cpp
    src/core.cpp
    src/cpu.cpp
)
#Add the header files for the project 
set(HEADERS
    include/cache.h
    include/processor.h
    include/node.h
    include/easylogging++.h
    include INSTRUCTION_ENUM.h
    include/core.h
    include/cpu.h
    include/memStack.h
    include/instructionQueue.h
)


#make logging thread safe
add_definitions(-DELPP_THREAD_SAFE)  # Enable thread safety if needed
add_definitions(-DELPP_NO_DEFAULT_LOG_FILE) 


#Create an executable 
add_executable(MulticoreProcessorSimulation ${SOURCES} src/main.cpp lib/easylogging++.cc)

#Include directories for header files
add_subdirectory(extern/easyloggingpp)
target_include_directories(MulticoreProcessorSimulation PRIVATE include)

#optional: Enable debug symbols for debuggin
set(CMAKE_BUILD_TYPE Debug)
