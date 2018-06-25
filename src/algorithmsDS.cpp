//
// Created by garrett on 6/22/18.
//

#include <list>
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
typedef std::list<std::pair<int, std::list<int>>> graph_t;

void single_random_cut(Graph &g) {
    int n = 1;
}

// EFFECTS: perform a single random cut and update graph
// MODIFIES: input graph
void single_random_cut(graph_t &graph) {
    // new element
    int n = graph.back().first;

    // choose edge  by choosing an adjacency randomly
    // srand(time(NULL));
    // find appropriate iterators pointing to head
    int head_idx = rand() % graph.size();
    auto head_iter = graph.begin();
    advance(head_iter, head_idx);
    int head_val = head_iter->first;

    // find iterator for tail side
    int tail_idx = rand() % head_iter->second.size();
    auto tail_iter = head_iter->second.begin();
    std::advance(tail_iter, tail_idx);
    int tail_val = *tail_iter;

    // cout << "head value is: " << head_val << endl;
    // cout << "tail value is: " << tail_val << endl;

    std::__cxx11::list<int> new_edges;

    // find head vertices corresponding to edge choice
    auto it = std::find_if(graph.begin(), graph.end(),
                           [&](const std::pair<int, std::__cxx11::list<int>> &element) {
                               return element.first == tail_val;
                           });
    const auto &head_verts = head_iter->second;
    const auto &tail_verts = it->second;

    // add all non tail/head edges to new list
    for (const auto &i : head_verts) {
        if (i != head_val && i != tail_val) {
            new_edges.push_back(i);
        }
    }
    for (const auto &i : tail_verts) {
        if (i != tail_val && i != head_val) {
            new_edges.push_back(i);
        }
    }

    // remove tail and head vertices from list
    graph.erase(it);
    graph.erase(head_iter);

    // update all other vertices
    graph.push_back(make_pair(n + 1, new_edges));
    for (auto &i : graph) {
        auto &ad_list = i.second;
        std::replace_if(
                ad_list.begin(), ad_list.end(),
                [&](int element) { return element == head_val || element == tail_val; },
                n + 1);
    }
}

void graph_print(const graph_t &graph) {
    // print
    for (auto i : graph) {
        std::cout << "vertex " << i.first << " has edges: ";
        for (auto j : i.second) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
}

// find minimum cut based on repeated randomized contraction algorithm
int min_cut_contraction(std::__cxx11::list<std::pair<int, std::__cxx11::list<int>>> graph) {
    while (graph.size() > 2) {
        single_random_cut(graph);
    }
    int min_cut = graph.front().second.size();
    return min_cut;
}

int min_cut_contraction(const Graph &g) {
    return 5;
}
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
        const auto &vertices = g.get_vertices();
        for (const auto &edge : vertices[s]->adj_edges) {
            if (!explored_array[edge.first]) {
                dfs(g, edge.first, explored_array);
            }
        }
    }

// EFFECTS: create a directed graph with reversed order
    AlgorithmDS::Graph reverse_graph(const AlgorithmDS::Graph &g) {
        AlgorithmDS::Graph grev;
        const auto &original_vertices = g.get_vertices();
        // std::vector::const_iterator i;
        for (auto i = original_vertices.begin();
             i != original_vertices.end(); ++i) {
            for (auto j = (*i)->adj_edges.begin(); j != (*i)->adj_edges.end(); ++j) {
                grev.add_edge(j->first, std::distance(original_vertices.cbegin(), i));
            }
        }
        return grev;
    }

// EFFECTS: create a directed graph with new indices
    AlgorithmDS::Graph update_labels(const AlgorithmDS::Graph &g, const std::vector<int> &new_order) {
        AlgorithmDS::Graph g_update;
        const auto &original_vertices = g.get_vertices();
        for (auto i = original_vertices.begin();
             i != original_vertices.end(); ++i) {
            auto dist = std::distance(original_vertices.cbegin(), i);
            for (auto j : (*i)->adj_edges) {
                g_update.add_edge(new_order[dist], new_order[j.first]);
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
        const auto &vertices = g.get_vertices();
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
         const auto &vertices = g.get_vertices();
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
        const auto &vertices = g.get_vertices();
        for (const auto &edge : vertices[s]->adj_edges) {
            if (!explored_array[edge.first]) {
                kosaraju_dfs(g, edge.first, explored_array, ordering, finish_count, leaders, l);
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
        const auto &vertices = g.get_vertices();
        for (const auto &edge : vertices[s]->adj_edges) {
            if (!explored_array[edge.first]) {
                dfs_sort(g, edge.first, explored_array, ordering, label);
            }
        }
        ordering[s] = label;
        --label;
    }
}