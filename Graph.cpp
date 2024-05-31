#include "Graph.h"

template <typename T>
Graph<T>::Graph() {}

template <typename T>
Graph<T>::~Graph() {}

template <typename T>
void Graph<T>::addVertex(const T& data) {
    vertices.push_back(Vertex(data));
}

template <typename T>
void Graph<T>::addEdge(int from, int to) {
    if (from < 0 || from >= vertices.getSize() || to < 0 || to >= vertices.getSize()) {
        std::cerr << "Invalid vertex index" << std::endl;
        return;
    }
    vertices[from].edges.push_back(to);
    //vertices[to].edges.push_back(from);
}

template <typename T>
const Vector<typename Graph<T>::Vertex>& Graph<T>::getVertices() const {
    return vertices;
}

template <typename T>
void Graph<T>::printGraph() const {
    for (int i = 0; i < vertices.getSize(); ++i) {
        std::cout << "Vertex " << i << " (" << vertices[i].data << "): ";
        for (int j = 0; j < vertices[i].edges.getSize(); ++j) {
            std::cout << vertices[i].edges[j] << " ";
        }
        std::cout << std::endl;
    }
}


