#include "Vector.h"

template <class T>
Vector<T>::Vector() : array(nullptr), capacity(0), size(0) {}

template <class T>
Vector<T>::Vector(int initialCapacity) : array(new T[initialCapacity]), capacity(initialCapacity), size(0) {}

template <class T>
Vector<T>::Vector(int initialSize, const T& value) : array(new T[initialSize]), capacity(initialSize), size(initialSize) {
    for (int i = 0; i < initialSize; ++i) {
        array[i] = value;
    }
}

template <class T>
Vector<T>::Vector(const Vector<T>& other) : array(new T[other.capacity]), capacity(other.capacity), size(other.size) {
    for (int i = 0; i < size; ++i) {
        array[i] = other.array[i];
    }
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
    if (this != &other) {
        delete[] array;

        array = new T[other.capacity];
        capacity = other.capacity;
        size = other.size;

        for (int i = 0; i < size; ++i) {
            array[i] = other.array[i];
        }
    }
    return *this;
}

template <class T>
Vector<T>::~Vector() {
    delete[] array;
}

template <class T>
void Vector<T>::push_back(T data) {
    if (size == capacity) {
        reserve((capacity == 0) ? 1 : capacity * 2);
    }
    array[size++] = data;
}

template <class T>
void Vector<T>::pop_back() {
    if (size > 0) {
        --size;
    } else {
        std::cerr << "Vector is empty" << std::endl;
    }
}

template <class T>
T& Vector<T>::operator[](int index) {
    if (index < 0 || index >= size) {
        std::cerr << "Index out of range" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    return array[index];
}

template <class T>
const T& Vector<T>::operator[](int index) const {
    if (index < 0 || index >= size) {
        std::cerr << "Index out of range" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    return array[index];
}

template <class T>
int Vector<T>::getSize() const {
    return size;
}

template <class T>
bool Vector<T>::empty() const {
    return size == 0;
}

template <class T>
void Vector<T>::resize(int newSize, const T& value) {
    if (newSize > capacity) {
        reserve(newSize);
    }
    for (int i = size; i < newSize; ++i) {
        array[i] = value;
    }
    size = newSize;
}

template <class T>
void Vector<T>::reserve(int newCapacity) {
    if (newCapacity > capacity) {
        allocateAndCopy(newCapacity);
    }
}

template <class T>
void Vector<T>::allocateAndCopy(int newCapacity) {
    T* newArray = new T[newCapacity];
    for (int i = 0; i < size; ++i) {
        newArray[i] = array[i];
    }
    delete[] array;
    array = newArray;
    capacity = newCapacity;
}

template <class T>
void Vector<T>::clear() {
  for (int i = 0; i < size; ++i) {
    array[i].~T();
  }

  size = 0;
}

template <class T>
T& Vector<T>::back() {
    if (size == 0) {
        std::cerr << "Vector is empty" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    return array[size - 1];
}

template <class T>
const T& Vector<T>::back() const {
    if (size == 0) {
        std::cerr << "Vector is empty" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    return array[size - 1];
}

