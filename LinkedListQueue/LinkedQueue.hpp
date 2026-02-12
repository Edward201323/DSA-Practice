#pragma once

#include "Queue.hpp"
#include <iostream>

using std::cout;
using std::endl;

template <typename T>
class LinkedQueue : public Queue<T> {
    protected:
        // represents an element in the queue
        struct Node {
            T value;
            Node *next;

            Node(T v = T(), Node* n = nullptr)
            : value(v), next(n) { }
        };

        // a pointer to the front (head) and back (last) of the queue
        Node *head, *last;

    private:
        // copy the state of the argument queue to `this`
        void copy(const LinkedQueue<T>&);

    public:
        // default constructor
        LinkedQueue();

        // copy constructor
        LinkedQueue(const LinkedQueue<T>&);

        // overloaded assignment operator
        LinkedQueue<T>& operator=(const LinkedQueue<T>&);

        // destructor
        virtual ~LinkedQueue();

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

        // determine if the queue currently empty
        virtual bool isEmpty() const override;
};

template <typename T>
LinkedQueue<T>::LinkedQueue() {
    this->head = nullptr;
    this->last = nullptr;
    this->length = 0;
}

template <typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T>& copyObj) {
    this->head = nullptr;
    this->last = nullptr;
    this->length = 0;
    copy(copyObj);
}

template <typename T>
LinkedQueue<T>& LinkedQueue<T>::operator=(const LinkedQueue<T>& rightObj) {
    if (this != &rightObj) {
        clear();
        copy(rightObj);
    }
    return *this;
}

template <typename T>
LinkedQueue<T>::~LinkedQueue() {
    clear();
}

template <typename T>
T LinkedQueue<T>::back() const {
    if(this->length == 0){
        throw std::string("The queue is empty.");
    }
    return this->last->value;
}

template <typename T>
void LinkedQueue<T>::clear() {
    if(this->length == 0){
        return;
    }
    Node *curr = this->head;
    while(curr != nullptr){
        Node *holder = curr->next;
        delete curr;
        curr = holder;
    }
    this->head = nullptr;
    this->last = nullptr;
    this->length = 0;
}

template <typename T>
void LinkedQueue<T>::copy(const LinkedQueue<T>& copyObj) {
    Node *curr = copyObj.head;
    while(curr != nullptr){
        enqueue(curr->value);
        curr = curr->next;
    }
    
}

template <typename T>
void LinkedQueue<T>::dequeue() { // O(1), has a head pointer
    if(this->length == 0){
        throw std::string("The queue is empty");
    }
    Node *holder = this->head;
    if(this->length == 1){
        this->last = nullptr;
        this->head = nullptr;
    } else {
        this->head = this->head->next;
    }
    delete holder;
    this->length--;
}

template <typename T>
void LinkedQueue<T>::enqueue(const T& elem) { // O(1) with a last pointer
    if(this->length == 0){ // Edge case
        this->head = new Node(elem);
        this->last = this->head;
        this->length++;
        return;
    }
    this->last->next = new Node(elem);
    this->last = this->last->next;
    this->length++;
}

template <typename T>
T LinkedQueue<T>::front() const { // O(1), have pointer on node
    if(this->length == 0){
        throw std::string("The queue is empty");
    }
    return this->head->value;
}

template <typename T>
int LinkedQueue<T>::getLength() const { // O(1)
    return this->length;
}

template <typename T>
bool LinkedQueue<T>::isEmpty() const { // O(1)
    return this->length == 0;
}

