//
// Created by Gregory Montilla on 5/7/18.
//

#ifndef HASH_CHAINEDHASHTABLE_H
#define HASH_CHAINEDHASHTABLE_H

#include<iostream>
#include <iomanip>
#include <list>
#include "record.h"

using namespace std;

template <typename T>
class ChainedHashTable {
private:
    static const int BUCKET = 11;
    list<T> *table;
public:
    ChainedHashTable();
    void insert_item(const T& entry);
    void delete_item(int key);
    int hash_function(int x) {
        return (x % BUCKET);
    }
    void display_hash();
};

template <typename T>
ChainedHashTable<T>::ChainedHashTable() {
    table = new list<T>[BUCKET];
}

template <typename T>
void ChainedHashTable<T>::insert_item(const T &entry){
    int index = hash_function(entry.key);
    table[index].push_back(entry);
}

template <typename T>
void ChainedHashTable<T>::delete_item(int key){
    int index = hash_function(key);
    typename list<T>:: iterator i;
    for (i = table[index].begin(); i != table[index].end(); i++) {
        if (i->key == key) {
            break;
        }
    }
    if (i != table[index].end()) {
        table[index].erase(i);
    }
}

template <typename T>
void ChainedHashTable<T>::display_hash(){
    for (int i = 0; i < BUCKET; i++) {
        cout << "[" << setfill('0') << setw(3) << i << "]";
        for (auto x : table[i]) {
            cout << "->[" << setw(4) << x.key << ":" << setw(4) << x.value << "]";
        }
        cout << "->|||" << endl;
    }
}

#endif //HASH_CHAINEDHASHTABLE_H
