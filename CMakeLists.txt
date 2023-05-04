CMAKE_MINIMUM_REQUIRED(VERSION 3.25.0)

project(computer_vision)

include_directories(./generating_data/headers)
include_directories(./algorithms/headers)
include_directories(./tests/headers)
include_directories(./benchmarks/headers)

set(ALGORITHMS_HDR algorithms/headers/function.hpp)
set(ALGORITHMS_SRC algorithms/sources/function.cpp)
add_library(func_algo ${ALGORITHMS_HDR} ${ALGORITHMS_SRC})

set(TIMER_HDR benchmarks/headers/timer.hpp)
set(TIMER_SRC benchmarks/sources/timer.cpp)
add_library(func_timer ${TIMER_HDR} ${TIMER_SRC})

add_executable(computer_vision main.cpp)

#Link OpenMP
find_package(OpenMP)
if(OpenMP_FOUND)
    message(STATUS "Link OpenMP")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
else()
    message(STATUS "Not link OpenMP")
endif()

# Link OpenCV
find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
    message(STATUS "Link OpenCV")
    include_directories( ${OpenCV_INCLUDE_DIRS} )
    add_compile_definitions(WITH_OPENCV2)
    target_link_libraries(computer_vision ${OpenCV_LIBS})
else()
    message(STATUS "Not link OpenCV")
endif()

target_link_libraries(computer_vision func_algo)
target_link_libraries(computer_vision func_timer)

