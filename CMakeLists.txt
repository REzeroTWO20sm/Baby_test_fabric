cmake_minimum_required(VERSION 3.20)
project(BABY_TEST)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(BABY_TEST main.cpp baby_test.cpp)