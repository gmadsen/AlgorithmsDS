//
// Created by garrett on 6/22/18.
//

#pragma once

#include <fstream>
#include <list>
#include <memory>
#include <vector>

namespace AlgorithmDS {
    class WeightedGraph {
    private:
        struct Vertex {
            int label;
            std::vector<std::pair<int, int>> adj_edges;
            bool explored;
        };  // class Vertex

    public:
        std::vector<std::unique_ptr<Vertex>> vertices;

        explicit WeightedGraph(std::ifstream &input);

        size_t size() const;

        const std::vector<std::unique_ptr<Vertex>> &get_vertices() const;

        void print() const;
    };
};