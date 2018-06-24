//
// Created by garrett on 6/22/18.
//

#include "Graph.h"
#include "WeightedGraph.h"
#include <iostream>
#include <sstream>

using std::cout;
namespace AlgorithmDS {
    WeightedGraph::WeightedGraph(std::ifstream &input) {
        std::__cxx11::string line;
        while (getline(input, line)) {
            std::istringstream str_ss(line);
            vertices.push_back(std::make_unique<Vertex>());
            str_ss >> vertices.back()->label;
            --vertices.back()->label;
            vertices.back()->explored = false;
            int outvertex = 0;
            int weight = 0;
            while (str_ss >> outvertex) {
                str_ss.ignore(1, ',');
                str_ss >> weight;
                --outvertex;
                vertices.back()->adj_edges.emplace_back(std::make_pair(outvertex, weight));
            }
        }
    }

    std::size_t WeightedGraph::size() const { return vertices.size(); }

    void WeightedGraph::print() const {
        for (const auto &i : vertices) {
            cout << "vertex " << i->label << " has weighted edges ";
            for (const auto &j : i->adj_edges) {
                cout << j.first << "," << j.second << " ";
            }
            cout << std::endl;
        }
    }

    const std::vector<std::unique_ptr<WeightedGraph::Vertex>> &WeightedGraph::get_vertices()
    const {
        return vertices;
    }
}