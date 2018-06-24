//
// Created by garrett on 6/19/18.
//

#include "Graph.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <set>

using namespace std;

namespace AlgorithmDS {

//////////////////////// helper functions//////////////////
    void add_edges_from_stream(ifstream &input, Graph &g);
////////////////////////////////////////////////////////////


/////////////// class Graph //////////////////////////
    Graph::Graph(adj_t::size_type size)
            : vertex_count(size), adjlist(size, list<int>()) {}

    Graph::Graph(adj_t::size_type size, ifstream &input)
            : vertex_count(size), adjlist(size, list<int>()) {
        add_edges_from_stream(input, *this);
    }

    const adj_t &Graph::get_adjacency_list() const { return adjlist; }

    adj_t::size_type Graph::size() const { return vertex_count; }

    void Graph::add_edge(int u, int v) { adjlist[u].push_back(v); }

// EFFECTS: print adjacency list for each vertex
    void Graph::print() const {
        for (auto i = adjlist.begin();
             i != adjlist.end(); ++i) {
            cout << "vertex " << distance(adjlist.begin(), i) << " is adjacent to: ";
            for (auto j = i->begin(); j != i->end(); ++j) {
                cout << *j << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
/////////////////////////////////////////////////////////////////////////
////////////////////  End of class Graph//////////////////////////////////////
/////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////
/////////////Overloads and Helpers////////////////////
//////////////////////////////////////////////////////

// EFFECTS: == override for class Graph
    bool operator==(const Graph &left, const Graph &right) {
        return (left.size() == right.size() &&
                left.get_adjacency_list() == right.get_adjacency_list());
    }

    void add_edges_from_stream(ifstream &input, Graph &g) {
        int u;
        int v;
        while (input >> u) {
            input >> v;
            g.add_edge(u, v);
        }
    }

}  // namespace AlgorithmDS