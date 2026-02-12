#include "hashing.hpp"
#include <string>
using namespace std;

// A helper method for hashing strings:
// convert a given string into its equivalent base-10 integer
// when treated as a base-256 ASCII number
int base256conversion(const string &s) {
    int base = 256;
    int result = 0;
    for (char ch : s) {
        result = result * base + static_cast<unsigned char>(ch);
    }
    return result;
}

// hashes a string by:
// 1) dividing it into a number of substrings ("folds")
//    each of which is foldSize-many characters long, then
// 2) converting each fold into a base-256 integer, and finally
// 3) combining everything together
int cs20::hash(const string &key, int foldSize) {
    int hashValue = 0;
    int keyLength = key.length();
    
    for (int i = 0; i < keyLength; i += foldSize) {
        string fold = key.substr(i, foldSize);
        hashValue += base256conversion(fold); 
    }
    
    return hashValue;
}

int cs20::hash(int key) {
    return key;
}