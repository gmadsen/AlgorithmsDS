//
// Created by garrett on 6/21/18.
//

#include "gtest/gtest.h"
#include "algorithmsDS.h"
#include <list>
#include <vector>
#include <Graph.h>
#include <WeightedGraph.h>
#include <VertexHeap.h>
#include "algorithmsDS.h"


using namespace std;
using namespace AlgorithmDS;

// test add_edges
TEST(graph_test_add_edges, smallpos) {
Graph g;

g.add_edge(0,1);
g.add_edge(0,2);
g.add_edge(1,4);
g.add_edge(4,1);

adj_t expected(5,list<int> ());
expected[0].push_back(1);
expected[0].push_back(2);
expected[1].push_back(4);
expected[4].push_back(1);
//ASSERT_EQ(g.get_vertices(), expected);
}

// test add_edges from stream ctor
TEST(graph_test_fstream_ctor, small_graph) {
ifstream input("small_graph.txt");
Graph g(input);

adj_t expected(5,list<int> ());
expected[0].push_back(1);
expected[0].push_back(2);
expected[1].push_back(4);
expected[4].push_back(1);
//ASSERT_EQ(g.get_vertices(), expected);
}

// test DFS for complete exploration
TEST(graph_test_dfs, small_graph) {
ifstream input("small_graph.txt");
Graph g( input);
vector<bool> explored_array(5, false);
vector<bool> expected(5, true);
expected[3] = false;
dfs(g, 0, explored_array);
EXPECT_EQ(explored_array, expected);
}

// test reverse_graph_small
TEST(graph_test_reverse_graph, small) {
ifstream input("small_graph.txt");
Graph g(input);
Graph grev = reverse_graph(g);


adj_t expected(5,list<int> ());
expected[1].push_back(0);
expected[1].push_back(4);
expected[2].push_back(0);
expected[4].push_back(1);
//ASSERT_EQ(grev.get_vertices(), expected);
}

// test topological ordering
TEST(graph_test_topological_ordering, small) {
Graph g;
g.add_edge(1,0);
g.add_edge(1,4);
g.add_edge(2,0);
g.add_edge(2,3);
g.add_edge(4,2);

auto actual = topological_sort(g);
vector<int> expected(5,0);
expected[0] = 4;
expected[1] = 0;
expected[2] = 2;
expected[3] = 3;
expected[4] = 1;

EXPECT_EQ(actual, expected);
}

// test update graph labels small graph
TEST(graph_test_update_labels, small_graph) {
Graph g;
g.add_edge(1,0);
g.add_edge(1,4);
g.add_edge(2,0);
g.add_edge(2,3);
g.add_edge(4,2);
vector<int> order {4,0,2,3,1};

Graph g_actual = update_labels(g, order);

Graph g_expected;
g_expected.add_edge(0,4);
g_expected.add_edge(0,1);
g_expected.add_edge(1,2);
g_expected.add_edge(2,4);
g_expected.add_edge(2,3);
EXPECT_EQ(g_actual, g_expected);
}

TEST(graph_test_kosaraju, medium) {
ifstream input("medium_graph.txt");
Graph g(input);
vector<int> scc = kosaraju(g);
cout << endl;
}

TEST(graph_test_dijkstra, small_weighted_graph) {
ifstream file("small_weighted_graph.txt");
WeightedGraph wg(file);
auto a = dijkstra(wg,0);
vector<int> expected {0,5,6,7,7};
EXPECT_EQ(a, expected);
}

TEST(heap_test_class_VertexHeap, small) {
VertexHeap heap;
ifstream file("small_weighted_graph.txt");
WeightedGraph wg(file);

heap.push(make_pair<int,int>(0,0));
heap.push(make_pair<int,int>(1,5));
heap.push(make_pair<int,int>(2,6));
heap.push(make_pair<int,int>(3,7));
heap.push(make_pair<int,int>(4,7));
heap.remove(3);
}


