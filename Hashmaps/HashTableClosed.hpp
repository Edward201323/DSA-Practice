#pragma once

#include "Dictionary.hpp"
#include "hashing.hpp"
#include <iostream>

template<typename Key, typename Val>
class HashTableClosed: public Dictionary<Key, Val> {
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

    // an enum to denote the state of a slot in the hash table
    enum class SlotType {
        EMPTY, TOMBSTONE, RECORD,
    };

    // the size of the underlying arrays for the hash table (total number of slots)
    int M;

    // the underlying dynamic array that stores the Records
    Record *ht;

    // a dynamic parallel array to indicate which slots of ht are in-use
    SlotType *flags;

    // the linear probing function (optionally with skips) 
    int probe(int) const;

    // the parameter for the linear probing function
    int probe_constant;

    int length;

public:
    // default constructor
    // first argument: size of the underlying hash table
    // second argument: the coefficient to use in linear probing
    HashTableClosed(int = 100, int = 1);

    // destructor
    virtual ~HashTableClosed();

    // it would be good practice to have a copy constructor and assignment operator,
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

    // print each slot of the hash table (for testing purposes)
    void print() const;
};

template<typename Key, typename Val>
HashTableClosed<Key, Val>::HashTableClosed(int maxSize, int probeSkipNum) {
    this->M = maxSize;
    this->probe_constant = probeSkipNum;
    this->length = 0;

    this->ht = new Record[maxSize];
    this->flags = new SlotType[maxSize];
    
    for(int i = 0; i < maxSize; i++){
        this->flags[i] = SlotType::EMPTY;
    }
}

template<typename Key, typename Val>
HashTableClosed<Key, Val>::~HashTableClosed() {
    delete[] this->ht;
    delete[] this->flags;
}

template<typename Key, typename Val>
void HashTableClosed<Key, Val>::clear() {
    this->length = 0;
    delete[] this->ht;
    this->ht = new Record[this->M];

    for(int i = 0; i < this->M; i++){
        this->flags[i] = SlotType::EMPTY;
    }
}

template<typename Key, typename Val>
Val HashTableClosed<Key, Val>::find(const Key &k) const {
    for(int i = 0; i < this->M; i++){
        int index = (cs20::hash(k) + probe(i)) % this->M;
        if(this->flags[index] == SlotType::EMPTY){
            throw std::string("Key does not exist!");
        }
        if(this->flags[index] == SlotType::RECORD && this->ht[index].k == k){
            return this->ht[index].v;
        }
    }
    throw std::string("Key does not exist!");
}

template<typename Key, typename Val>
void HashTableClosed<Key, Val>::insert(const Key &k, const Val &v) {
    if(this->length >= this->M){
        throw std::string("The hash is full!");
    }

    int first_tombstone = -1;
    for(int i = 0; i < this->M; i++){
        int index = (cs20::hash(k) + probe(i)) % this->M;
        if(this->ht[index].k == k && this->flags[index] == SlotType::RECORD){
            this->ht[index].v = v;
            return;
        }
        else if(this->flags[index] == SlotType::TOMBSTONE && first_tombstone == -1){
            first_tombstone = index;
        }
        else if(this->flags[index] == SlotType::EMPTY){
            if(first_tombstone != -1){
                index = first_tombstone;
            }
            this->ht[index].k = k;
            this->ht[index].v = v;
            this->flags[index] = SlotType::RECORD;
            this->length++;
            return;
        }
    }
    throw std::string("The hash is full!");
}

template<typename Key, typename Val>
int HashTableClosed<Key, Val>::probe(int i) const {
    return probe_constant * i;
}

template<typename Key, typename Val>
void HashTableClosed<Key, Val>::remove(const Key &k) {    
    for(int i = 0; i < this->M; i++){
        int index = (cs20::hash(k) + probe(i)) % this->M;
        if(this->flags[index] == SlotType::EMPTY){
            throw std::string("The key you're trying to remove DNE!");
        }
        if(this->ht[index].k == k && this->flags[index] == SlotType::RECORD){
            this->flags[index] = SlotType::TOMBSTONE;
            this->length--;
            return;
        }
    }
    throw std::string("The key you're trying to remove DNE!");
}

template<typename Key, typename Val>
int HashTableClosed<Key, Val>::size() const {
    return this->length;
}

template<typename Key, typename Val>
void HashTableClosed<Key, Val>::print() const {
    for (int i = 0; i < this->M; i++) {
        std::cout << i << " ";
        switch (this->flags[i]) {
        case SlotType::EMPTY:
            std::cout << "empty";
            break;
        case SlotType::TOMBSTONE:
            std::cout << "tombstone";
            break;
        case SlotType::RECORD:
            std::cout << "key=" << this->ht[i].k << ", value=" << this->ht[i].v;
            break;
        }
        std::cout << std::endl;
    }
}