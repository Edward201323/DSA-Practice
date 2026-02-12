#include "heaptest.hpp"
#include "ArrayHeap.hpp"
#include <iostream>
using namespace std;

void test5(HeapOrder order);

void testHeap() {
    // TODO you can add other tests here, if you need to troubleshoot

    cout << "Max-Heap test: " << endl;
    test5(HeapOrder::MAX_HEAP);

    cout << endl;

    cout << "Min-Heap test: " << endl;
    test5(HeapOrder::MIN_HEAP);
}

void test5(HeapOrder order) {
    ArrayHeap<int> h(5, order);
    cout << "Inserting 2 3 4 5 1 into the heap (in that order)" << endl;
    int arr[5] = {2, 3, 4, 5, 1};
    for (int i : arr) {
        cout << "inserting " << i << ": " << std::flush;
        h.insert(i);
        h.print();
    }
    cout << "Removing all, in order: " << endl;
    while (h.getLength() > 0) {
        cout << h.peek() << " ";
        h.remove();
    }
    cout << endl;
}
