#pragma once

#include "Queue.hpp"
#include <iostream>

template <typename T>
class ArrayQueue : public Queue<T> {
    private:
        // an array that contains the elements
        T* buffer;

        // the maximum number of elements in the queue
        int maxSize;

        // the current position of the front element in the queue
        int frontIndex;

        // the current position of the back element in the queue
        int backIndex;

        // copy the values from the argument queue to `this`
        void copy(const ArrayQueue<T>&);

        void resize();

    public:
        // constructor with the maximum size as the argument
        ArrayQueue(int = 100);

        // copy constructor
        ArrayQueue(const ArrayQueue<T>&);

        // overloaded assignment operator
        ArrayQueue<T>& operator=(const ArrayQueue<T>&);

        // destructor
        virtual ~ArrayQueue();

        // return the element at the back of the queue
        virtual T back() const override;

        // remove all elements in the queue, resetting to the initial state
        virtual void clear() override;

        // remove the front element from the queue
        virtual void dequeue() override;

        // add the argument to the back of the queue
        virtual void enqueue(const T&) override;

        // return the element at the front of the queue
        virtual T front() const override;

        // return the current length of the queue
        virtual int getLength() const override;

        // return the maximum size of the queue
        int getMaxSize() const;

        // determine if the queue is currently empty
        virtual bool isEmpty() const override;

        // determine if the queue is currently full
        bool isFull() const;
};

template <typename T>
ArrayQueue<T>::ArrayQueue(int i) {
    this->buffer = new T[i];
    this->maxSize = i;
    this->length = 0;
    this->frontIndex = 0;
    this->backIndex = 0;
}

template <typename T>
ArrayQueue<T>::ArrayQueue(const ArrayQueue<T>& copyObj) {
    copy(copyObj);
}

template <typename T>
ArrayQueue<T>& ArrayQueue<T>::operator=(const ArrayQueue<T>& rightObj) {
    if (this != &rightObj) {
        // TODO
        // do whatever you need to do before `copy` is called
        // to ensure there are no bugs
        copy(rightObj);
    }
    return *this;
}

template <typename T>
void ArrayQueue<T>::resize(){
    T *old_array = this->buffer;

    this->buffer = new T[this->length * 2];
    this->maxSize *= 2;

    for(int i = 0; i < this->length; i++){
        this->buffer[i] = old_array[i];
    }
    
    delete[] old_array;
}

template <typename T>
ArrayQueue<T>::~ArrayQueue() {
    delete this->buffer;
}

template <typename T>
T ArrayQueue<T>::back() const {
    if(isEmpty()){
        throw std::string("The queue is empty");
    }
    return this->buffer[backIndex];
}

template <typename T>
void ArrayQueue<T>::clear() {
    delete[] this->buffer;
    this->maxSize = 10;
    this->length = 0;
    this->frontIndex = 0;
    this->backIndex = 0;
}

template <typename T>
void ArrayQueue<T>::copy(const ArrayQueue<T>& copyObj) {
    // TODO
}

template <typename T>
void ArrayQueue<T>::dequeue() {
    // TODO
}

template <typename T>
void ArrayQueue<T>::enqueue(const T& elem) {
    if(this->length == this->maxSize){
        resize();
    }
    this->backIndex = (this->backIndex + 1) % this->maxSize;
    this->buffer[this->backIndex] = ;
    this->length++;
}

template <typename T>
T ArrayQueue<T>::front() const {
    return this->buffer[frontIndex];
}

template <typename T>
int ArrayQueue<T>::getLength() const {
    return this->length;
}

template <typename T>
int ArrayQueue<T>::getMaxSize() const {
    if(isEmpty()){
        throw std::string("The queue is empty");
    }
    return maxSize;
}

template <typename T>
bool ArrayQueue<T>::isEmpty() const {
    return this->length == 0;
}

template <typename T>
bool ArrayQueue<T>::isFull() const {
    return this->length == maxSize;
}
