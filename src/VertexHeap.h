//
// Created by garrett on 6/22/18.
//

#pragma once

#include <fstream>
#include <list>
#include <memory>
#include <vector>

namespace AlgorithmDS {
class VertexHeap {
private:
    typedef std::vector<std::pair<int, int>> heaplist;
    heaplist heap;

public:
    typedef std::vector<std::pair<int,int>>::iterator iterator;
    iterator begin() { return heap.begin(); }
    iterator end() { return heap.end(); }
    std::pair<int,int> top() const;

    void print() const;
    void push(std::pair<int,int> v);
    void pop();
    void remove(int vertex);
    int value_at(int vertex) const;
    size_t size() const;
};
}