 include_directories(${/test/lib/googletest-master/googletest}/include ${/test/lib/googletest-master/googletest})
set(
        GRAPH_TEST_SOURCES
        ${CMAKE_SOURCE_DIR}/src/Graph.cpp
        ${CMAKE_SOURCE_DIR}/src/mult_algorithm.cpp
        ${CMAKE_SOURCE_DIR}/src/WeightedGraph.cpp
        ${CMAKE_SOURCE_DIR}/src/algorithmsDS.cpp
        ${CMAKE_SOURCE_DIR}/src/VertexHeap.cpp

)
add_executable(runAllTests
        basic_test.cpp graph_test.cpp ${GRAPH_TEST_SOURCES} mult_algorithm_test.cpp)

target_link_libraries(runAllTests gtest gtest_main )
