#include <iostream>
#include "hashing.hpp"
#include "HashTable.hpp"
using namespace std;

void testHashes();
void testSingleHash(const std::string &key, int foldNum, int expected);
void testTable();

int main() {
    int choice;
    do {
        cout << "1 - Test hash function" << endl;
        cout << "2 - Test hash table" << endl;
        cout << "Enter 1 or 2: ";
        cin >> choice;
    } while (choice != 1 && choice != 2);
    switch (choice) {
    case 1:
        testHashes();
        break;
    case 2:
        testTable();
        break;
    }
    return 0;
}

void testHashes() {
    testSingleHash("Alice", 1, 478);
    testSingleHash("Juan", 2, 44003);
    testSingleHash("George", 3, 12176596);
    if (cs20::hash("Bob", 2) == cs20::hash("Bob!", 2)) {
        cout << "Error: cs20::hash(\"Bob\", 2) == cs20::hash(\"Bob!\", 2)"
                << endl;
    } else {
        cout << "Good: cs20::hash(\"Bob\", 2) != cs20::hash(\"Bob!\", 2)"
                << endl;
    }
    if (cs20::hash("orange", 2) == cs20::hash("angeor", 2)) {
        cout << "Good: cs20::hash(\"orange\", 2) == cs20::hash(\"angeor\", 2)" << endl;
    } else {
        cout << "Error: cs20::hash(\"orange\", 2) != cs20::hash(\"angeor\", 2)" << endl;
    }
}

void testSingleHash(const std::string &key, int foldNum, int expected) {
    int result = cs20::hash(key, foldNum);
    if (result == expected) {
        cout << "Good: ";
    } else {
        cout << "Error: ";
    }
    cout << "cs20::hash(\"" << key << "\", " << foldNum << ") = " << result
            << " (expected " << expected << ")" << endl;
}

void testTable() {
    Dictionary<string, string> *d = new HashTable<string, string>(10);
    string command;
    string key, value;

    while (true) {
        cout << "Choose a function (clear, find, insert, remove, size, quit): ";
        cin >> command;

        if (command == "clear") {
            d->clear();
            cout << "Cleared the dictionary!" << endl;
        }
        else if (command == "find") {
            cout << "Enter a key to find: ";
            cin.ignore();
            getline(cin, key);
            try {
                value = d->find(key);
                cout << "Found value: " << value << endl;
            } catch (const string &e) {
                cout << e << endl;
            }
        }
        else if (command == "insert") {
            cout << "Enter a record to insert.\nKey: ";
            cin.ignore();
            getline(cin, key);
            cout << "Value: ";
            getline(cin, value);
            try {
                d->insert(key, value);
                cout << "Stored!" << endl;
            } catch (const string &e) {
                cout << e << endl;
            }
        }
        else if (command == "remove") {
            cout << "Enter a key to remove: ";
            cin.ignore();
            getline(cin, key);
            try {
                d->remove(key);
                cout << "Removed!" << endl;
            } catch (const string &e) {
                cout << e << endl;
            }
        }
        else if (command == "size") {
            cout << "Size: " << d->size() << endl;
        }
        else if (command == "quit") {
            break;
        }
        else {
            cout << "invalid option" << endl;
        }

        cout << endl;
    }

    delete d;
}
