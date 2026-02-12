#include "ArraySorter.hpp"
#include <iostream>
using namespace std;

// An enum for the different sorting implementations
enum class SortType {
    BUBBLE, SELECTION, INSERTION,
};

void testSort(SortType);

int main() {
    // Test each of the sorting implementations
    testSort(SortType::BUBBLE);
    testSort(SortType::SELECTION);
    testSort(SortType::INSERTION);
    return 0;
}

void testSort(SortType st) {
    const int N = 8;
    int arr[N] = { 42, 20, 17, 13, 28, 14, 23, 15 };

    // Output the initial (unsorted) array
    cout << "Input: ";
    for (int i = 0; i < N; i++) {
        cout << " " << arr[i];
    }
    cout << endl;

    // Call the appropriate sorting algorithm
    ArraySorter sorter;
    cout << "Using ";
    switch (st) {
    case SortType::BUBBLE:
        cout << "Bubble";
        sorter.bubbleSort(arr, N);
        break;
    case SortType::SELECTION:
        cout << "Selection";
        sorter.selectionSort(arr, N);
        break;
    case SortType::INSERTION:
        cout << "Insertion";
        sorter.insertionSort(arr, N);
        break;
    }
    cout << " Sort..." << endl;

    // Output the (hopefully) now-sorted array
    cout << "Output:";
    for (int i = 0; i < N; i++) {
        cout << " " << arr[i];
    }
    cout << endl;

    // Output information about how many comparisons and swaps were made
    cout << "# Comparisons: " << sorter.getNumComparisons() << endl;
    cout << "# Swaps: " << sorter.getNumSwaps() << endl;
    cout << endl;
}
