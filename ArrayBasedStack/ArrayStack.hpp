#pragma once

#include "Stack.hpp"
#include <iostream>
#include <string>

template <typename T>
class ArrayStack : public Stack<T> {
    private:
        // an array that contains the elements
        T* buffer;

        // the maximum number of elements in the stack
        int maxSize;
        
        int default_size;

        // copy the state of the argument stack to `this`
        void copy(const ArrayStack<T>&);

        void resize();

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

        // retrun default size
        int getDefaultSize() const;

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
    if(i <= 0){
        i = 1;
    }
    this->buffer = new T[i];
    this->length = 0;
    this->default_size = i;
    this->maxSize = i;
}

template <typename T>
ArrayStack<T>::ArrayStack(const ArrayStack<T>& copyObj) {
    copy(copyObj);
}

template <typename T>
void ArrayStack<T>::resize(){
    T *old_stack = this->buffer;

    this->maxSize *= 2;
    this->buffer = new T[maxSize];
    
    for(int i = 0; i < this->length; i++){
        this->buffer[i] = old_stack[i];
    }

    delete[] old_stack;
}

template <typename T>
ArrayStack<T>& ArrayStack<T>::operator=(const ArrayStack<T>& rightObj) {
    if (this != &rightObj) { // avoid self-assignment
        copy(rightObj);
    }
    return *this;
}

template <typename T>
ArrayStack<T>::~ArrayStack() {
    delete[] this->buffer;
}

template <typename T>
void ArrayStack<T>::clear() {
    delete[] this->buffer;
    this->maxSize = this->default_size;
    this->length = 0;
    this->buffer = new T[this->maxSize];
}

template <typename T>
void ArrayStack<T>::copy(const ArrayStack<T>& copyObj) { // O(n)
    if(this->buffer != nullptr){
        delete[] this->buffer;
    }
    this->buffer = new T[copyObj.getMaxSize()];
    this->default_size = copyObj.getDefaultSize();
    this->length = copyObj.getLength();
    for(int i = 0; i < this->length; i++){
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
int ArrayStack<T>::getDefaultSize() const {
    return default_size;
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
    if (isEmpty()) {
        throw std::string("Cannot peek an empty stack.");
    }
    return this->buffer[this->length - 1];
}

template <typename T>
void ArrayStack<T>::pop() {
    if (isEmpty()) {
        throw std::string("Out of range.");
    }
    this->length--;
}

template <typename T>
void ArrayStack<T>::push(const T& elem) {
    if(this->length >= maxSize){
        resize();
    }
    this->buffer[this->length] = elem;
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
