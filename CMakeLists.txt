cmake_minimum_required(VERSION 3.10)
project(AlgorithmsDS)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

set(BOOST_ROOT /usr/local/boost_1_66_0)
#set(Boost_LIBRARY_DIR /usr/local/boost_1_67_0/libs)
find_package(Boost 1.66 COMPONENTS ) #system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_subdirectory(test)

add_library(AlgorithmsDS
        SHARED
        src/Graph.cpp
        src/Graph.h
        src/mult_algorithm.h
        src/mult_algorithm.cpp
        src/algorithmsDS.cpp
        src/algorithmsDS.h
        src/WeightedGraph.cpp
        src/WeightedGraph.h
        src/VertexHeap.cpp
        src/VertexHeap.h)

target_link_libraries(AlgorithmsDS ${Boost_LIBRARIES})
