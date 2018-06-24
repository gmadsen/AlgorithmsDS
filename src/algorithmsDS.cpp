//
// Created by garrett on 6/22/18.
//

#include <set>
#include <map>
#include <algorithm>
#include "algorithmsDS.h"
#include "Graph.h"
#include "WeightedGraph.h"
#include "VertexHeap.h"
#include <iostream>
#include <sstream>
#include <limits>


using std::numeric_limits;

namespace AlgorithmDS {
    //////////////////////////////Helper function declarations////////////////////////////////////////////
    void kosaraju_dfs_loop(const AlgorithmDS::Graph &g, std::vector<int> &ordering,
                           std::map<int, int> &leaders);

    void kosaraju_dfs(const AlgorithmDS::Graph &g, int s, std::vector<bool> &explored_array,
                      std::vector<int> &ordering, int &finish_count,
                      std::map<int, int> &leaders, int l);

    void dfs_sort(const AlgorithmDS::Graph &g, int s, std::vector<bool> &explored_array,
                  std::vector<int> &ordering, int &label);
/////////////////////////////////////////////////////////////////////////////////////////////////////////


// EFFECTS: explore all vertices in graph with Depth first search
// MODIFIES: explored array
// REQUIRES: assumes initial call has an explored array of all false
    void dfs(const AlgorithmDS::Graph &g, int s, std::vector<bool> &explored_array) {
        explored_array[s] = true;
        // cout << "s is : " << s << endl;
        auto &adj_list = g.get_adjacency_list();
        for (const auto &edge : adj_list[s]) {
            if (!explored_array[edge]) {
                dfs(g, edge, explored_array);
            }
        }
    }

// EFFECTS: create a directed graph with reversed order
    AlgorithmDS::Graph reverse_graph(const AlgorithmDS::Graph &g) {
        AlgorithmDS::Graph grev(g.size());
        const auto &orig_adj_list = g.get_adjacency_list();
        // std::vector::const_iterator i;
        for (auto i = orig_adj_list.begin();
             i != orig_adj_list.end(); ++i) {
            for (auto j = i->begin(); j != i->end(); ++j) {
                grev.add_edge(*j, distance(orig_adj_list.cbegin(), i));
            }
        }
        return grev;
    }

// EFFECTS: create a directed graph with new indices
    AlgorithmDS::Graph update_labels(const AlgorithmDS::Graph &g, const std::vector<int> &new_order) {
        AlgorithmDS::Graph g_update(g.size());
        const auto &orig_adj_list = g.get_adjacency_list();
        for (auto i = orig_adj_list.begin();
             i != orig_adj_list.end(); ++i) {
            auto dist = distance(orig_adj_list.cbegin(), i);
            for (int j : *i) {
                g_update.add_edge(new_order[dist], new_order[j]);
            }
        }
        return g_update;
    }

// EFFECTS: calculate finishing times using kosarjus
    std::vector<int> topological_sort(const AlgorithmDS::Graph &g) {
        int size = g.size();
        std::vector<int> ordering(size, 0);
        std::vector<bool> explored(size, false);
        int current_label = size - 1;
        const auto &vertices = g.get_adjacency_list();
        for (auto i = vertices.cbegin(); i != vertices.cend(); ++i) {
            auto dist = distance(vertices.cbegin(), i);
            if (!explored[dist]) {
                dfs_sort(g, dist, explored, ordering, current_label);
            }
        }
        return ordering;
    }

    std::vector<int> kosaraju(const AlgorithmDS::Graph &g) {
        int size = g.size();
        std::vector<int> ordering(size, 0);
        std::map<int, int> leaders;

        kosaraju_dfs_loop(reverse_graph(g), ordering, leaders);
        leaders.clear();
        kosaraju_dfs_loop(update_labels(g, ordering), ordering, leaders);

        std::vector<int> scc_sizes;
        scc_sizes.reserve(leaders.size());
        for (auto i : leaders) {
            scc_sizes.push_back(i.second);
        }
        sort(scc_sizes.begin(), scc_sizes.end(), std::greater<>());
        int split_size = scc_sizes.size();
        std::vector<int> five_scc(scc_sizes.begin(),
                                  scc_sizes.begin() + (split_size < 5 ? split_size : 5));
        return five_scc;
    }
    
    std::vector<int> dijkstra(WeightedGraph &wg, int s) {
        /////// initialize
        VertexHeap heap;
        int size = wg.size();
        const auto &pvertices = wg.get_vertices();

        // set all distances to inf
        std::vector<int> distance(size, numeric_limits<int>::max());
        // fill untouched with all vertices
        // make heap
        for (const auto &i : pvertices) {
            heap.push(std::make_pair(i->label, numeric_limits<int>::max()));
        }
        // add s to touched
        distance[s] = 0;
        pvertices[s]->explored = true;
        heap.remove(s);
        for (const auto &i : pvertices[s]->adj_edges) {
            heap.remove(i.first);
            int greedy_score = distance[s] + i.second;
            heap.push(std::make_pair(i.first, greedy_score));
        }

        while (heap.size() > 0) {
            std::pair<int, int> p(heap.top());
            distance[p.first] = p.second;
            heap.remove(p.first);
            pvertices[p.first]->explored = true;
            for (const auto &i : pvertices[p.first]->adj_edges) {
                if (!pvertices[i.first]->explored) {
                    int greedy_score = distance[p.first] + i.second;
                    int current_value = heap.value_at(i.first);
                    if (current_value > greedy_score) {
                        heap.remove(i.first);
                        heap.push(std::make_pair(i.first, greedy_score));
                    }
                }
            }
        }

        return distance;
    }

// EFFECTS: calculate finishing times using kosarjus
    void kosaraju_dfs_loop(const AlgorithmDS::Graph &g, std::vector<int> &ordering,
                           std::map<int, int> &leaders) {
        std::vector<bool> explored(g.size(), false);

        int t = -1;
        // global leader
        int s = 0;
        const auto &vertices = g.get_adjacency_list();
        for (auto i = vertices.crbegin(); i != vertices.crend(); ++i) {
            auto dist = distance(vertices.cbegin(), i.base()) - 1;
            if (!explored[dist]) {
                s = dist;
                kosaraju_dfs(g, dist, explored, ordering, t, leaders, s);
            }
        }
    }

// REQUIRES: assumes initial call has an explored array of all false
    void kosaraju_dfs(const AlgorithmDS::Graph &g, int s, std::vector<bool> &explored_array,
                      std::vector<int> &ordering, int &finish_count,
                      std::map<int, int> &leaders, int l) {
        explored_array[s] = true;
        leaders[l] += 1;
        auto &adj_list = g.get_adjacency_list();
        for (const auto &edge : adj_list[s]) {
            if (!explored_array[edge]) {
                kosaraju_dfs(g, edge, explored_array, ordering, finish_count, leaders, l);
            }
        }
        ++finish_count;
        ordering[s] = finish_count;
    }

// EFFECTS: explore all vertices in graph with Depth first search
// MODIFIES: explored array
// REQUIRES: assumes initial call has an explored array of all false
    void dfs_sort(const AlgorithmDS::Graph &g, int s, std::vector<bool> &explored_array,
                  std::vector<int> &ordering, int &label) {
        explored_array[s] = true;
        auto &adj_list = g.get_adjacency_list();
        for (const auto &edge : adj_list[s]) {
            if (!explored_array[edge]) {
                dfs_sort(g, edge, explored_array, ordering, label);
            }
        }
        ordering[s] = label;
        --label;
    }
}