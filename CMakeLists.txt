cmake_minimum_required(VERSION 3.10)
project(ranges_task)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

set(BINARY_NAME ${PROJECT_NAME})

add_executable(${BINARY_NAME} src/main.cpp)

enable_testing()
add_subdirectory(test)
