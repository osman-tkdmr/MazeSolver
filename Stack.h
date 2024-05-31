#ifndef STACK_H
#define STACK_H
#include <iostream>

template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& data, Node* next = nullptr) : data(data), next(next) {}
    };

    Node* top;
    int count;

public:
    Stack();
    ~Stack();
    void push(const T& element);
    T pop();
    T peek() const;
    bool isEmpty() const;
    int size() const;
};

#include "Stack.cpp"

#endif // STACK_H

