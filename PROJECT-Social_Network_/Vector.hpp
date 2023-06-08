#pragma once

//Github https://github.com/plamena-ilieva

#include <iostream>
#include <exception>
#include <fstream>
template <typename T>
class Vector 
{
    T* data;
    size_t size;
    size_t capacity;

    void free();
    void copyFrom(const Vector<T>& other);
    void moveFrom(Vector&& other);
    void resize();

public:
    Vector();
    Vector(const Vector<T>& other);
    Vector(Vector<T>&& other);
    Vector<T>& operator=(const Vector<T>& other);
    Vector<T>& operator=(Vector&& other);
    ~Vector();

    size_t getSize() const;
    size_t getCapacity() const;
    void setCapacity(size_t newCapacity);

    void pushBack(const T& element);
    void pushBack(T&& element);

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    void popBack();
    void clear();
};

template <typename T>
void Vector<T>::free() 
{
    delete[] data;
}

template <typename T>
void Vector<T>::copyFrom(const Vector<T>& other) 
{
    size = other.size;
    capacity = other.capacity;

    data = new T[capacity];

    for (size_t i = 0; i < size; i++)
    {
        data[i] = other.data[i];
    }
}

template <typename T>
void Vector<T>::moveFrom(Vector&& other)
{
    data = other.data;
    size = other.size;
    capacity = other.capacity;

    other.data = nullptr;
    other.size = 0;
    other.capacity = 0;
}

template <typename T>
void Vector<T>::resize() 
{
    capacity = 2 * capacity;

    T* newMemory = new T[capacity];

    for (size_t i = 0; i < size; i++)
    {
        newMemory[i] = std::move(data[i]);
    }

    delete[] data;
    data = newMemory;
}

template <typename T>
Vector<T>::Vector() 
{
    size = 0;
    capacity = 8;
    data = new T[capacity];
}

template <typename T>
void Vector<T>::setCapacity(size_t newCapacity) 
{
    size = 0;
    delete[] data;
    capacity = newCapacity;
    data = new T[capacity];
}

template <typename T>
Vector<T>::Vector(const Vector<T>& other) 
{
    copyFrom(other);
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) 
{
    if (this != &other) 
    {
        free();
        copyFrom(other);
    }
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& other)
{
    if (this != &other)
    {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

template <typename T>
Vector<T>::~Vector<T>() 
{
    free();
}

template <typename T>
size_t Vector<T>::getSize() const 
{
    return size;
}

template <typename T>
size_t Vector<T>::getCapacity() const 
{
    return capacity;
}

template <typename T>
void Vector<T>::pushBack(const T& element) 
{
    if (size == capacity)
    {
        resize();
    }

    size++;
    data[size - 1] = element;
}

template <typename T>
void Vector<T>::pushBack(T&& element)
{
    if (size == capacity)
    {
        resize();
    }

    size++;
    data[size - 1] = std::move(element);
}

template <typename T>
T& Vector<T>::operator[](size_t index) 
{
    if (index >= size)
    {
        throw std::out_of_range(" of range");
    }

    return data[index];
}

template <typename T>
const T& Vector<T>::operator[](size_t index) const 
{
    if (index >= size)
    {
        throw std::out_of_range("out of ");
    }

    return data[index];
}

template <typename T>
void Vector<T>::popBack() 
{
    --size;
}

template <typename T>
void Vector<T>::clear() 
{
    free();
    size = 0;
    capacity = 8;
    data = new T[capacity];
}