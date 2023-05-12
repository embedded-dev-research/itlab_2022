project(computer_vision)

include_directories(headers)

set(HDR1 ${CMAKE_CURRENT_SOURCE_DIR}/headers/Function.hpp)
set(SRC1 ${CMAKE_CURRENT_SOURCE_DIR}/sources/Function.cpp)
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

add_executable(computer_vision
        ${CMAKE_CURRENT_SOURCE_DIR}/app/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/headers/Structer.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/headers/data_render.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/headers/Color.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/headers/BMP.hpp)
target_link_libraries(computer_vision func_algo1)