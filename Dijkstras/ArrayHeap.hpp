#pragma once

#include <iostream>
#include <string>

// an enum to specify whether a heap object is a min-heap or a max-heap
enum class HeapOrder {
    MIN_HEAP,
    MAX_HEAP,
};

// T - the type of data to store in the heap. It needs to implement comparison operations.
template <typename T>
class ArrayHeap {
private:
    // the size of the underlying dynamic array
    int maxSize;

    // how many elements are in the array-based tree:
    // - 0 when the heap is empty
    // - when non-empty, 0 to length-1 (inclusive) is the range of valid indices
    int length;

    // the underlying dynamic array to store a complete array-based tree
    T *buffer;

    // specifies whether this is a min-heap or max-heap
    HeapOrder order;

    // returns true if the element at index `parent` is <= the element at index `child`, for min heaps
    // (and vice-versa for max-heaps: true when `parent` is >= `child`)
    bool correctlyOrdered(int parent, int child);

    // sift down the node at a specific index
    void siftDown(int index);

    // sift up the node at a specific index
    void siftUp(int index);

    // swap two elements in the array, given by their indices
    void swap(int index1, int index2);

public:
    // - i: the maximum size of the underlying array for storing the tree
    // - o: whether this should be a min-heap or max-heap
    ArrayHeap(int i = 100, HeapOrder o = HeapOrder::MIN_HEAP);
    ~ArrayHeap();

    // returns how many elements are stored in the heap
    int getLength() const;

    // add an element into the heap
    void insert(const T &elem);

    // look at whatever the root element of the heap is
    const T& peek() const;

    // prints the array representation (for debugging)
    void print() const;

    // remove the root element from the heap
    void remove();
};

template <typename T>
ArrayHeap<T>::ArrayHeap(int i, HeapOrder o) : maxSize(i), length(0), buffer(new T[i]), order(o) {}

template <typename T>
ArrayHeap<T>::~ArrayHeap() {
    delete [] buffer;
}

template <typename T>
bool ArrayHeap<T>::correctlyOrdered(int parent, int child) {
    if (order == HeapOrder::MAX_HEAP)
        return buffer[parent] >= buffer[child];
    else
        return buffer[parent] <= buffer[child];
}

template <typename T>
int ArrayHeap<T>::getLength() const {
    return length;
}

template <typename T>
void ArrayHeap<T>::insert(const T &elem) {
    if (length == maxSize)
        throw std::string("insert error: heap is full");


    buffer[length] = elem;
    length++;

    siftUp(length - 1);
}

template <typename T>
const T& ArrayHeap<T>::peek() const {
    if (length == 0) {
        throw std::string("peek error: heap is empty");
    }
    return buffer[0];
}

template <typename T>
void ArrayHeap<T>::print() const {
    for (int i = 0; i < length; i++) {
        std::cout << buffer[i] << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void ArrayHeap<T>::remove() {
    if (length == 0)
        throw std::string("remove error: heap is empty");

    // replace the root with the last leaf
    buffer[0] = buffer[length - 1];
    length--;

    // sift that former-leaf down to preserve the heap ordering property
    siftDown(0);
}

template <typename T>
void ArrayHeap<T>::siftDown(int index) {
    // find the indices of this node's children
    // (which might not exist -- we'll have to compare them to this->length)
    int left = index * 2 + 1;
    int right = index * 2 + 2;

    // if the child indices are in bounds, we'll have to do comparisons and swaps
    // (and if they're not in bounds, then the node is already sifted down as far as it can go)
    if (left < length) {
        // left is a valid index: the given `index` has a left child in the tree

        // if that's the last node in the tree,
        // there's no right child, so we have a special case of only making one comparison
        if (left == length - 1) {
            if (!correctlyOrdered(index, left)) {
                swap(index, left);
            }
        } else { // since right == left + 1, we know right < length at this point
            // there are two children: find out which would be correct to swap with
            int bestChild = correctlyOrdered(left, right) ? left : right;
            if (!correctlyOrdered(index, bestChild)) {
                swap(index, bestChild);
                siftDown(bestChild);
            }
        }
    }
}

template <typename T>
void ArrayHeap<T>::siftUp(int index) {
    if (index == 0) return; 

    int parent = (index - 1) / 2;

    if (!correctlyOrdered(parent, index)) {
        swap(parent, index);

        siftUp(parent);
    }
}
template <typename T>
void ArrayHeap<T>::swap(int index1, int index2) {
    T temp = buffer[index1];
    buffer[index1] = buffer[index2];
    buffer[index2] = temp;
}
