#include "Queue.h"

template <typename T>
Queue<T>::Queue() : front(nullptr), rear(nullptr) {}

template <typename T>
Queue<T>::~Queue() {
    while (!isEmpty()) {
        dequeue();
    }
}

template <typename T>
void Queue<T>::enqueue(const T& data) {
    Node* newNode = new Node(data);
    if (isEmpty()) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}

template <typename T>
void Queue<T>::dequeue() {
    if (!isEmpty()) {
        Node* temp = front;
        front = front->next;
        delete temp;
        if (front == nullptr) {
            rear = nullptr; 
        }
    } else {
        std::cout << "Queue is empty. Cannot dequeue." << std::endl;
    }
}


template <typename T>
T Queue<T>::peek() const {
    if (!isEmpty()) {
        return front->data;
    } else {
        std::cout << "Queue is empty." << std::endl;
        return T();
    }
}

template <typename T>
bool Queue<T>::isEmpty() const {
    return front == nullptr;
}

