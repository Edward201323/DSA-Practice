#pragma once

#include "List.hpp"
#include <iostream>
#include <string>

using std::cout;
using std::endl;

template<typename T>
class LinkedListR: public List<T> {
protected:
    // represents an element in the linked list
    struct Node {
        T value;
        Node *next;

        Node(T v = T(), Node *n = nullptr) :
                value(v), next(n) {
        }
    };

    // a pointer to the front of the list
    Node *head;

private:
    // Recursive methods that do most of the work for the respective public methods
    void appendRec(const T&, Node*);
    void clearRec(Node*);
    T getElementRec(unsigned, Node*) const;
    void insertRec(unsigned, const T&, Node*);
    void printRec(Node*) const;
    void removeRec(unsigned, Node*);
    void replaceRec(unsigned, const T&, Node*);

public:
    LinkedListR();
    ~LinkedListR();

    void append(const T&) override;
    void clear() override;
    T getElement(unsigned) const override;
    unsigned getLength() const override;
    void insert(unsigned, const T&) override;
    bool isEmpty() const override;
    void print() const;
    void remove(unsigned) override;
    void replace(unsigned, const T&) override;
};

template<typename T>
LinkedListR<T>::LinkedListR() :
        head(nullptr) {
}

template<typename T>
LinkedListR<T>::~LinkedListR() {
    clear();
}

template<typename T>
void LinkedListR<T>::append(const T &elem) {
    if(!head){
        this->head = new Node(elem);
        this->length++;
    } else {
        appendRec(elem, this->head);
    }

}

template<typename T>
void LinkedListR<T>::appendRec(const T &elem, Node *node) {
    if(!node->next){
        node->next = new Node(elem);
        this->length++;
        return;
    }
    appendRec(elem, node->next);
}

template<typename T>
void LinkedListR<T>::clear() {
    // Recursively deallocate each node
    clearRec(head);
    // Update head and length afterwards
    head = nullptr;
    this->length = 0;
}

template<typename T>
void LinkedListR<T>::clearRec(Node *node) {
    if(!node){
        return;
    }
    clearRec(node->next);
    delete node;
    this->length--;
}

template<typename T>
T LinkedListR<T>::getElement(unsigned position) const {
    if(position < 0 || position >= this->length){
        throw std::string("Out of bounds");
    }
    return getElementRec(position, this->head);
}

template<typename T>
T LinkedListR<T>::getElementRec(unsigned position, Node *node) const {
    if(position == 0){
        return node->value;
    }
    return getElementRec(position - 1, node->next);
}

template<typename T>
unsigned LinkedListR<T>::getLength() const {
    return this->length;
}

template<typename T>
void LinkedListR<T>::insert(unsigned position, const T &elem) {
    if (position >= this->length) {
        throw std::string("insert error: position out of bounds");
    }
    if (position == 0) {
        // updating the head is still a special case
        head = new Node(elem, head);
    } else {
        // otherwise we can use the recursive method
        insertRec(position, elem, head);
    }
    this->length++;
}

template<typename T>
void LinkedListR<T>::insertRec(unsigned position, const T &elem, Node *node) {
    if(position == 1){
        Node *holder = node->next;
        node->next = new Node(elem);
        node->next->next = holder;
        this->length++;
        return;
    }
    insertRec(position - 1, elem, node->next);
}

template<typename T>
bool LinkedListR<T>::isEmpty() const {
    return this->length == 0;
}

template<typename T>
void LinkedListR<T>::print() const {
    if (head == nullptr) {
        std::cout << "List is empty, no elements to display." << std::endl;
    } else {
        printRec(head);
        std::cout << std::endl;
    }
}

template<typename T>
void LinkedListR<T>::printRec(Node *node) const {
    if (node != nullptr) {
        std::cout << node->value;
    }
    if (node->next != nullptr) {
        std::cout << " --> ";
        printRec(node->next);
    }
}

template<typename T>
void LinkedListR<T>::remove(unsigned position) {
    if (position >= this->length) {
        throw std::string("remove error: index out of bounds");
    }
    if (position == 0) {
        // updating the head is still a special case
        Node *prev = head;
        head = head->next;
        delete prev;
    } else {
        // otherwise we can use the recursive method
        removeRec(position, head);
    }
    this->length--;
}

template<typename T>
void LinkedListR<T>::removeRec(unsigned position, Node *node) {
    if(position == 1){
        Node *holder = node->next;
        node->next = node->next->next;
        delete holder;
        this->length--;
        return;
    }
    removeRec(position - 1, node->next);
}

template<typename T>
void LinkedListR<T>::replace(unsigned position, const T &elem) {

    if(position >= this->length){
        throw std::string("Out of bounds");
    }
    replaceRec(position, elem, this->head);
}

template<typename T>
void LinkedListR<T>::replaceRec(unsigned position, const T &elem, Node *node) {
    if(position == 0){
        node->value = elem;
        return;
    }
    replaceRec(position - 1, elem, node->next);
}
