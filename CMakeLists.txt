CMAKE_MINIMUM_REQUIRED(VERSION 3.25.0)

project(computer_vision)

include_directories(./generating_data/headers ./algorithms/headers ./tests/headers ./benchmarks/headers)

set(HDR algorithms/headers/function.hpp)
set(SRC algorithms/sources/function.cpp)
add_library(func_algo ${HDR} ${SRC})

set(HDR1 benchmarks/headers/timer.hpp)
set(SRC1 benchmarks/sources/timer.cpp)
add_library(func_algo1 ${HDR1} ${SRC1})

find_package(OpenMP)
if(OpenMP_FOUND)
    message(STATUS "Link OpenMP")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
else()
    message(STATUS "Not link OpenMP")
endif()

add_executable(computer_vision main.cpp)
target_link_libraries(computer_vision func_algo)
target_link_libraries(computer_vision func_algo1)
