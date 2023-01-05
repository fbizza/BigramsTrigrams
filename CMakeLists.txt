cmake_minimum_required(VERSION 3.21)
project(BigramsTrigrams)


# added -fopenmp
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")

set(SOURCE_FILES main.cpp Sequential.cpp Sequential.h)
add_executable(BigramsTrigrams ${SOURCE_FILES})

