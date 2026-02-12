#include <iostream>
#include "HashTableClosed.hpp"
using namespace std;

void testSequence(HashTableClosed<int, char> &t);

int main() {
    HashTableClosed<int, char> linear1(11, 1);
    HashTableClosed<int, char> linear3(11, 3);
    testSequence(linear1);
    testSequence(linear3);
    return 0;
}

void testSequence(HashTableClosed<int, char> &t) {
    cout << "==== BEGINNING TEST ====" << endl;
    try {
        t.insert(28, 'A');
        t.insert(63, 'B');
        t.insert(16, 'C');
        t.insert(17, 'D');
        t.insert(82, 'E');
        t.print();
        cout << endl;

        cout << "find 17: " << t.find(17) << endl;

        cout << "find 93: ";
        try {
            cout << t.find(93) << " (oh no, that should have thrown an exception)" << endl;
        } catch (const string &e) {
            cout << e << endl;
        }
        cout << endl;

        t.remove(63);
        t.print();
        cout << endl;

        cout << "find 82: " << t.find(82) << endl;
        cout << endl;

        t.insert(49, 'F');
        t.print();
    } catch (const string &e) {
        cout << "unexpected exception: " << e << endl;
    }
    cout << "==== END OF TEST ====" << endl;
}
