#include "Stack.h"

template <typename T>
Stack<T>::Stack() : top(nullptr), count(0) {}

template <typename T>
Stack<T>::~Stack() {
    while (!isEmpty()) {
        pop();
    }
}

template <typename T>
void Stack<T>::push(const T& element) {
    Node* newNode = new Node(element, top);
    top = newNode;
    count++;
}

template <typename T>
T Stack<T>::pop() {
    if (isEmpty()) {
        std::cout << "Stack is empty. Cannot pop." << std::endl;
        return T();
    } else {
        Node* tempNode = top;
        T topElement = top->data;
        top = top->next;
        delete tempNode;
        count--;
        return topElement;
    }
}

template <typename T>
T Stack<T>::peek() const {
    if (isEmpty()) {
        std::cout << "Stack is empty." << std::endl;
        return T();
    } else {
        return top->data;
    }
}

template <typename T>
bool Stack<T>::isEmpty() const {
    return top == nullptr;
}

template <typename T>
int Stack<T>::size() const {
    return count;
}

