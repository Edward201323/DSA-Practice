#include "ArrayListDictionary.hpp"
#include <string>
#include <iostream>
using namespace std;

int main() {
    // variables
    const SearchImpl mode = SearchImpl::SEQ_ITER; // TODO change this to test your methods
    ArrayListDictionary<string, string> dict(mode, 8);
    string userWord;

    // add data to the dictionary
    dict.insert("banana", "a fruit that many like, or a phone");
    dict.insert("cactus", "a pointy plant");
    dict.insert("dog", "a domesticated fluff ball");
    dict.insert("graph", "an awesome data structure!");
    dict.insert("haskell", "fantastic programming language, go learn it");
    dict.insert("igloo", "a cool house");
    dict.insert("phoenix", "a bird on fire");
    dict.insert("quack", "said Mr. Duck");

    // loop to let the user search for entries in the dictionary
    while (true) {
        try {
            cout << "Enter a key to search my dictionary (or -1 to stop): ";
            getline(cin, userWord);
            if (userWord == "-1") {
                break;
            }
            cout << dict.find(userWord) << endl;
        } catch (const string &e) {
            cout << e << endl;
        }
    }

    // terminate
    return 0;
}
