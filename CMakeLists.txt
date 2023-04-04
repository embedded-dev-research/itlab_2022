CMAKE_MINIMUM_REQUIRED(VERSION 3.25.0)

set(CMAKE_CXX_COMPILER "C:/MinGW/bin/g++.exe")
set(CMAKE_C_COMPILER "C:/MinGW/bin/gcc.exe")

project(computer_vision)

include_directories(./headers)

find_package(OpenMP)
if(OpenMP_FOUND)
    message(STATUS "Link OpenMP")
else()
    message(STATUS "Not link OpenMP")
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")

add_executable(computer_vision main.cpp ./headers/Structer.hpp ./headers/data_render.hpp ./headers/Color.hpp )
