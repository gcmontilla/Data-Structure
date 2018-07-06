//
// Created by Gregory Montilla on 5/2/18.
//

#ifndef HASH_HASHTABLE_H
#define HASH_HASHTABLE_H

#include <iomanip>
#include "record.h"

template<typename T>
class HashTable{
public:
    static const int CAPACITY = 17;
    HashTable();
    void insert(const T& entry);
    void remove(int key);
    bool is_present(int key) const;
    void find( int key, bool& found, T& result) const;
    int size();
    int get_collisions();
    void displayHash();
private:
    static const int NEVER_USED = -1;
    static const int PREV_USED = -2;
    int _size;
    int collisions;
    T data[CAPACITY];
    int hash(int key) const;
    int next_index(int index) const;
    void find_index(int key, bool& found, int& index) const;
    bool never_used(int size) const;
    bool is_vacant(int size) const;
};

template<typename T>
HashTable<T>::HashTable() {
    _size = 0;
    collisions = 0;
    for (int i = 0; i < CAPACITY; ++i) {
        data[i].key = NEVER_USED;
    }
}

template<typename T>
void HashTable<T>::insert(const T &entry) {
    bool is_present;
    int index;
    find_index(entry.key, is_present,index);
    if(!is_present) {
        index = hash(entry.key);
        while (!is_vacant(index)) {
            assert(size() < CAPACITY);
            index = next_index(index);
            ++collisions;
        }
        ++_size;
        data[index] = entry;
    }
}


template<typename T>
void HashTable<T>::remove(int key) {
    assert(key >= 0);
    bool found;
    int index;
    find_index(key, found, index);
    if (found) {
        data[index].key = PREV_USED;
        --_size;
    }
}

template<typename T>
bool HashTable<T>::is_present(int key) const {
    bool found;
    int index;
    assert(key >= 0);
    find(key, found, index);
    return found;
}

template<typename T>
void HashTable<T>::find(int key, bool &found, T &result) const {
    int index;
    assert(key >= 0);
    find(key, found, index);
    if (found) {
        result = data[index];
    }
}

template<typename T>
int HashTable<T>::size() {
    return _size;
}

template<typename T>
int HashTable<T>::next_index(int index) const {
    return ((index+1) % CAPACITY);
}

template<typename T>
void HashTable<T>::find_index(int key, bool &found, int& index) const {
    int count = 0;
    index = hash(key);
    while((count<CAPACITY) && (!never_used(index)) && (data[index].key != key)) {
        ++count;
        index = next_index(index);
    }
    found = (data[index].key == index);
}

template<typename T>
bool HashTable<T>::never_used(int size) const {
    return data[size].key == NEVER_USED;
}

template<typename T>
bool HashTable<T>::is_vacant(int size) const {
    return data[size].key < 0;
}

template<typename T>
int HashTable<T>::hash(int key) const {
    return key % CAPACITY;
}

template<typename T>
int HashTable<T>::get_collisions() {
    return collisions;
}

template <typename T>
void HashTable<T>::displayHash() {
    for (int i = 0; i < CAPACITY; i++) {
        cout << "[" << setfill('0') << setw(3) << i << "]";
        cout << "->[" << setw(4) << data[i].key << ":" << setw(4) << data[i].value << "]";
        cout << "->|||" << endl;
    }
}


#endif //HASH_HASHTABLE_H

