//
// Created by garrett on 6/19/18.
//

#include "Graph.h"
#include <algorithm>
#include <iostream>
#include <memory>
#include <map>
#include <set>
#include <boost/iterator/zip_iterator.hpp>
#include <boost/range/iterator_range.hpp>

using namespace std;

namespace AlgorithmDS {

//////////////////////// helper functions//////////////////
    void add_edges_from_stream(ifstream &input, Graph &g);
////////////////////////////////////////////////////////////


/////////////// class Graph //////////////////////////
    Graph::Graph() {}

    Graph::Graph(ifstream &input) {
        add_edges_from_stream(input, *this);
    }

    const std::vector<std::unique_ptr<Graph::Vertex>> &Graph::get_vertices() const { return vertices; }

    size_t Graph::size() const { return vertices.size(); }

    void Graph::add_edge(int u, int v) {
        size_t size = this->size();
        while (size < u + 1) {
            vertices.emplace_back(std::make_unique<Vertex>());
            ++size;
        }
        vertices[u]->adj_edges.emplace_back(make_pair(v, 1));
    }

// EFFECTS: print adjacency list for each vertex
    void Graph::print() const {
        for (auto i = vertices.begin();
             i != vertices.end(); ++i) {
            cout << "vertex " << distance(vertices.begin(), i) << " is adjacent to: ";
            for (auto j = (*i)->adj_edges.begin(); j != (*i)->adj_edges.end(); ++j) {
                cout << (*j).first << " ";
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
    template<class... Conts>
    auto zip_range(Conts &... conts)
    -> decltype(boost::make_iterator_range(
            boost::make_zip_iterator(boost::make_tuple(conts.begin()...)),
            boost::make_zip_iterator(boost::make_tuple(conts.end()...)))) {
        return {boost::make_zip_iterator(boost::make_tuple(conts.begin()...)),
                boost::make_zip_iterator(boost::make_tuple(conts.end()...))};
    }

// ...

// EFFECTS: == override for class Graph
    bool operator==(const Graph &left, const Graph &right) {
        const auto &lhs = left.get_vertices();
        const auto &rhs = right.get_vertices();
        if (left.size() != right.size()) return false;
        for (auto &&t : zip_range(lhs, rhs)) {
            if (t.get<0>()->adj_edges != t.get<1>()->adj_edges) return false;

        }
        return true;
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