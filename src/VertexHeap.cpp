//
// Created by garrett on 6/22/18.
//

#include "VertexHeap.h"
#include <utility>
#include <iostream>
#include <algorithm>

using std::make_heap;
using std::cout;
using std::pair;

   bool vert_compare(pair<int, int> a, pair<int, int> b) {
        return (a.second > b.second);
    }
namespace AlgorithmDS {

    std::pair<int, int> VertexHeap::top() const { return heap[0]; }

    void VertexHeap::print() const {
        for (auto i : heap) {
            cout << "vertex " << i.first << " greedy score " << i.second << std::endl;
        }
    }

    void VertexHeap::push(std::pair<int, int> v) {
        heap.push_back(v);
        push_heap(heap.begin(), heap.end(), vert_compare);
    }

    void VertexHeap::pop() {
        pop_heap(heap.begin(), heap.end(), vert_compare);
        heap.pop_back();
    }

    void VertexHeap::remove(int vertex_value) {
        auto it =
                find_if(heap.begin(), heap.end(), [&vertex_value](const auto &vertex) {
                    return vertex.first == vertex_value;
                });
        if (it != heap.end()) {
            *it = heap.back();
            heap.pop_back();
            make_heap(heap.begin(), heap.end(), vert_compare);
        }
    }

    int VertexHeap::value_at(int vertex_value) const {
        auto it =
                find_if(heap.begin(), heap.end(), [&vertex_value](const auto &vertex) {
                    return vertex.first == vertex_value;
                });
        if (it != heap.end()) {
            return it->second;
        }
        return -1;
    }

    std::size_t VertexHeap::size() const { return heap.size(); }
}