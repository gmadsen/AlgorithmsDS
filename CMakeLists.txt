cmake_minimum_required(VERSION 3.10)
project(AlgorithmsDS)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_subdirectory(test)

add_library(AlgorithmsDS SHARED src/Graph.cpp src/Graph.h src/mult_algorithm.h src/mult_algorithm.cpp)
