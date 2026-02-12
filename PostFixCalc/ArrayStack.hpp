#pragma once

#include "Stack.hpp"
#include <iostream>

template <typename T>
class ArrayStack : public Stack<T> {
    private:
        // an array that contains the elements
        T* buffer;

        // the maximum number of elements in the stack
        int maxSize;

        // copy the state of the argument stack to `this`
        void copy(const ArrayStack<T>&);

    public:
        // constructor with the maximum size as the argument
        ArrayStack(int = 100);

        // copy constructor
        ArrayStack(const ArrayStack<T>&);

        // overloaded assignment operator
        ArrayStack<T>& operator=(const ArrayStack<T>&);

        // destructor
        virtual ~ArrayStack();

        // remove all elements in the stack, resetting to the initial state
        virtual void clear() override;

        // return the current length of the stack
        virtual int getLength() const override;

        // return the maximum size of the stack
        int getMaxSize() const;

        // determine if the stack currently empty
        virtual bool isEmpty() const override;

        // determine if the stack is currently full
        bool isFull() const;

        // return the element at the top of the stack
        virtual T peek() const override;

        // remove the top element from the stack
        virtual void pop() override;

        // add the argument to the top of the stack
        virtual void push(const T&) override;

        // overloaded stream insertion operator to make printing easier
        template <typename U>
        friend std::ostream& operator<<(std::ostream&, const ArrayStack<U>&);
};

template <typename T>
ArrayStack<T>::ArrayStack(int i) {
    maxSize = i;
    buffer = new T[i];
    this->length = 0;
}

template <typename T>
ArrayStack<T>::ArrayStack(const ArrayStack<T>& copyObj) {
    copy(copyObj);
}

template <typename T>
ArrayStack<T>& ArrayStack<T>::operator=(const ArrayStack<T>& rightObj) {
    if (this != &rightObj) { // avoid self-assignment
        // Deallocate the existing this->buffer
        // since the copy method will allocate its own memory for that
        delete[] buffer;
        copy(rightObj);
    }
    return *this;
}

template <typename T>
ArrayStack<T>::~ArrayStack() {
    delete[] buffer;
}

template <typename T>
void ArrayStack<T>::clear() {
    this->length = 0;
}

// This method will allocate dynamic memory and store it in this->buffer,
// so make sure you've deallocated anything already there before calling
template <typename T>
void ArrayStack<T>::copy(const ArrayStack<T>& copyObj) {
    // copy enough of copyObj's underlying array
    // to make sure we have a copy of everything that's in the stack
    this->maxSize = copyObj.maxSize;
    this->length = copyObj.length;
    this->buffer = new T[maxSize];
    for (int i = 0; i < this->length; i++) {
        this->buffer[i] = copyObj.buffer[i];
    }
}

template <typename T>
int ArrayStack<T>::getLength() const {
    return this->length;
}

template <typename T>
int ArrayStack<T>::getMaxSize() const {
    return maxSize;
}

template <typename T>
bool ArrayStack<T>::isEmpty() const {
    return this->length == 0;
}

template <typename T>
bool ArrayStack<T>::isFull() const {
    return this->length == maxSize;
}

template <typename T>
T ArrayStack<T>::peek() const {
    if (this->length == 0) {
        throw std::string("peek error: stack is empty");
    }
    return buffer[this->length - 1];
}

template <typename T>
void ArrayStack<T>::pop() {
    if (this->length == 0) {
        throw std::string("pop error: stack underflow");
    }
    this->length--;
}

template <typename T>
void ArrayStack<T>::push(const T& elem) {
    if (this->length == maxSize) {
        throw std::string("push error: stack overflow");
    }
    buffer[this->length] = elem;
    this->length++;
}

template <typename T>
std::ostream& operator<<(std::ostream& outStream, const ArrayStack<T>& myObj) {
    if (myObj.isEmpty()) {
        outStream << "Stack is empty, no elements to display.\n";
    }
    else {
        for (int i = myObj.length - 1; i >= 0; i--) {
            outStream << (i == myObj.length - 1 ? "top\t" : "\t")
                      << myObj.buffer[i] << std::endl;
        }
    }

    return outStream;
}
