#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& data, Node* next = nullptr) : data(data), next(next) {}
    };

    Node* front;
    Node* rear;

public:
    Queue();
    ~Queue();
    void enqueue(const T& data);
    void dequeue();
    T peek() const;
    bool isEmpty() const;
};

#include "Queue.cpp" 

#endif // QUEUE_H

