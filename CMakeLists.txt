CMAKE_MINIMUM_REQUIRED(VERSION 3.25.0)

project(computer_vision)

include_directories(./headers)

set(HRD headers/BMP.hpp)
set(SRC sources/BMP.cpp)

add_library(func_algo ${HDR} ${SRC})

find_package(OpenMP)
if(OpenMP_FOUND)
    message(STATUS "Link OpenMP")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
else()
    message(STATUS "Not link OpenMP")
endif()

add_executable(computer_vision main.cpp ./headers/Structer.hpp ./headers/data_render.hpp ./headers/Color.hpp ./headers/BMP.hpp)
target_link_libraries(computer_vision func_algo)