#include "hashing.hpp"
#include <string>
using namespace std;

// A helper method for hashing strings:
// convert a given string into its equivalent base-10 integer
// when treated as a base-256 ASCII number
int base256conversion(const string &s) {
    int total = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        total = total * 256 + static_cast<unsigned char>(s[i]);
    }
    return total;
}

// hashes a string by:
// 1) dividing it into a number of substrings ("folds")
//    each of which is foldSize-many characters long, then
// 2) converting each fold into a base-256 integer, and finally
// 3) combining everything together
int cs20::hash(const string &key, int foldSize) {
    int total = 0;
    size_t len = key.size();

    for (size_t i = 0; i < len; i += foldSize) {
        string fold = key.substr(i, foldSize);
        int foldValue = base256conversion(fold);
        total += foldValue;
    }
    return total;
}