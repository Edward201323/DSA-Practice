#pragma once

#include <string>

/**
 * This file contains hashing methods for different data types.
 * They will all be overloaded methods called "hash". This is important:
 * A templated HashTable<K,V> can generically call "hash"
 * and it will work out as long as this file contains some `int hash(const K &key)`
 * for whatever that type K is.
 *
 * For example, by having an `int hash(const std::string &key)`,
 * A `HashTable<std::string, ANYTHING>` will have access to an appropriate hash function.
 * 
 * Finally, "hash" is a pretty common name:
 * for example, the standard library has its own overloaded hash functions called `std::hash`.
 * We'll similarly put ours inside of our own "namespace" to help prevent potential naming collisions.
 */

namespace cs20 {
    // hash a string using the "folding" method
    // (if no foldSize is provided, we'll use 2 as a default)
    int hash(const std::string &key, int foldSize = 2);

    // This is where we would provide more overloaded hash functions.
    // If you are bored, you could add an
    // int hash (int key, int numDigits = SOMETHING);
    // that implements the mid-square method for integers
    // and confirm that you can make a HashTable<int, ANYTHING> that works.
}
