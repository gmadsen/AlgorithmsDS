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
        struct Vertex {
            int label;
            std::vector<std::pair<int,int>> adj_edges;
            bool explored;
        };
        std::vector<std::unique_ptr<Vertex>> vertices;
    public:
        // ctor with size
        explicit Graph();
        // ctor with std::ifstream
        Graph(std::ifstream &input);

        // EFFECTS: the total number of vertices
        size_t size() const;

        // EFFECTS: print adjacency for each vertex
        void print() const;

        // EFFECTS: add edge to graph
        void add_edge(int u, int v);

        const std::vector<std::unique_ptr<Vertex>> & get_vertices() const;

    };  // class Graph

// == overload for class Graph
    bool operator==(const Graph &left, const Graph &right);

}  // namespace AlgorithmDS




