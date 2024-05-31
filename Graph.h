#ifndef GRAPH_H
#define GRAPH_H
#include "Vector.h"
#include <iostream>

template <typename T>
class Graph {
private:
    struct Vertex {
        T data;
        Vector<int> edges;
        Vertex() = default;
        Vertex(const T& data) : data(data) {}
    };

    Vector<Vertex> vertices;

public:
    Graph();
    ~Graph();
    void addVertex(const T& data);
    void addEdge(int from, int to);
    void printGraph() const;
    const Vector<Vertex>& getVertices() const;
};

#include "Graph.cpp"

#endif // GRAPH_H

