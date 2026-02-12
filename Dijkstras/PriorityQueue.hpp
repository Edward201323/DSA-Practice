#pragma once

#include "ArrayHeap.hpp"

// An enum that specifies whether small or large priority values are dequeued first
enum class PriorityMode {
    ASCENDING, // small priority values leave first
    DESCENDING, // large priority values leave first
};

// T - the type of the data being stored in the priority queue
// P - the type of the priority (probably float, int, etc)
template <typename T, typename P>
class PriorityQueue {
private:

    // An element in the priority queue has both:
    // - the actual item to be stored
    // - its priority level, which determines the order in which dequeue happens
    struct PriorityRecord {
        T data;
        P priority;

        PriorityRecord(T t = T(), P p = P()) : data(t), priority(p) {}

        // We store these records in an ArrayHeap implementation
        // that relies on having comparison operators.
        // The comparisons should all be based on the priority of the Record
        bool operator<(const PriorityRecord &rightObj) const {
            return this->priority < rightObj.priority;
        }
        bool operator>(const PriorityRecord &rightObj) const {
            return this->priority > rightObj.priority;
        }
        bool operator<=(const PriorityRecord &rightObj) const {
            return this->priority <= rightObj.priority;
        }
        bool operator>=(const PriorityRecord &rightObj) const {
            return this->priority >= rightObj.priority;
        }
    };

    // Whether large or small priority values exit the queue first
    PriorityMode mode;

    // The underlying heap data structure to store the elements in the priority queue
    // while allowing for efficient update operations
    ArrayHeap<PriorityRecord> heap;

public:

    // m - whether to dequeue in order of increasing versus decreasing priority
    // i - the max size of the underlying ArrayHeap
    PriorityQueue(PriorityMode m = PriorityMode::DESCENDING, int i = 100);

    // remove the next element from the queue, based on the priority order
    void dequeue();

    // insert an element into the queue with the given priority
    void enqueue(const T &elem, const P &priority);

    // access the element at the front of the queue, based on priority order
    T frontElement() const;

    // access the priority of the element at the front of the queue, based on priority order
    P frontPriority() const;

    // returns true if there are no elements in the queue, and false otherwise
    bool isEmpty() const;
};

template <typename T, typename P>
PriorityQueue<T,P>::PriorityQueue(PriorityMode m, int i) :
    mode(m),
    heap(i, (m == PriorityMode::ASCENDING) ? HeapOrder::MIN_HEAP : HeapOrder::MAX_HEAP) {
}

template <typename T, typename P>
void PriorityQueue<T,P>::dequeue() {
    heap.remove();
}

template <typename T, typename P>
void PriorityQueue<T,P>::enqueue(const T &elem, const P &priority) {
    heap.insert(PriorityRecord(elem, priority));
}

template <typename T, typename P>
T PriorityQueue<T,P>::frontElement() const {
    return heap.peek().data;
}

template <typename T, typename P>
P PriorityQueue<T,P>::frontPriority() const {
    return heap.peek().priority;
}

template <typename T, typename P>
bool PriorityQueue<T,P>::isEmpty() const {
    return heap.getLength() == 0;
}
