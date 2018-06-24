//
// Created by garrett on 6/19/18.
//

#pragma once

#include <fstream>
#include <list>
#include <memory>
#include <utility>
#include <vector>

namespace AlgorithmDS {
    typedef std::vector<std::list<int>> adj_t;
    class Graph {
    private:
        adj_t::size_type vertex_count;
        adj_t adjlist;

    public:
        // ctor with size
        explicit Graph(adj_t::size_type size);
        // ctor with std::ifstream
        Graph(adj_t::size_type size, std::ifstream &input);

        // EFFECTS: the total number of vertices
        adj_t::size_type size() const;

        // EFFECTS: print adjacency for each vertex
        void print() const;

        // EFFECTS: get adjacency list
        const adj_t &get_adjacency_list() const;

        // EFFECTS: add edge to graph
        void add_edge(int u, int v);
    };  // class Graph

    // class WeightedGraph

    // class VertexHeap


// == overload for class Graph
    bool operator==(const Graph &left, const Graph &right);

}  // namespace AlgorithmDS




