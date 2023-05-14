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
option(WITH_OPENCV2 "Build with OpenCV" OFF)
if(WITH_OPENCV2)
    find_package(OpenCV REQUIRED)
    if(OpenCV_FOUND)
        message(STATUS "Link OpenCV")
        include_directories( ${OpenCV_INCLUDE_DIRS} )
        add_compile_definitions(WITH_OPENCV2)
        target_link_libraries(computer_vision ${OpenCV_LIBS})
    else()
        message(STATUS "Not link OpenCV")
    endif()
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