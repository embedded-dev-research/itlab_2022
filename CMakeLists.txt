CMAKE_MINIMUM_REQUIRED(VERSION 3.25.0)

# build 3rdparty gtest
include(cmake/gtest.cmake)

add_subdirectory(algo)
add_subdirectory(tests)
