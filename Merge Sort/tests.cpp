#include "tests.hpp"
#include "MergeSorter.hpp"
#include <iostream>
using namespace std;

/**
 * We have some forward declarations for auxiliary methods
 *(I didn't put these in the header, because other files don't need to access them)
 */

// Converts a given array of size N into a list of linked Nodes, and then sorts them with MergeSorter
void runTest(const int arr[], const int N);

// Construct a list of linked Nodes out of a given array of size N
Node* buildList(const int arr[], const int N);

// Deallocate a linked list (intended to be used after buildList)
void deallocateList(Node *head);


/**
 * Definitions for the functions declared in the header
 */

// cout the contents of a linked list starting from the given Node
void print(Node *head) {
    while (head != nullptr) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << "nullptr" << endl;
}

void testSplit() {
    MergeSorter ms;
    Node *head1, *head2;

    // Test 1
    int t1[2] = {1, 2};
    head1 = buildList(t1, 2);
    cout << "Splitting:" << endl;
    print(head1);
    cout << "Yields:" << endl;
    head2 = ms.split(head1);
    print(head1);
    print(head2);
    deallocateList(head1);
    deallocateList(head2);

    cout << endl;

    // Test 2
    int t2[5] = {1, 2, 3, 4, 5};
    head1 = buildList(t2, 5);
    cout << "Splitting:" << endl;
    print(head1);
    cout << "Yields:" << endl;
    head2 = ms.split(head1);
    print(head1);
    print(head2);
    deallocateList(head1);
    deallocateList(head2);
}

void testMerge() {
    MergeSorter ms;
    Node *head1, *head2;
    Node *merged;

    // Test 1
    head1 = new Node(1);
    head2 = new Node(2);
    cout << "Merging:" << endl;
    print(head1);
    print(head2);
    cout << "Yields:" << endl;
    merged = ms.merge(head1, head2);
    print(merged);
    deallocateList(merged);

    cout << endl;

    // Test 2
    int a1[3] = {2, 4, 5};
    int b1[2] = {1, 3};
    head1 = buildList(a1, 3);
    head2 = buildList(b1, 2);
    cout << "Merging:" << endl;
    print(head1);
    print(head2);
    cout << "Yields:" << endl;
    merged = ms.merge(head1, head2);
    print(merged);
    deallocateList(merged);
}

void testSort() {
    // Test 0
    const int N0 = 2;
    int arr0[N0] = { 2, 1 };
    runTest(arr0, N0);

    cout << endl;

    // Test 1
    const int N1 = 8;
    int arr1[N1] = { 42, 20, 17, 13, 28, 14, 23, 15 };
    runTest(arr1, N1);

    cout << endl;

    // Test 2
    const int N2 = 10;
    int arr2[N2] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
    runTest(arr2, N2);
}


/**
 * Definitions for the functions declared in this file
 */

// Converts a given array of size N into a list of linked Nodes, and then sorts them with MergeSorter
void runTest(const int arr[], const int N) {
    Node *head = buildList(arr, N); // get a linked-list version of the data
    MergeSorter sorter;

    cout << "Before: ";
    print(head);
    head = sorter.mergeSort(head);
    cout << "After:  ";
    print(head);
    cout << "# Comparisons: " << sorter.numComparisons << endl;

    // Make sure to deallocate the memory we got from buildList
    deallocateList(head);
}

// Construct a list of linked Nodes out of a given array of size N.
// It is up to the caller to make sure the memory allocated from this method gets freed.
Node* buildList(const int arr[], const int N) {
    Node *head = new Node(arr[0]);
    Node *tail = head; // keep track of the tail for easy appends
    for (int i = 1; i < N; i++) {
        tail->next = new Node(arr[i]);
        tail = tail->next;
    }

    return head;
}

// Deallocate a linked list (intended to be used after buildList)
// (classes and destructors normally help us avoid having to remember to do all these things!)
void deallocateList(Node *head) {
    while (head != nullptr) {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
}
