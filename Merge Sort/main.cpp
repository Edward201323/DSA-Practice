#include "tests.hpp"
#include <iostream>
using namespace std;

int main() {
    int choice;

    // prompt the user for which test to run
    do {
        cout << "Test your implementation..." << endl;
        cout << "1 - test MergeSorter::split" << endl;
        cout << "2 - test MergeSorter::merge" << endl;
        cout << "3 - test MergeSorter::mergeSort" << endl;
        cout << "Enter 1, 2, or 3: ";
        cin >> choice;
        cout << endl;
    } while(choice != 1 && choice != 2 && choice != 3);

    // run the test
    switch(choice) {
    case 1:
        testSplit();
        break;
    case 2:
        testMerge();
        break;
    case 3:
        testSort();
        break;
    }

    return 0;
}
