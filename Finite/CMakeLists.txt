cmake_minimum_required(VERSION 3.15)
project(Finite)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

add_executable(Finite main.cpp)