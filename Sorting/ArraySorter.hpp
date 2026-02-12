#pragma once

class ArraySorter {
private:
    // Variables to count the number of comparisons and the number of swaps
    int numComparisons;
    int numSwaps;

    // A function that returns `left < right` but also increments the comparison counter
    template<typename T>
    bool lessThan(const T &left, const T &right);

    // Swap two pieces of data (specified by their indices) in the given array
    // and increment the swap counter
    template<typename T>
    void swap(T arr[], int i, int j);

public:
    ArraySorter();

    // Access the the number of comparisons / number of swaps
    int getNumComparisons() const;
    int getNumSwaps() const;

    // Set the counters back to 0
    void resetCounts();

    // Three different sorting algorithms that modify the given array

    template<typename T>
    void bubbleSort(T arr[], int N);

    template<typename T>
    void insertionSort(T arr[], int N);

    template<typename T>
    void selectionSort(T arr[], int N);
};

ArraySorter::ArraySorter() {
    resetCounts();
}

template<typename T>
bool ArraySorter::lessThan(const T &left, const T &right) {
    numComparisons++;
    return left < right;
}

template<typename T>
void ArraySorter::swap(T arr[], int i, int j) {
    numSwaps++;
    // Source: https://www.youtube.com/watch?v=DJxEYOC8IRc
    // I thought it'd be fun to try this
    if(i != j){
        arr[i] ^= arr[j];
        arr[j] ^= arr[i];
        arr[i] ^= arr[j];
    }
}

void ArraySorter::resetCounts() {
    numComparisons = 0;
    numSwaps = 0;
}

int ArraySorter::getNumComparisons() const {
    return numComparisons;
}

int ArraySorter::getNumSwaps() const {
    return numSwaps;
}

template<typename T>
void ArraySorter::bubbleSort(T arr[], int N) { // O(n^2)
    for(int j = 0; j < N - 1; j++){
        for(int i = 0; i < N - j - 1; i++){
            if(lessThan(arr[i + 1], arr[i])){
                swap(arr, i, i + 1);
            }
        }
    }
}

template<typename T>
void ArraySorter::insertionSort(T arr[], int N) { // O(n^2)
    for(int i = 0; i < N; i++){
        int j = i;
        while(j > 0 && lessThan(arr[j], arr[j - 1])){
            swap(arr, j, j - 1);
            j--;
        }
    }
}

template<typename T>
void ArraySorter::selectionSort(T arr[], int N) { // O(n^2)
    for(int i = 0; i < N - 1; i++){
        int minIndex = i;
        for(int j = i + 1; j < N; j++){
            if(lessThan(arr[j], arr[minIndex])){
                minIndex = j;
            }
        }
        if(minIndex != i){
            swap(arr, i, minIndex);
        }
    }
}
