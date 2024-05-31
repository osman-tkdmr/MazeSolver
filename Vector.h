#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>


template <class T>
class Vector {
private:
    T* array;
    int capacity;
    int size;

    void allocateAndCopy(int newCapacity);

public:
    Vector();
    Vector(int initialCapacity);
    Vector(int initialSize, const T& value);
    Vector(const Vector<T>& other);
    Vector& operator=(const Vector<T>& other);
    ~Vector();

    void push_back(T data);
    void pop_back();
    T& operator[](int index);
    const T& operator[](int index) const;
    int getSize() const;
    bool empty() const;
    void resize(int newSize, const T& value = T());
    void reserve(int newCapacity);
    void clear();
    
    T& back();
    const T& back() const;
};

#include "Vector.cpp"

#endif // VECTOR_H

