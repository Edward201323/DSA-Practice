#pragma once

#include "Dictionary.hpp"
#include "hashing.hpp"

template<typename Key, typename Val>
class HashTable: public Dictionary<Key, Val> {
protected:
    // an element in a dictionary, contains a key and a value
    struct Record {
        Key k;
        Val v;

        Record() :
                k(Key()), v(Val()) {
        }
        Record(Key x, Val y) :
                k(x), v(y) {
        }
    };

    // the size of the underlying arrays for the hash table (total number of slots)
    int M;

    // the underlying dynamic array that stores the Records
    Record *ht;

    // a dynamic parallel array to indicate which slots of ht are in-use
    bool *occupied;

    int length;

public:
    // default constructor
    HashTable(int = 100);

    // destructor
    virtual ~HashTable();

    // XXX it would be good practice to have a copy constructor and assignment operator,
    // but we'll skip those for this lab.

    // remove all records in the dictionary, resetting to the initial state
    virtual void clear() override;

    // retrieve the record that matches the argument key
    virtual Val find(const Key&) const override;

    // add the record as a key-value pair to the dictionary
    virtual void insert(const Key&, const Val&) override;

    // remove the record that matches the argument key from the dictionary
    virtual void remove(const Key&) override;

    // return the number of records in the dictionary
    virtual int size() const override;
};

template<typename Key, typename Val>
HashTable<Key, Val>::HashTable(int maxSize) {
    this->M = maxSize;
    this->length = 0;

    this->ht = new Record[M];
    this->occupied = new bool[M];
}

template<typename Key, typename Val>
HashTable<Key, Val>::~HashTable() {
    delete[] this->ht;
    delete[] this->occupied;
}

template<typename Key, typename Val>
void HashTable<Key, Val>::clear() {
    delete[] this->ht;
    delete[] this->occupied;

    this->ht = new Record[M];
    this->occupied = new bool[M];

    this->length = 0;
}

template<typename Key, typename Val>
Val HashTable<Key, Val>::find(const Key &k) const {
    int hash_index = cs20::hash(k) % M;
    if(this->occupied[hash_index] == true && this->ht[hash_index].k == k){
        return this->ht[hash_index].v;
    } else {
        throw std::string("The key does not exist!");
    }
}

template<typename Key, typename Val>
void HashTable<Key, Val>::insert(const Key &k, const Val &v) {
    int hash_index = cs20::hash(k) % M;
    if(this->occupied[hash_index] == false){
        this->occupied[hash_index] = true;
        
        this->ht[hash_index].k = k;
        this->ht[hash_index].v = v;

        this->length++;
    } else {
        throw std::string("There is a key at that index!");
    }
}

template<typename Key, typename Val>
void HashTable<Key, Val>::remove(const Key &k) {
    int hash_index = cs20::hash(k) % M;
    if(this->occupied[hash_index] == true){
        this->occupied[hash_index] = false;
        this->length--;
    } else {
        throw std::string("The key does not exist!");
    }
}

template<typename Key, typename Val>
int HashTable<Key, Val>::size() const {
    return this->length;
}
