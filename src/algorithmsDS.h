//
// Created by garrett on 6/22/18.
//

#pragma once

#include <list>
#include "Graph.h"
#include "WeightedGraph.h"


namespace AlgorithmDS {

   int min_cut_contraction(std::__cxx11::list<std::pair<int, std::__cxx11::list<int>>> graph);
   int min_cut_contraction(const Graph &g);

// EFFECTS: explore all vertices in graph with Depth first search
    void dfs(const AlgorithmDS::Graph &g, int s, std::vector<bool> &explored);

// EFFECTS: create a directed graph with reversed order
    AlgorithmDS::Graph reverse_graph(const AlgorithmDS::Graph &g);

// EFFECTS: create a directed graph with new indices
    AlgorithmDS::Graph update_labels(const AlgorithmDS::Graph &g, const std::vector<int> &order);

// EFFECTS: calculate finishing times using kosarjus
    std::vector<int> topological_sort(const AlgorithmDS::Graph &g);

// EFFECTS: return a vector of SCC sizes
    std::vector<int> kosaraju(const AlgorithmDS::Graph &g);

// EFFECTS: return a vector of shortest paths from s to all Dijkstra's
    std::vector<int> dijkstra(WeightedGraph &wg, int s);
}