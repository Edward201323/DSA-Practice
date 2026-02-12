#pragma once

struct Node {
    int data;
    Node *next;

    // Constructor that allows specifying the values for data and next, with defaults
    Node(int d = 0, Node *n = nullptr) : data(d), next(n) {}
};

class MergeSorter {
    // `friend` lets us say some functions can access private methods of this class.
    // We'll use this to test the methods (tests.hpp/.cpp)
    // WARNING: use this feature VERY sparingly (there are often better ways to test code)
    friend void testSplit();
    friend void testMerge();

private:
    // returns `left < right` and updates numComparisons
    bool lessThan(int left, int right);

    // Splits the given linked list into two equal sublists (or nearly equal when the length is odd).
    // The passed `head` argument remains the head of a now-shorter list;
    // the return value is the head of the other sublist.
    Node* split(Node *head);

    // Combines two sorted lists and returns a pointer to the head of the now-sorted combined list
    Node* merge(Node *head1, Node *head2);

public:
    // track how many comparisons the sorting algorithm performs
    int numComparisons;

    // Constructor
    MergeSorter();

    // Performs merge sort on the given linked list
    Node* mergeSort(Node *head);
};
